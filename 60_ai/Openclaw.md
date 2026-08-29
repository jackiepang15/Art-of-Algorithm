# OpenClaw

## Ubuntu

* DEB822: /etc/apt/sources.list.d/ubuntu.sources

```bash
Types: deb
URIs: https://mirrors.tuna.tsinghua.edu.cn/ubuntu
Suites: resolute resolute-updates resolute-backports
Components: main restricted universe multiverse
Signed-By: /usr/share/keyrings/ubuntu-archive-keyring.gpg
```

```bash
sudo apt update
sudo apt install -y nodejs
nodejs -v

pip3 install playwright --break-system-packages

# 1) Persist the override
echo 'export PLAYWRIGHT_HOST_PLATFORM_OVERRIDE=ubuntu24.04-x64' >> ~/.bashrc
source ~/.bashrc

# 2) Install browsers (works for chromium, firefox, webkit)
npx playwright install chromium

# 3) Install runtime libs — Ubuntu 26 ships t64 lib variants (y2038 transition)
sudo apt install -y \
  libnss3 libnspr4 \
  libatk1.0-0t64 libatk-bridge2.0-0t64 libatspi2.0-0t64 \
  libcups2t64 \
  libxkbcommon0 libxcomposite1 libxdamage1 libxfixes3 libxrandr2 \
  libgbm1 libdrm2 \
  libpango-1.0-0 libcairo2 \
  libasound2t64 libwayland-client0

# 4) Smoke test
node -e 'const{chromium}=require("playwright");(async()=>{const b=await chromium.launch();console.log("OK");await b.close();})();'

sudo apt install -y curl
curl -fsSL https://openclaw.ai/install.sh | bash
```

* Proxy - .bashrc

```bash
export HOST_IP=127.0.0.1
export PROXY_PORT=1088
export ALL_PROXY="http://$HOST_IP:$PROXY_PORT"
export http_proxy="http://$HOST_IP:$PROXY_PORT"
export https_proxy="http://$HOST_IP:$PROXY_PORT"
```

## Ollama

* qwen3.6:35b
  * contextWindow: 131072
  * maxTokens: 8192
* gemma4:26b
* gemma4:12b
* qwen3.5:9b

```bash
NAME                                                    ID              SIZE     PROCESSOR          CONTEXT    UNTIL
modelscope.cn/unsloth/qwen3.6:35b_q3_k_m                459faab7c506    18 GB    41%/59% CPU/GPU    131072     Forever
NAME                                                    ID              SIZE     PROCESSOR          CONTEXT    UNTIL
gemma4:26b                                              5571076f3d70    18 GB    46%/54% CPU/GPU    131072     Forever
NAME                                                    ID              SIZE     PROCESSOR          CONTEXT    UNTIL
modelscope.cn/unsloth/gemma-4-26B-A4B-it-GGUF:latest    5970ee2fff85    18 GB    47%/53% CPU/GPU    131072     Forever
NAME                                                    ID              SIZE     PROCESSOR          CONTEXT    UNTIL
modelscope.cn/unsloth/gemma-4-26B-A4B-it-GGUF:q3_k_m    52b666ed2b23    14 GB    31%/69% CPU/GPU    131072     Forever
NAME                                                    ID              SIZE     PROCESSOR          CONTEXT    UNTIL
modelscope.cn/unsloth/gemma-4-26B-A4B-it-GGUF:q2_k_xl   368db1f6f76c    12 GB    18%/82% CPU/GPU    131072     Forever
NAME                                                    ID              SIZE     PROCESSOR          CONTEXT    UNTIL
modelscope.cn/unsloth/gemma-4-26B-A4B-it-GGUF:iq2_m     e713dabc838b    11 GB    14%/86% CPU/GPU    131072     Forever
NAME                                                    ID              SIZE     PROCESSOR          CONTEXT    UNTIL
gemma4:12b                                              4eb23ef187e2    8.0 GB   100% GPU           131072     Forever
NAME                                                    ID              SIZE     PROCESSOR          CONTEXT    UNTIL
modelscope.cn/unsloth/gemma-4-12b-it-GGUF:latest        d30b707b1672    7.8 GB   100% GPU           131072     Forever
```

## Models

```bash
pip install modelscope
modelscope download --model Qwen/Qwen3.6-35B-A3B --local_dir ./Qwen3.6-35B-A3B
```

## Fonts

```bash
sudo apt install -y fonts-noto-cjk
```

## Reset

```bash
 # 重置显卡驱动（最快捷的免重启方法）快捷键
 Win + Ctrl + Shift + B
```

## Configuration

* models.providers.ollama

```json
"baseUrl": "http://127.0.0.1:11434",
"api": "ollama",
"apiKey": "OLLAMA_API_KEY",
```

* agents.defaults
  * compaction.reserveTokensFloor
  * heartbeat.every
  * memorySearch.model

```json
"compaction": {
    "mode": "safeguard",
    "reserveTokensFloor": 40000
},
"heartbeat": {
    "every": "120m",
    "target": "last"
},
"memorySearch": {
  "provider": "ollama",
  "model": "nomic-embed-text"
}
```

* browser

```bash
google-chrome --disable-gpu --disable-software-rasterizer
```

```json
"enabled": true,
"executablePath": "/usr/bin/google-chrome-stable",
"headless": true,
"noSandbox": true,
"defaultProfile": "openclaw",
"ssrfPolicy": {
  "dangerouslyAllowPrivateNetwork": true
}
```

```bash
openclaw browser --browser-profile openclaw start
openclaw browser --browser-profile openclaw set viewport 1920 1080
openclaw browser --browser-profile openclaw open https://baidu.com
openclaw browser --browser-profile openclaw navigate https://bing.com
openclaw browser --browser-profile openclaw screenshot --full-page --type jpeg
openclaw browser --browser-profile openclaw stop

请 1）用 openclaw browser navigate 切换到 https://baidu.com 这个网页；2）用 openclaw browser screenshot --full-page --type jpeg 截个图；3）把这个图片用MEDIA: 开头的绝对路径表示，并在聊天面板中将其转为图片流，实现内联预览。
```

```bash
http://127.0.0.1:18789/__openclaw__/assistant-media?source=/home/jackie/.openclaw/workspace/baidu-screenshot.png&token=fU48WsKau4CUcCjaq44lZZDniIQYCZHYVxHvMObEn3I
```

* tools
  * web_search: disable ollama
  * fetch: allowRfc2544BenchmarkRange

```json
"search": {
  "provider": "ollama",
  "enabled": false
},
"fetch": {
  "enabled": true,
  "ssrfPolicy": {
    "allowRfc2544BenchmarkRange": true
  }
}
```

* skills
  * multi-search-engine: enable

```bash
openclaw hooks enable self-improvement
```

```json
"entries": {
  "multi-search-engine": {
    "enabled": true,
  }
}
```

* channels
  * feishu
  * wecom

```bash
vi ~/.openclaw/npm/node_modules/@wecom/wecom-openclaw-plugin/openclaw.plugin.json

vi ~/.openclaw/npm/node_modules/@openclaw/feishu/openclaw.plugin.json
```

```json
"wecom": {
  "enabled": true,
  "botId": "aibduPHGUktVpTbGNPUXNapRJRRLUkzLSif",
  "secret": "KXxRppDflIu4RzmezO1UXIRvB6g0CXERBVdsdMhK6E0"
},
"feishu": {
  "enabled": true,
  "appId": "cli_a9741f36f57b9bb4",
  "appSecret": {
    "source": "file",
    "provider": "lark-secrets",
    "id": "/lark/appSecret"
  },
  "domain": "feishu",
  "connectionMode": "websocket",
  "requireMention": true,
  "dmPolicy": "allowlist",
  "allowFrom": [
    "ou_e2cd3729eb8fcce91b5c470a51da7b8b"
  ],
  "groupAllowFrom": [
    "ou_e2cd3729eb8fcce91b5c470a51da7b8b"
  ],
  "groupPolicy": "open",
  "groups": {
    "*": {
      "enabled": true
    }
  },
  "streaming": true,
  "footer": {
    "elapsed": true,
    "status": true
  }
}
```

QClaw Auto Start

* powershell.exe -WindowStyle Hidden -File "D:\Scripts\start_qclaw.ps1"

```bash
$qclaw = Get-ChildItem -Path "D:\Portable\QClaw" -Filter "qclaw.exe" -Recurse | Sort-Object LastWriteTime -Descending | Select-Object -First 1
if ($qclaw) { Start-Process $qclaw.FullName }
```

Google Chrome

```bash
google-chrome --headless --load-extension=/home/jackie/opencli-extension --disable-gpu --enable-logging --v=1 --enable-extension-activity-logging
```

## References

* [Bilibili - 龙虾退散潮，我做了一期OpenClaw理性入门教程](https://www.bilibili.com/video/BV1TxwQz5E4B)
  * [OpenClaw 安装、部署 & 使用教程](https://my.feishu.cn/wiki/LuRMwMOYviKhVHkaTq7cpdx3nEN)
* Channels
  * [penClaw飞书官方插件上线｜一文讲清功能、安装更新教程与常见问题！](https://www.feishu.cn/content/article/7613711414611463386)
  * [OpenClaw如何接入企业微信智能机器人](https://open.work.weixin.qq.com/help2/pc/21657)
