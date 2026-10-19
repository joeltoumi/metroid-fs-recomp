#!/usr/bin/env python3
"""Split the decomp's pointer-bearing data blobs into typed C (mf-android).

Some of src/data's `sBlob_<start>_<end>` arrays are still raw bytes copied out
of the ROM, but they contain 32-bit ROM pointers: mostly animation frame
tables (struct FrameData) and pointer tables. On the GBA that's fine; a 64-bit
build can't use them, because the pointers are 4 bytes and point into the
GBA's address space.

This tool rewrites each such blob, in place and in the same order, as:
  * raw pieces         const u8 sBlob_<s>_<e>[] = INCBIN_U8("data/Blob_<s>_<e>.bin");
  * frame tables       const struct FrameData sFrameData_<addr>[] = { ... };
  * pointer tables     const void* const sPointers_<addr>[] = { ... };
with every pointer written as a symbol expression, and updates database.json
(new raw pieces, US and EU addresses). The GBA build still produces the same
ROM; the native build gets real pointers.

References to the old blob (`(const u8*)sBlob_X + 0x123`, `sBlob_X + 0x123`,
bare `sBlob_X`) in src/ and port/decomp/ are rewritten to the new pieces.
Declarations of all pieces go in include/data/blob_pieces.h.

Pointer detection: a word is a pointer when it is a ROM address and, in the
EU ROM, the same word moved by the EU data shift (so code pointers below the
first EU shift are found by being a function's address + 1 instead).

Usage: split_blobs.py --repo . --elf mf_us.elf --us mf_us.gba --eu mf_eu.gba
                      --eumap eumap.json BLOB [BLOB...]   (dry run without --apply)
"""
import argparse
import bisect
import json
import re
import struct
import subprocess
from pathlib import Path

ROM = 0x08000000


def load_syms(elf):
    syms = []
    out = subprocess.run(["arm-none-eabi-nm", "-S", "-n", elf], capture_output=True, text=True).stdout
    for l in out.splitlines():
        p = l.split()
        if len(p) == 4 and p[0].startswith("08") and not p[3].startswith((".", "$")):
            syms.append([int(p[0], 16), int(p[1], 16), p[2], p[3]])
        elif len(p) == 3 and p[0].startswith("08") and p[1] in "Tt" and not p[2].startswith((".", "$", "_0")):
            syms.append([int(p[0], 16), 2, p[1], p[2]])
    syms.sort()
    return syms


class Layout:
    """Address -> C expression, over ELF symbols plus the new pieces."""

    def __init__(self, syms):
        self.items = [(s[0], s[1], s[2], s[3], None) for s in syms]
        self.funcs = {s[0] for s in syms if s[2] in "Tt"}
        self.removed = set()

    def replace(self, blob_name, pieces):
        self.removed.add(blob_name)
        self.items = [i for i in self.items if i[3] != blob_name]
        for p in pieces:
            self.items.append((p["addr"], p["size"], "R", p["name"], p))
        self.items.sort()
        self.starts = [i[0] for i in self.items]

    def finish(self):
        self.items.sort()
        self.starts = [i[0] for i in self.items]

    def find(self, a):
        i = bisect.bisect_right(self.starts, a) - 1
        best = None
        for j in range(i, max(i - 8, -1), -1):
            s = self.items[j]
            if s[0] <= a < s[0] + max(s[1], 1) and (best is None or s[0] > best[0]):
                best = s
        return best

    used = set()

    def expr(self, a, ctype="const u8*"):
        """C expression for ROM address a (an address constant)."""
        e, s = self._expr(a)
        if s is not None and s[4] is None:
            Layout.used.add(s[3])
        return e, s

    def _expr(self, a):
        if a & 1 and (a - 1) in self.funcs:
            s = self.find(a - 1)
            return s[3], s
        s = self.find(a)
        if s is None:
            return None, None
        start, size, kind, name, piece = s
        off = a - start
        if piece is not None and piece["kind"] == "frames":
            if off % 8:
                return None, s
            return f"&{name}[{off // 8}]", s
        if piece is not None and piece["kind"] == "pointers":
            if off % 4:
                return None, s
            return f"&{name}[{off // 4}]", s
        if off == 0:
            return name, s
        return f"((const u8*){name} + {off:#x})", s


def classify(us, eu, ua, ea, size, layout):
    """Per 4-byte slot of the blob: is it a pointer?"""
    ptr = {}
    for o in range((4 - ua % 4) % 4, size - 3, 4):
        a = struct.unpack_from("<I", us, ua + o)[0]
        b = struct.unpack_from("<I", eu, ea + o)[0]
        if ROM <= a < ROM + 0x1000000:
            if a != b and ROM <= b < ROM + 0x1000000:
                ptr[o] = a
            elif a & 1 and (a - 1) in layout.funcs:
                ptr[o] = a
    # A ROM address between two pointers is one too (its target may not
    # have moved in the EU ROM).
    for o in range((4 - ua % 4) % 4, size - 3, 4):
        a = struct.unpack_from("<I", us, ua + o)[0]
        if o not in ptr and ROM <= a < ROM + 0x800000 and o - 4 in ptr and o + 4 in ptr:
            ptr[o] = a
    # A function address alone in the middle of raw data is a coincidence
    # (graphics), not a pointer: keep only those next to another pointer.
    for o in [o for o, a in ptr.items() if a < ROM + 0x86e50]:
        if o - 4 not in ptr and o + 4 not in ptr:
            del ptr[o]
    return ptr


def split(us, ua, size, ptr):
    """Pieces: frame tables, pointer tables and raw runs."""
    pieces = []
    o = 0
    raw_start = 0

    def flush_raw(end):
        if end > raw_start:
            pieces.append({"kind": "raw", "off": raw_start, "size": end - raw_start})

    def u32(x):
        return struct.unpack_from("<I", us, ua + x)[0]

    while o < size:
        if o in ptr and (ua + o) % 4 == 0:
            # Frame table: {ptr, timer, 0, 0, 0}... {0, 0}
            entries = []
            p = o
            while p + 8 <= size and p in ptr and u32(p + 4) < 0x100:
                entries.append((ptr[p], u32(p + 4)))
                p += 8
            if entries and p + 8 <= size and u32(p) == 0 and u32(p + 4) == 0:
                flush_raw(o)
                pieces.append({"kind": "frames", "off": o, "size": p + 8 - o, "entries": entries})
                o = p + 8
                raw_start = o
                continue
            # Pointer table: consecutive pointers (NULLs allowed inside).
            p = o
            vals = []
            while p + 4 <= size and (p in ptr or (u32(p) == 0 and p + 4 in ptr)):
                vals.append(ptr.get(p, 0))
                p += 4
            if len(vals) >= 1:
                flush_raw(o)
                pieces.append({"kind": "pointers", "off": o, "size": p - o, "values": vals})
                o = p
                raw_start = o
                continue
        o += 1 if (ua + o) % 4 else 4
    flush_raw(size)
    return pieces


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--repo", required=True)
    ap.add_argument("--elf", required=True)
    ap.add_argument("--us", required=True)
    ap.add_argument("--eu", required=True)
    ap.add_argument("--eumap", required=True)
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("blobs", nargs="+")
    args = ap.parse_args()

    repo = Path(args.repo)
    us = open(args.us, "rb").read()
    eu = open(args.eu, "rb").read()
    eumap = json.loads(open(args.eumap).read())
    layout = Layout(load_syms(args.elf))
    layout.finish()

    plans = {}
    eu_ptr = {}  # US pointer value -> EU pointer value, from the same slots
    for name in args.blobs:
        m = re.match(r"sBlob_([0-9a-fA-F]+)_([0-9a-fA-F]+)$", name)
        ua = int(m.group(1), 16)
        size = int(m.group(2), 16) - ua
        ea = eumap[name][2]
        ptr = classify(us, eu, ua, ea, size, layout)
        pieces = split(us, ua, size, ptr)
        for p in pieces:
            p["addr"] = ROM + ua + p["off"]
            p["eu"] = ea + p["off"]
            a = ua + p["off"]
            if p["kind"] == "raw":
                p["name"] = f"sBlob_{a:x}_{a + p['size']:x}"
                if p["off"] == 0 and p["size"] == size:
                    p["name"] = name
            elif p["kind"] == "frames":
                p["name"] = f"sFrameData_{a:x}"
            else:
                p["name"] = f"sPointers_{a:x}"
        plans[name] = pieces
        layout.replace(name, pieces)
        for o, a in ptr.items():
            eu_ptr[a] = struct.unpack_from("<I", eu, ea + o)[0]

    # EU address of each raw piece. Usually the blob's EU address plus the
    # piece's offset, but localized graphics can change sizes inside a blob:
    # then the EU pointers to the piece say where it is.
    for name, pieces in plans.items():
        for p in pieces:
            if p["kind"] != "raw":
                continue
            us_bytes = us[p["addr"] - ROM:p["addr"] - ROM + p["size"]]
            if eu[p["eu"]:p["eu"] + p["size"]] == us_bytes:
                continue
            votes = {}
            for t, e in eu_ptr.items():
                if p["addr"] <= t < p["addr"] + p["size"]:
                    cand = e - (t - p["addr"]) - ROM
                    votes[cand] = votes.get(cand, 0) + 1
            if votes:
                best = max(votes, key=votes.get)
                if best != p["eu"]:
                    print(f"EU {p['name']}: {p['eu']:#x} -> {best:#x} (pointers: {votes})")
                    p["eu"] = best
            elif eu.find(us_bytes, max(0, p["eu"] - 0x4000), p["eu"] + 0x4000 + p["size"]) >= 0:
                p["eu"] = eu.find(us_bytes, max(0, p["eu"] - 0x4000), p["eu"] + 0x4000 + p["size"])
            else:
                print(f"EU {p['name']}: content differs and no pointer locates it, keeping {p['eu']:#x}")

    # Emit.
    decls = []
    bad = []
    # A few blobs are `static u8` (not const): their pieces keep that, so they
    # stay in the same section and the ROM layout doesn't move.
    constness = {}
    for f in (repo / "src").rglob("*.c"):
        for m in re.finditer(r'^(?:static\s+)?(const\s+)?u8 (sBlob_\w+)\[\d*\] = INCBIN_U8', f.read_text(), re.M):
            constness[m.group(2)] = "const " if m.group(1) else ""
    for name, pieces in plans.items():
        text = []
        c = constness[name]
        for p in pieces:
            if p["kind"] == "raw":
                text.append(f'{c}u8 {p["name"]}[{p["size"]}] = INCBIN_U8("data/{p["name"][1:]}.bin");')
                decls.append(f'extern {c}u8 {p["name"]}[{p["size"]}];')
            elif p["kind"] == "frames":
                lines = [f'{c}struct FrameData {p["name"]}[{len(p["entries"]) + 1}] = {{']
                for a, timer in p["entries"]:
                    e, _ = layout.expr(a)
                    if e is None:
                        bad.append((p["name"], hex(a)))
                        e = f"(const u8*){a:#x}"
                    lines.append(f"    {{ (const u16*){e}, {timer} }},")
                lines.append("    FRAME_DATA_TERMINATOR")
                lines.append("};")
                text.append("\n".join(lines))
                decls.append(f'extern {c}struct FrameData {p["name"]}[{len(p["entries"]) + 1}];')
            else:
                lines = [f'const void* {c}{p["name"]}[{len(p["values"])}] = {{']
                for a in p["values"]:
                    if a == 0:
                        lines.append("    NULL,")
                        continue
                    e, _ = layout.expr(a)
                    if e is None:
                        bad.append((p["name"], hex(a)))
                        e = f"(const u8*){a:#x}"
                    lines.append(f"    (const void*){e},")
                lines.append("};")
                text.append("\n".join(lines))
                decls.append(f'extern const void* {c}{p["name"]}[{len(p["values"])}];')
        plans[name] = (pieces, "\n\n".join(text))

    summary = {n: [(p["kind"], hex(p["addr"]), p["size"]) for p in ps] for n, (ps, _) in plans.items()}
    for n, s in summary.items():
        kinds = {}
        for k, _, sz in s:
            kinds[k] = kinds.get(k, 0) + 1
        print(n, kinds)
    for b in bad:
        print("UNRESOLVED", *b)
    if not args.apply:
        return

    # Rewrite the blob definitions.
    for name, (pieces, text) in plans.items():
        for f in (repo / "src").rglob("*.c"):
            s = f.read_text()
            m = re.search(r'^(static\s+)?(const\s+)?u8 ' + name + r'\[\d*\] = INCBIN_U8\("[^"]+"\);', s, re.M)
            if m:
                s = s[:m.start()] + text + s[m.end():]
                if '#include "data/blob_pieces.h"' not in s:
                    s = '#include "data/blob_pieces.h"\n' + s
                f.write_text(s)
                break
        else:
            raise SystemExit(f"definition of {name} not found")

    # Declarations of the existing symbols the pointers refer to (copied from
    # their definitions; a `static` one becomes global).
    DEF = re.compile(r'^(static\s+)?((?:const\s+)?[A-Za-z_][\w\s\*]*?(?:const\s*)?\**)\s*\b(\w+)\s*((?:\[[^\]]*\])+)\s*=')
    FUNC = re.compile(r'^(static\s+)?([A-Za-z_][\w\s\*]*?)\b(\w+)\s*\(([^)]*)\)\s*$')
    need = sorted(Layout.used - set(plans))
    found = {}
    for f in (repo / "src").rglob("*.c"):
        lines = f.read_text().split("\n")
        changed = False
        for i, l in enumerate(lines):
            m = DEF.match(l)
            if m and m.group(3) in need and m.group(3) not in found:
                found[m.group(3)] = f"extern {m.group(2).strip()} {m.group(3)}{m.group(4)};"
                if m.group(1):
                    lines[i] = l[len(m.group(1)):]
                    changed = True
                continue
            m = FUNC.match(l)
            if m and m.group(3) in need and m.group(3) not in found and i + 1 < len(lines) and lines[i + 1].startswith("{"):
                found[m.group(3)] = f"{m.group(2).strip()} {m.group(3)}({m.group(4)});"
        if changed:
            f.write_text("\n".join(lines))
    for n in need:
        if n not in found:
            found[n] = f"void {n}(void); // assembly"
    decls = [found[n] for n in need] + [""] + decls

    # Header with every piece and the symbols their pointers need.
    hdr = repo / "include" / "data" / "blob_pieces.h"
    hdr.write_text("#ifndef BLOB_PIECES_H\n#define BLOB_PIECES_H\n\n"
                   "// Generated by tools/port/split_blobs.py.\n\n"
                   '#include "types.h"\n#include "oam.h"\n\n' + "\n".join(decls) + "\n\n#endif /* BLOB_PIECES_H */\n")

    # References to the old blobs.
    ref = re.compile(r'(\(\s*const\s+u8\s*\*\s*\)\s*)?\b(' + "|".join(plans) + r')\b(\s*\+\s*(0x[0-9a-fA-F]+|\d+))?')
    for f in list((repo / "src").rglob("*.c")) + list((repo / "port" / "decomp").rglob("*.[ch]")):
        s = f.read_text()
        if not ref.search(s):
            continue

        def sub(m):
            name = m.group(2)
            off = int(m.group(4), 0) if m.group(4) else 0
            a = int(name.split("_")[1], 16) + off + ROM
            # Declarations (`extern const u8 sBlob_X[];`) are dropped below.
            e, _ = layout.expr(a)
            if e is None:
                print("UNREWRITTEN", f, m.group(0))
                return m.group(0)
            return e if not m.group(1) else f"((const u8*){e})"

        lines = []
        for line in s.split("\n"):
            if re.match(r'\s*extern\s+(const\s+)?u8\s+(' + "|".join(plans) + r')\s*\[', line):
                continue
            lines.append(line)
        s = ref.sub(sub, "\n".join(lines))
        if '#include "data/blob_pieces.h"' not in s:
            s = '#include "data/blob_pieces.h"\n' + s
        f.write_text(s)

    # database.json: drop the old blob, add the raw pieces.
    dbp = repo / "database.json"
    db = json.loads(dbp.read_text())
    out = []
    for e in db:
        stem = e["path"][:-4] if e["path"].endswith(".bin") else None
        if stem and "s" + stem in plans:
            for p in plans["s" + stem][0]:
                if p["kind"] == "raw":
                    out.append({"path": p["name"][1:] + ".bin", "count": f"0x{p['size']:X}",
                                "addr": {"us": f"0x{p['addr'] - ROM:X}", "eu": f"0x{p['eu']:X}"}, "size": 1})
            continue
        out.append(e)
    dbp.write_text(json.dumps(out, indent=2) + "\n")


if __name__ == "__main__":
    main()
