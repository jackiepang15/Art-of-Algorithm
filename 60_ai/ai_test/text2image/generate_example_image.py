import os
import base64
from PIL import Image, ImageDraw, ImageFont
import re

# 获取工作目录
base_dir = r"D:\Jackie\Art\wiki"
images_dir = os.path.join(base_dir, "images", "math_1_3")
output_path = os.path.join(base_dir, "example_5_output.jpeg")

# 第1讲【例 5】的内容提取：
# 题目文字：数一数，需要多少块砖才能把坏了的墙补好?
# 图片文件：7c80905e8e4cd4636f839fb7251b9627eff052d83397b2ceff444f884a7d0d78.jpg

# 查找图片文件
image_filename = "7c80905e8e4cd4636f839fb7251b9627eff052d83397b2ceff444f884a7d0d78.jpg"
image_path = os.path.join(images_dir, image_filename)

if not os.path.exists(image_path):
    print(f"图片文件不存在: {image_path}")
    print("可用图片文件:")
    for f in os.listdir(images_dir):
        print(f"  {f}")
    exit(1)

# 加载背景图片
try:
    bg_image = Image.open(image_path)
except Exception as e:
    print(f"打开图片失败: {e}")
    exit(1)

# 创建一个更大的图片来容纳文字和图片
# 设置图片宽度（带一些边距）
img_width = bg_image.width + 100
# 预估图片高度（带上方文字空间）
img_height = bg_image.height + 150

# 创建新图片（白色背景）
output_image = Image.new('RGB', (img_width, img_height), 'white')
draw = ImageDraw.Draw(output_image)

# 尝试加载中文字体
try:
    # 常见中文字体路径
    font_paths = [
        r"C:\Windows\Fonts\msyh.ttc",  # 微软雅黑
        r"C:\Windows\Fonts\simhei.ttf",  # 黑体
        r"C:\Windows\Fonts\simsun.ttc",  # 宋体
    ]
    font = None
    for fp in font_paths:
        if os.path.exists(fp):
            try:
                font = ImageFont.truetype(fp, 20)
                break
            except:
                continue
    if font is None:
        font = ImageFont.load_default()
except:
    font = ImageFont.load_default()

# 添加标题文字
title_text = "数一数，需要多少块砖才能把坏了的墙补好?"
# 计算文字高度
txt_bbox = draw.textbbox((0, 0), title_text, font=font)
txt_height = txt_bbox[3] - txt_bbox[1]
txt_width = txt_bbox[2] - txt_bbox[0]

# 绘制标题文字（居中偏上）
title_start_y = 10
title_start_x = (img_width - txt_width) // 2

draw.text((title_start_x, title_start_y), title_text, fill='black', font=font)

# 将原图片粘贴到输出图片的适当位置
offset_x = 50
offset_y = title_start_y + txt_height + 20
output_image.paste(bg_image, (offset_x, offset_y))

# 保存图片
output_image.convert('RGB').save(output_path, 'JPEG', quality=95)
print(f"图片已保存到: {output_path}")
print(f"图片尺寸: {output_image.size}")
