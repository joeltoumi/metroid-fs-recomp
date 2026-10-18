#!/usr/bin/env python3
"""Generate the native build's runtime-asset glue (mf-android).

The decomp embeds game data at compile time with the INCBIN macros, which
tools/preproc expands from the files `make extract` copies out of the ROM:

    const u16 sCommonTilesPal[16 * 16] = INCBIN_U16("data/common/common_tiles.pal");
    const u8 sMainDeck_70_Bg2[14] = {
        19, // Room width
        14, // Room height
        _INCBIN_U8("data/rooms/main_deck/main_deck_70_bg2.rle")
    };

The port can't ship that data, so for every src/data/**.c file:

  * the file is run through the C preprocessor with -DPLATFORM_PC (the INCBIN
    macros are then left undefined, so they survive as text);
  * each INCBIN becomes a zero initializer of the exact size (database.json),
    and the file is written to OUT/data/<path>.c, which is what gets compiled;
  * a constructor at the end registers, for each INCBIN, where its bytes go:
    (address inside the array, ROM offset, byte count). At startup the port
    copies them out of the player's own ROM (port/src/assets.c).

The ROM offsets are the region's column of database.json.

Usage: gen_assets.py --root REPO --out DIR --region us --cc CC [--jobs N]
Prints the list of generated files (one per line) on stdout.
"""
import argparse
import concurrent.futures
import json
import os
import re
import subprocess
import sys
from pathlib import Path

ELEM_SIZES = {"U8": 1, "S8": 1, "U16": 2, "S16": 2, "U32": 4, "S32": 4}

# INCBIN_U8("path") / _INCBIN_U8("path"); the preprocessor may have split it
# over lines only in theory, the decomp keeps each on one line.
INCBIN = re.compile(r'(_?)INCBIN_([US](?:8|16|32))\s*\(\s*"([^"]+)"\s*\)')
# `NAME[..][..] = {` (with optional elements already listed) right before an
# _INCBIN, or `NAME[..] =` right before a plain INCBIN.
DECL_BRACED = re.compile(r'([A-Za-z_]\w*)\s*((?:\[[^\]]*\]\s*)+)=\s*\{([^{};=]*)$', re.S)
DECL_PLAIN = re.compile(r'([A-Za-z_]\w*)\s*((?:\[[^\]]*\]\s*)+)=\s*$', re.S)


def parse_args():
    ap = argparse.ArgumentParser()
    ap.add_argument("--root", required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--region", default="us")
    ap.add_argument("--cc", default="cc")
    ap.add_argument("--jobs", type=int, default=os.cpu_count() or 2)
    return ap.parse_args()


def load_db(root, region):
    db = json.loads((root / "database.json").read_text())
    entries = {}
    for e in db:
        addr = e["addr"].get(region)
        if addr is None:
            continue
        count = e["count"]
        if isinstance(count, dict):
            count = count[region]
        rel = str(Path(e.get("dir", "data"), e["path"]))
        entries[rel] = (int(addr, 16), int(count, 16) * e["size"])
    return entries


def preprocess(cc, root, region, src):
    # A few of these files also hold code: give it every prototype, as the
    # forced include does for the other game sources.
    cmd = [cc, "-E", "-nostdinc", f"-I{root / 'include'}", f"-I{root / 'port' / 'decomp'}",
           "-include", "port/prototypes.h",
           "-DPLATFORM_PC", f"-DREGION_{region.upper()}", str(src)]
    return subprocess.run(cmd, check=True, capture_output=True, text=True).stdout


def count_elems(prefix):
    """Elements already listed in an initializer prefix (top level commas)."""
    depth = 0
    items = 0
    current = ""
    for ch in prefix:
        if ch in "({[":
            depth += 1
        elif ch in ")}]":
            depth -= 1
        if ch == "," and depth == 0:
            if current.strip():
                items += 1
            current = ""
        else:
            current += ch
    if current.strip():
        items += 1
    return items


def strip_line_markers(text):
    return "\n".join(l for l in text.split("\n") if not l.startswith("#"))


def gen_file(args, root, out, entries, src):
    pp = preprocess(args.cc, root, args.region, src)
    rel_src = src.relative_to(root)
    pieces = []
    sites = []
    pos = 0
    for m in INCBIN.finditer(pp):
        underscore, kind, path = m.group(1), m.group(2), m.group(3)
        if path not in entries:
            raise SystemExit(f"{rel_src}: {path} not in database.json for region {args.region}")
        rom_offset, nbytes = entries[path]
        esize = ELEM_SIZES[kind]
        if nbytes % esize:
            raise SystemExit(f"{rel_src}: {path} size {nbytes} is not a multiple of {esize}")
        count = nbytes // esize
        # The declaration is always just before the INCBIN: only look at the
        # tail of the file so far (searching all of it is quadratic).
        tail = strip_line_markers(pp[max(0, m.start() - 4096):m.start()])
        if underscore:
            d = DECL_BRACED.search(tail)
            if d is None:
                raise SystemExit(f"{rel_src}: can't find the array around {path}")
            prefix = count_elems(d.group(3))
            # Elements before the data are kept; the data itself is zeros.
            replacement = f"[{prefix + count - 1}] = 0"
        else:
            d = DECL_PLAIN.search(tail)
            if d is None:
                raise SystemExit(f"{rel_src}: can't find the array for {path}")
            prefix = 0
            if "[]" in d.group(2).replace(" ", ""):
                replacement = f"{{ [{count - 1}] = 0 }}"
            else:
                # Sized (possibly multi-dimensional) array: zeros fill it.
                replacement = "{ 0 }"
        symbol = d.group(1)
        sites.append((symbol, prefix * esize, rom_offset, nbytes, path))
        pieces.append(pp[pos:m.start()])
        pieces.append(replacement)
        pos = m.end()
    pieces.append(pp[pos:])

    dst = out / "data" / rel_src
    lines = ["".join(pieces)]
    if sites:
        lines += [
            "",
            "// Generated by tools/port/gen_assets.py: where each INCBIN's bytes come from.",
            "typedef struct PortAsset { unsigned char* dst; unsigned int romOffset; unsigned int size; unsigned long arraySize; } PortAsset;",
            "void Port_RegisterAssets(PortAsset* assets, unsigned long count);",
            "static PortAsset sPortAssets[] = {",
        ]
        for symbol, byte_prefix, rom_offset, nbytes, path in sites:
            lines.append(f"    {{ (unsigned char*){symbol} + {byte_prefix}, 0x{rom_offset:x}, 0x{nbytes:x}, sizeof({symbol}) }}, // {path}")
        lines += [
            "};",
            "",
            "__attribute__((constructor)) static void PortRegisterAssets(void)",
            "{",
            "    Port_RegisterAssets(sPortAssets, sizeof(sPortAssets) / sizeof(sPortAssets[0]));",
            "}",
        ]
    text = "\n".join(lines) + "\n"
    dst.parent.mkdir(parents=True, exist_ok=True)
    if not dst.exists() or dst.read_text() != text:
        dst.write_text(text)
    return dst, len(sites)


def main():
    args = parse_args()
    root = Path(args.root).resolve()
    out = Path(args.out).resolve()
    out.mkdir(parents=True, exist_ok=True)

    entries = load_db(root, args.region)
    data_files = sorted(f for f in (root / "src").rglob("*.c")
                        if "/data/" in str(f) or "INCBIN_" in f.read_text(errors="replace"))
    results = []
    with concurrent.futures.ProcessPoolExecutor(max_workers=args.jobs) as ex:
        futs = [ex.submit(gen_file, args, root, out, entries, f) for f in data_files]
        for f in futs:
            results.append(f.result())

    total = sum(n for _, n in results)
    sys.stderr.write(f"gen_assets: {len(results)} data files, {total} ROM assets (region {args.region})\n")
    for w, _ in results:
        print(w)


if __name__ == "__main__":
    main()
