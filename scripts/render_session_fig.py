#!/usr/bin/env python3
"""Render the compile-session figure (barrier -> fix -> success) as PNG.

All terminal content is the real output of the SpecCompiler runs over the
exemplo-condutor project. Regenerate after changing the example.
"""
import sys

from PIL import Image, ImageDraw, ImageFont

FONT = "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf"
FONT_B = "/usr/share/fonts/truetype/dejavu/DejaVuSansMono-Bold.ttf"

BG = (30, 30, 30)
PANEL = (24, 24, 24)
BORDER = (70, 70, 70)
TITLE = (200, 200, 200)
TXT = (212, 212, 212)
RED = (241, 76, 76)
GREEN = (35, 209, 139)
CYAN = (17, 168, 205)
DIM = (140, 140, 140)

PANELS = [
    ("1. Compilação bloqueada pela fase ANALYZE", [
        ("$ ", GREEN, "speccompiler build docs/project.yaml", TXT),
        ("ERROR ", RED, "srs.md:27 [traceability_hlr_to_vc] High-level requirement", TXT),
        ("      ", TXT, "'AL-001' is not covered by any VC", TXT),
        ("ERROR ", RED, "svc.md:3 [traceability_vc_to_hlr] Verification case", TXT),
        ("      ", TXT, "'AL-002' has no traceability link to an HLR", TXT),
        ("ERROR ", RED, "Pipeline aborted: analysis found 2 error(s)", TXT),
    ]),
    ("2. Correção no SVC: declaração da rastreabilidade", [
        ("$ ", GREEN, "git diff docs/svc.md", TXT),
        ("  ", DIM, "## VC: Verificação do Disparo do Alarme @AL-002", DIM),
        ("  ", DIM, "", DIM),
        ("  ", DIM, "> verification_method: Test", DIM),
        ("+ ", GREEN, "", GREEN),
        ("+ ", GREEN, "> traceability: [AL-001](@)", GREEN),
    ]),
    ("3. Recompilação bem-sucedida", [
        ("$ ", GREEN, "speccompiler build docs/project.yaml", TXT),
        ("INFO  ", CYAN, "Running phase: initialize (4 context(s))", TXT),
        ("INFO  ", CYAN, "Running phase: resolve (4 context(s))", TXT),
        ("INFO  ", CYAN, "Running phase: transform (4 context(s))", TXT),
        ("INFO  ", CYAN, "Running phase: analyze (4 context(s))", TXT),
        ("INFO  ", CYAN, "Running phase: emit (4 context(s))", TXT),
        ("INFO  ", CYAN, "Generated html5: build/www/svc.html", TXT),
        ("INFO  ", CYAN, "SpecCompiler build complete. Processed 4 document(s).", GREEN),
    ]),
]

FS = 15
font = ImageFont.truetype(FONT, FS)
font_b = ImageFont.truetype(FONT_B, FS)
LH = FS + 7
PAD = 14
TITLE_H = 30
GAP = 16
W = 760

height = GAP
for _, lines in PANELS:
    height += TITLE_H + PAD * 2 + LH * len(lines) + GAP

img = Image.new("RGB", (W, height), BG)
d = ImageDraw.Draw(img)

y = GAP
for title, lines in PANELS:
    ph = TITLE_H + PAD * 2 + LH * len(lines)
    d.rounded_rectangle([GAP, y, W - GAP, y + ph], radius=8, fill=PANEL, outline=BORDER, width=1)
    d.line([GAP, y + TITLE_H, W - GAP, y + TITLE_H], fill=BORDER, width=1)
    d.text((GAP + PAD, y + 7), title, font=font_b, fill=TITLE)
    ty = y + TITLE_H + PAD
    for prefix, pcolor, rest, rcolor in lines:
        d.text((GAP + PAD, ty), prefix, font=font, fill=pcolor)
        px = d.textlength(prefix, font=font)
        d.text((GAP + PAD + px, ty), rest, font=font, fill=rcolor)
        ty += LH
    y += ph + GAP

out = sys.argv[1] if len(sys.argv) > 1 else "exemplo-sessao.png"
img.save(out)
print(f"wrote {out} ({W}x{height})")
