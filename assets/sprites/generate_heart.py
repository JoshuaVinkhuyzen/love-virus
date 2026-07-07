"""
generate_heart.py

Procedurally generates the pixel-art heart sprite used by the game
(assets/sprites/heart.png), using a mathematical heart curve rather than
hand-placed pixels, so the shape stays correctly proportioned at any size.

Requires: Python 3 + Pillow (pip install pillow)
Usage:    python generate_heart.py
Output:   heart.png in the current directory
"""

from PIL import Image, ImageDraw, ImageFont

# --- Config ---
HEART_SIZE = 40            # square grid for the heart shape itself (keeps proportions correct)
GRID_W, GRID_H = 40, 40    # final logical grid (heart centered inside, square canvas)
SCALE = 4                  # each grid cell becomes SCALE x SCALE real pixels
IMG_W, IMG_H = GRID_W * SCALE, GRID_H * SCALE

OUTLINE   = (196, 46, 84, 255)    # reddish-pink
FILL      = (255, 128, 164, 255) # pink
HIGHLIGHT = (255, 189, 209, 255) # lighter pink shading (upper-left shine)
SHADOW    = (222, 76, 112, 255)  # slightly darker pink (lower shading)
TRANSPARENT = (0, 0, 0, 0)

def heart_inside(x, y):
    # classic implicit heart curve: (x^2 + y^2 - 1)^3 - x^2*y^3 <= 0
    return (x**2 + y**2 - 1)**3 - (x**2) * (y**3) <= 0

# Build boolean grid of which logical pixels are inside the heart.
# The shape math uses a SQUARE sub-grid (HEART_SIZE x HEART_SIZE) so x and y
# are normalized by the same denominator -- this keeps the heart's natural
# proportions correct regardless of the final canvas size.
offset = (GRID_W - HEART_SIZE) // 2  # center the heart horizontally in the wider canvas
grid = [[False]*GRID_W for _ in range(GRID_H)]
for row in range(GRID_H):
    for col in range(GRID_W):
        hx = col - offset
        hy = row
        x = (hx - HEART_SIZE/2) / (HEART_SIZE/2) * 1.2
        y = (HEART_SIZE/2 - hy) / (HEART_SIZE/2) * 1.2  # flipped so point faces down
        if heart_inside(x, y):
            grid[row][col] = True

def is_outline(row, col):
    if not grid[row][col]:
        return False
    for dr, dc in [(-1,0),(1,0),(0,-1),(0,1)]:
        nr, nc = row+dr, col+dc
        if nr < 0 or nr >= GRID_H or nc < 0 or nc >= GRID_W or not grid[nr][nc]:
            return True
    return False

img = Image.new("RGBA", (IMG_W, IMG_H), TRANSPARENT)
draw = ImageDraw.Draw(img)

for row in range(GRID_H):
    for col in range(GRID_W):
        if not grid[row][col]:
            continue
        if is_outline(row, col):
            color = OUTLINE
        # elif row < GRID_H * 0.32 and col < GRID_W * 0.42:
        #     color = HIGHLIGHT
        # elif row > GRID_H * 0.72:
        #     color = SHADOW
        else:
            color = FILL
        x0, y0 = col*SCALE, row*SCALE
        draw.rectangle([x0, y0, x0+SCALE-1, y0+SCALE-1], fill=color)

# "CLICK ME" text
font = ImageFont.load_default(size=20)
text = "CLICK ME"
bbox = draw.textbbox((0,0), text, font=font)
text_w, text_h = bbox[2]-bbox[0], bbox[3]-bbox[1]
text_x = (IMG_W - text_w)//2
text_y = int(IMG_H * 0.35)
draw.text((text_x, text_y), text, font=font, fill=(255,255,255,255))

img.save("assets/sprites/heart.png")
print(f"Saved {IMG_W}x{IMG_H} image")