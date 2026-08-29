# AI

## Test

- Human Intelligence
- Artificial Intelligence

## Tools

PDF to Markdown

- Step 1: Install MinerU

```bash
pip install --upgrade pip
pip install uv
uv pip install -U "mineru[all]"

python -m pip install lmdeploy==0.11.1

# pip install torch==2.8.0 torchvision==0.23.0 torchaudio==2.8.0 --index-url https://download.pytorch.org/whl/cu128
# python -m pip install D:/Jackie/Downloads/torch-2.8.0+cu128-cp310-cp310-win_amd64.whl
pip install torch==2.8.0 torchvision==0.23.0 torchaudio==2.8.0 -i https://tsinghua.edu.cn --find-links https://mirrors.aliyun.com/pytorch-wheels/cu128
python -c "import torch; print(torch.cuda.is_available()); print(torch.cuda.get_device_name(0) if torch.cuda.is_available() else 'No GPU found')"

mineru -p math_1.pdf  -o ./output
```

- Step 2: Remove HTML tags

```bash
python D:\Jackie\Art\Art-of-Algorithm\99_others\clean_html.py --input_path D:\Jackie\Art\wiki\3_Work_Experience\3_3_Study_Notes\life_math_6.md --output_path D:\Jackie\Art\wiki\3_Work_Experience\3_3_Study_Notes\life_math_6_cleaned.md --tags details
```

- Step 3: Fix typos

```bash
del the first page
add # 奥数教程
del 微信公众号 教辅资料站
rep \n## -> \n###
rep \n### 致读者 -> \n## 致读者
rep \n### 前言 -> \n## 前言
rep \n### 目录 -> \n## 目录
rep \n### 参考答案 -> \n## 参考答案
rep \n### 第([0-9 ]+)讲 -> \n## 第$1讲
```

## References

### Agent

Github

- MCP: <https://github.com/modelcontextprotocol>

Courses

- 20分钟教会你用CherryStudio+MCP搭建自动化AI智能体+本地知识库
  - <https://www.bilibili.com/video/BV1LVedzDE3V>
- 从零编写MCP并发布上线，超简单！手把手教程
  - <https://www.bilibili.com/video/BV1RNTtzMENj>
- MCP: Build Rich-Context AI Apps with Anthropic
  - <https://learn.deeplearning.ai/courses/mcp-build-rich-context-ai-apps-with-anthropic/>

### LLM

Courses

- DeepSeek+RAGFlow构建个人知识库
  - <https://www.bilibili.com/video/BV1WiP2ezE5a>

### Deep Learning

Courses

- Deep Learning Specialization
  - <https://www.coursera.org/specializations/deep-learning/>
