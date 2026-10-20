#!/usr/bin/env python3
"""Generates the Android launcher icons (original artwork, no game assets).

Writes an adaptive icon (background + foreground + monochrome layers, API 26+)
and legacy square/round PNGs for older launchers, for every density.

Usage: make_icons.py zm|mf RES_DIR
Needs Pillow and the Inter Display Bold font (fonts-inter).
"""
import math
import os
import random
import sys

from PIL import Image, ImageChops, ImageDraw, ImageFilter, ImageFont

FONT = "/usr/share/fonts/opentype/inter/InterDisplay-Black.otf"
FONT_FALLBACK = "/usr/share/fonts/opentype/inter/InterDisplay-Bold.otf"

# Adaptive icon layers are 108dp; legacy icons 48dp.
DENSITIES = {"mdpi": 1.0, "hdpi": 1.5, "xhdpi": 2.0, "xxhdpi": 3.0, "xxxhdpi": 4.0}
S = 1024  # working canvas for one 108dp layer

THEMES = {
    # Zero Mission: a warm planet over deep space.
    "zm": dict(
        sky=((10, 8, 34), (52, 16, 58)),
        orb=((255, 196, 92), (232, 92, 28), (120, 26, 18)),
        ring=(255, 210, 140),
        glow=(255, 120, 40),
        text="ZM",
        text_color=(255, 255, 255),
        shadow=(70, 10, 10),
    ),
    # Fusion: a glowing nucleus inside a cold, cellular sky.
    "mf": dict(
        sky=((4, 20, 36), (8, 64, 84)),
        orb=((230, 255, 150), (60, 210, 120), (10, 80, 70)),
        ring=(150, 240, 255),
        glow=(80, 255, 170),
        text="MF",
        text_color=(255, 255, 255),
        shadow=(0, 40, 50),
    ),
}


def lerp(a, b, t):
    return tuple(int(round(x + (y - x) * t)) for x, y in zip(a, b))


def font(size):
    path = FONT if os.path.exists(FONT) else FONT_FALLBACK
    return ImageFont.truetype(path, size)


def background(theme):
    img = Image.new("RGB", (S, S))
    px = img.load()
    top, bottom = theme["sky"]
    for y in range(S):
        for x in range(S):
            # Diagonal gradient with a soft vignette.
            t = (x + y) / (2 * S)
            c = lerp(top, bottom, t)
            d = math.hypot(x - S * 0.5, y - S * 0.45) / (S * 0.75)
            k = max(0.0, 1.0 - 0.35 * d * d)
            px[x, y] = tuple(int(v * k) for v in c)
    draw = ImageDraw.Draw(img)
    rng = random.Random(7 if theme["text"] == "ZM" else 11)
    for _ in range(90):
        x, y = rng.uniform(0, S), rng.uniform(0, S)
        r = rng.choice((1.5, 2, 2.5, 3.5))
        a = rng.randint(90, 230)
        draw.ellipse((x - r, y - r, x + r, y + r), fill=(a, a, min(255, a + 20)))
    if theme["text"] == "MF":
        # Faint cell membranes.
        cells = Image.new("L", (S, S), 0)
        cd = ImageDraw.Draw(cells)
        for _ in range(14):
            x, y = rng.uniform(0, S), rng.uniform(0, S)
            r = rng.uniform(60, 160)
            cd.ellipse((x - r, y - r, x + r, y + r), outline=60, width=6)
        cells = cells.filter(ImageFilter.GaussianBlur(3))
        tint = Image.new("RGB", (S, S), theme["ring"])
        img = Image.composite(tint, img, cells.point(lambda v: v // 2))
    return img


def orb_layer(theme):
    """The planet/nucleus, inside the 66dp safe zone."""
    layer = Image.new("RGBA", (S, S), (0, 0, 0, 0))
    cx, cy, r = S / 2, S / 2, S * 0.235
    light, mid, dark = theme["orb"]

    # Glow.
    glow = Image.new("L", (S, S), 0)
    ImageDraw.Draw(glow).ellipse((cx - r * 1.25, cy - r * 1.25, cx + r * 1.25, cy + r * 1.25), fill=150)
    glow = glow.filter(ImageFilter.GaussianBlur(S * 0.04))
    layer.paste(Image.new("RGBA", (S, S), theme["glow"] + (255,)), (0, 0), glow)

    # Sphere shading: light from the upper left.
    sphere = Image.new("RGBA", (S, S), (0, 0, 0, 0))
    sp = sphere.load()
    lx, ly = cx - r * 0.45, cy - r * 0.5
    x0, x1 = int(cx - r) - 1, int(cx + r) + 2
    for y in range(int(cy - r) - 1, int(cy + r) + 2):
        for x in range(x0, x1):
            d = math.hypot(x + 0.5 - cx, y + 0.5 - cy)
            if d > r + 1:
                continue
            a = 255 if d <= r else int(255 * (r + 1 - d))
            t = min(1.0, math.hypot(x - lx, y - ly) / (r * 1.7))
            c = lerp(light, mid, min(1.0, t * 1.6)) if t < 0.62 else lerp(mid, dark, (t - 0.62) / 0.38)
            if theme["text"] == "ZM":
                # Banded surface.
                band = math.sin((y - cy) / r * 7.0 + (x - cx) / r * 1.2)
                if band > 0.55:
                    c = tuple(int(v * 0.86) for v in c)
            else:
                # Nucleus.
                dn = math.hypot(x - (cx + r * 0.08), y - (cy + r * 0.1))
                if dn < r * 0.32:
                    k = 1.0 - dn / (r * 0.32)
                    c = lerp(c, (255, 255, 230), k * 0.85)
            sp[x, y] = c + (a,)
    layer = Image.alpha_composite(layer, sphere)

    # Tilted ring in front of the sphere (only the lower half shows over it).
    ring = Image.new("L", (S * 2, S * 2), 0)
    rd = ImageDraw.Draw(ring)
    rw, rh = r * 3.0 * 2, r * 0.9 * 2
    rd.ellipse((S - rw / 2, S - rh / 2, S + rw / 2, S + rh / 2), outline=255, width=int(S * 0.022))
    # Hide the back half where it passes behind the sphere.
    cut = Image.new("L", (S * 2, S * 2), 0)
    ImageDraw.Draw(cut).rectangle((0, 0, S * 2, S), fill=255)
    sphere_mask = Image.new("L", (S * 2, S * 2), 0)
    ImageDraw.Draw(sphere_mask).ellipse((S - r, S - r, S + r, S + r), fill=255)
    hidden = ImageChops.multiply(cut, sphere_mask)
    ring = ImageChops.subtract(ring, hidden)
    ring = ring.rotate(-20, resample=Image.BICUBIC).crop((S // 2, S // 2, S // 2 + S, S // 2 + S))
    layer.paste(Image.new("RGBA", (S, S), theme["ring"] + (255,)), (0, 0), ring)
    return layer


def text_layer(theme, size_frac=0.2):
    layer = Image.new("RGBA", (S, S), (0, 0, 0, 0))
    f = font(int(S * size_frac))
    d = ImageDraw.Draw(layer)
    box = d.textbbox((0, 0), theme["text"], font=f)
    w, h = box[2] - box[0], box[3] - box[1]
    x = S / 2 - w / 2 - box[0]
    y = S * 0.5 - h / 2 - box[1]
    shadow = Image.new("RGBA", (S, S), (0, 0, 0, 0))
    ImageDraw.Draw(shadow).text((x + S * 0.008, y + S * 0.012), theme["text"], font=f, fill=theme["shadow"] + (220,))
    shadow = shadow.filter(ImageFilter.GaussianBlur(S * 0.008))
    layer = Image.alpha_composite(layer, shadow)
    ImageDraw.Draw(layer).text((x, y), theme["text"], font=f, fill=theme["text_color"] + (255,))
    return layer


def monochrome(fg):
    """Themed-icon layer (Android 13+): the shapes as a single-colour mask."""
    a = fg.split()[3].point(lambda v: 255 if v > 100 else 0)
    out = Image.new("RGBA", fg.size, (255, 255, 255, 0))
    out.putalpha(a)
    return out


def save(img, path, px):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    img.resize((px, px), Image.LANCZOS).save(path, optimize=True)


def main():
    if len(sys.argv) != 3 or sys.argv[1] not in THEMES:
        sys.exit(__doc__)
    theme = THEMES[sys.argv[1]]
    res = sys.argv[2]

    bg = background(theme)
    orb = orb_layer(theme)
    fg = Image.alpha_composite(orb, text_layer(theme))
    mono = monochrome(Image.alpha_composite(orb_layer(theme), Image.new("RGBA", (S, S), (0, 0, 0, 0))))
    full = Image.alpha_composite(bg.convert("RGBA"), fg)

    # Legacy icons show the middle 72dp of the 108dp layers, scaled to 48dp.
    inner = int(S * 18 / 108)
    legacy = full.crop((inner, inner, S - inner, S - inner))
    rounded_mask = Image.new("L", legacy.size, 0)
    ImageDraw.Draw(rounded_mask).rounded_rectangle((0, 0) + legacy.size, radius=legacy.size[0] * 0.18, fill=255)
    square = Image.new("RGBA", legacy.size, (0, 0, 0, 0))
    square.paste(legacy, (0, 0), rounded_mask)
    circle_mask = Image.new("L", legacy.size, 0)
    ImageDraw.Draw(circle_mask).ellipse((0, 0) + legacy.size, fill=255)
    rnd = Image.new("RGBA", legacy.size, (0, 0, 0, 0))
    rnd.paste(legacy, (0, 0), circle_mask)

    for name, k in DENSITIES.items():
        d = os.path.join(res, "mipmap-" + name)
        save(bg, os.path.join(d, "ic_launcher_background.png"), round(108 * k))
        save(fg, os.path.join(d, "ic_launcher_foreground.png"), round(108 * k))
        save(mono, os.path.join(d, "ic_launcher_monochrome.png"), round(108 * k))
        save(square, os.path.join(d, "ic_launcher.png"), round(48 * k))
        save(rnd, os.path.join(d, "ic_launcher_round.png"), round(48 * k))

    adaptive = (
        '<?xml version="1.0" encoding="utf-8"?>\n'
        '<adaptive-icon xmlns:android="http://schemas.android.com/apk/res/android">\n'
        '    <background android:drawable="@mipmap/ic_launcher_background" />\n'
        '    <foreground android:drawable="@mipmap/ic_launcher_foreground" />\n'
        '    <monochrome android:drawable="@mipmap/ic_launcher_monochrome" />\n'
        '</adaptive-icon>\n'
    )
    d = os.path.join(res, "mipmap-anydpi-v26")
    os.makedirs(d, exist_ok=True)
    for name in ("ic_launcher.xml", "ic_launcher_round.xml"):
        with open(os.path.join(d, name), "w") as fh:
            fh.write(adaptive)

    # Store listing / README size.
    full.resize((512, 512), Image.LANCZOS).save(os.path.join(res, "..", "ic_launcher-playstore.png"), optimize=True)


if __name__ == "__main__":
    main()
