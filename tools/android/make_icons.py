#!/usr/bin/env python3
"""Builds the Android launcher icons from the logo artwork.

The logo is a rounded square on a white background. The script finds the
rounded square, cuts it out with a clean transparent edge and writes, for
every density:
  - ic_launcher.png / ic_launcher_round.png: the logo as is (legacy launchers)
  - ic_launcher_background.png / ic_launcher_foreground.png: adaptive icon
    layers (API 26+). The background is a flat colour taken from the logo's
    edge; the logo sits in the foreground, inside the safe zone, so whatever
    shape the launcher masks the icon to, no text gets cut.
and ic_launcher-playstore.png (512x512) next to res/.

Usage: make_icons.py LOGO RES_DIR
Needs Pillow.
"""
import os
import sys

from PIL import Image, ImageChops, ImageDraw, ImageFilter

DENSITIES = {"mdpi": 1.0, "hdpi": 1.5, "xhdpi": 2.0, "xxhdpi": 3.0, "xxxhdpi": 4.0}
S = 1024        # working size
INSET = 4       # px trimmed from the edge, to drop the JPEG halo
LOGO_DP = 62    # logo size inside the 108dp adaptive canvas (safe zone: 66dp circle)


def cut_logo(path):
    im = Image.open(path).convert("RGB")
    w, h = im.size
    # Background: the white area connected to the image border. Flood fill
    # a marker colour from the corners over near-white pixels.
    lum = im.convert("L")
    marker = Image.merge("RGB", [lum.point(lambda v: 255 if v > 200 else 0)] * 3)
    for corner in ((0, 0), (w - 1, 0), (0, h - 1), (w - 1, h - 1)):
        ImageDraw.floodfill(marker, corner, (255, 0, 0), thresh=0)
    r, g, _ = marker.split()
    outside = ImageChops.subtract(r, g)  # 255 only where the fill reached
    mask = ImageChops.invert(outside)
    # Pull the edge in to drop the light JPEG halo, then soften it.
    mask = mask.filter(ImageFilter.MinFilter(2 * INSET + 1)).filter(ImageFilter.GaussianBlur(1.2))

    x0, y0, x1, y1 = mask.point(lambda v: 255 if v > 128 else 0).getbbox()
    art = im.convert("RGBA")
    art.putalpha(mask)
    art = art.crop((x0, y0, x1, y1))
    aw, ah = art.size

    # Centre on a transparent square (the artwork may be a few px off square).
    side = max(aw, ah)
    logo = Image.new("RGBA", (side, side), (0, 0, 0, 0))
    logo.paste(art, ((side - aw) // 2, (side - ah) // 2), art)

    # Adaptive background: the art's average colour along its edge, darkened.
    band = im.crop((x0 + side // 6, y0 + 4, x1 - side // 6, y0 + side // 12))
    edge = band.resize((1, 1), Image.BOX).getpixel((0, 0))
    return logo.resize((S, S), Image.LANCZOS), tuple(int(c * 0.7) for c in edge)


def save(img, path, px):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    img.resize((px, px), Image.LANCZOS).save(path, optimize=True)


def main():
    if len(sys.argv) != 3:
        sys.exit(__doc__)
    logo, edge = cut_logo(sys.argv[1])
    res = sys.argv[2]

    bg = Image.new("RGB", (S, S), edge)
    fg = Image.new("RGBA", (S, S), (0, 0, 0, 0))
    size = round(S * LOGO_DP / 108)
    off = (S - size) // 2
    small = logo.resize((size, size), Image.LANCZOS)
    fg.paste(small, (off, off), small)

    for name, k in DENSITIES.items():
        d = os.path.join(res, "mipmap-" + name)
        save(bg, os.path.join(d, "ic_launcher_background.png"), round(108 * k))
        save(fg, os.path.join(d, "ic_launcher_foreground.png"), round(108 * k))
        save(logo, os.path.join(d, "ic_launcher.png"), round(48 * k))
        save(logo, os.path.join(d, "ic_launcher_round.png"), round(48 * k))
        stale = os.path.join(d, "ic_launcher_monochrome.png")
        if os.path.exists(stale):
            os.remove(stale)

    adaptive = (
        '<?xml version="1.0" encoding="utf-8"?>\n'
        '<adaptive-icon xmlns:android="http://schemas.android.com/apk/res/android">\n'
        '    <background android:drawable="@mipmap/ic_launcher_background" />\n'
        '    <foreground android:drawable="@mipmap/ic_launcher_foreground" />\n'
        '</adaptive-icon>\n'
    )
    d = os.path.join(res, "mipmap-anydpi-v26")
    os.makedirs(d, exist_ok=True)
    for name in ("ic_launcher.xml", "ic_launcher_round.xml"):
        with open(os.path.join(d, name), "w") as fh:
            fh.write(adaptive)

    logo.resize((512, 512), Image.LANCZOS).save(
        os.path.join(res, "..", "ic_launcher-playstore.png"), optimize=True)


if __name__ == "__main__":
    main()
