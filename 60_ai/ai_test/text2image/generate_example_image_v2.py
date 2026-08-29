#!/usr/bin/env python3
"""
Generate an image for the first lecture's last example (例 5)
"""
from PIL import Image, ImageDraw, ImageFont
import os

# Paths
base_dir = r"D:\Jackie\Art\wiki\3_Work_Experience\3_3_Study_Notes"
image_dir = os.path.join(base_dir, "images", "math_1_3")
example_image_path = os.path.join(image_dir, "7c80905e8e4cd4636f839fb7251b9627eff052d83397b2ceff444f884a7d0d78.jpg")
output_path = os.path.join(base_dir, "lecture1_example5.png")

# Load the example image
example_img = Image.open(example_image_path)

# Resize example image if too large (max width 800px)
max_width = 800
if example_img.width > max_width:
    ratio = max_width / example_img.width
    new_height = int(example_img.height * ratio)
    example_img = example_img.resize((max_width, new_height), Image.Resampling.LANCZOS)

# Create a new image with white background
# Calculate total height needed
padding = 40
title_height = 80
gap = 20
total_width = max(example_img.width, 900) + 2 * padding
total_height = padding + title_height + gap + example_img.height + padding

# Create canvas
canvas = Image.new('RGB', (total_width, total_height), 'white')
draw = ImageDraw.Draw(canvas)

# Try to load a Chinese font
font_paths = [
    "C:/Windows/Fonts/msyh.ttc",  # Microsoft YaHei
    "C:/Windows/Fonts/simhei.ttf",  # SimHei
    "C:/Windows/Fonts/msyh.ttf",
]
font = None
for fp in font_paths:
    if os.path.exists(fp):
        try:
            font = ImageFont.truetype(fp, 36)
            break
        except:
            continue

if font is None:
    font = ImageFont.load_default()

# Draw title
title_text = "【例 5】数一数，需要多少块砖才能把坏了的墙补好？"
# Center the title
bbox = draw.textbbox((0, 0), title_text, font=font)
text_width = bbox[2] - bbox[0]
text_x = (total_width - text_width) // 2
text_y = padding + (title_height - (bbox[3] - bbox[1])) // 2
draw.text((text_x, text_y), title_text, font=font, fill='black')

# Paste example image centered horizontally
img_x = (total_width - example_img.width) // 2
img_y = padding + title_height + gap
canvas.paste(example_img, (img_x, img_y))

# Save
canvas.save(output_path, "PNG")
print(f"Saved to {output_path}")
print(f"Image size: {canvas.width}x{canvas.height}")
