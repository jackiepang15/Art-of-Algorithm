#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import markdown
from markdown.extensions.extra import ExtraExtension
from markdown.extensions.codehilite import CodeHiliteExtension
from PIL import Image, ImageDraw, ImageFont
from io import BytesIO
import matplotlib.pyplot as plt
import numpy as np
import re

# 第一讲最后一道例题（不包含解答过程和提示）
example_content = """【例 5】数一数，需要多少块砖才能把坏了的墙补好?

题目描述：
在下面的图中，有一面墙被打破了，需要用砖块来修补。
"""

# 定义公式和内容渲染
def render_latex(content):
    """渲染LaTeX公式"""
    # 将 $$...$$ 和 $...$ 格式的LaTeX公式转换为matplotlib公式
    content = re.sub(r'\$\$(.*?)\$\$', r'$$ \1 $$', content)
    content = re.sub(r'\$(.*?)\$', r'$$ \1 $$', content)
    return content

def create_example_image():
    """创建例题图片"""

    # 创建画布
    fig = plt.figure(figsize=(10, 6), dpi=150)
    ax = fig.add_subplot(111)

    # 设置中文字体
    plt.rcParams['font.sans-serif'] = ['SimHei', 'Microsoft YaHei', 'Arial Unicode MS']
    plt.rcParams['axes.unicode_minus'] = False

    # 标题
    ax.text(0.5, 0.95, example_content,
            ha='center', va='center',
            fontsize=24, fontweight='bold',
            transform=ax.transAxes)

    # 添加说明文字
    ax.text(0.5, 0.90, '数学题图片示例',
            ha='center', va='center',
            fontsize=14, style='italic',
            transform=ax.transAxes,
            color='gray')

    # 添加装饰性边框
    rect = plt.Rectangle((0.1, 0.1), 0.8, 0.8,
                        linewidth=3, edgecolor='#4CAF50', facecolor='none')
    ax.add_patch(rect)

    # 添加角标
    corners = [(0.1, 0.1), (0.1, 0.9), (0.9, 0.9), (0.9, 0.1)]
    for corner in corners:
        ax.text(corner[0], corner[1], 'Math Problem',
                ha='center', va='center',
                fontsize=10, fontweight='bold',
                color='#4CAF50')

    # 设置坐标轴
    ax.set_xlim(0, 1)
    ax.set_ylim(0, 1)
    ax.axis('off')

    # 保存图片
    output_path = r'D:\Jackie\Art\Art-of-Algorithm\60_ai\pdf2md\example_5_image.png'
    plt.tight_layout()
    plt.savefig(output_path, dpi=150, bbox_inches='tight', facecolor='white')
    print(f"图片已保存到: {output_path}")

    plt.close()

if __name__ == "__main__":
    create_example_image()
