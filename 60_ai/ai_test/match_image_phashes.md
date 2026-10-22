# Nominatim: a free, open-source search engine that performs forward and reverse geocoding using data from OpenStreetMap

## 1 windows 下怎么安装和部署

在 Windows 上部署 Nominatim，需要先了解一个关键背景：**官方并未正式支持 Windows**，其 CI 测试虽已覆盖 Windows，但建议“有冒险精神”的用户尝试并反馈问题。因此，目前并没有像 Linux 那样“一键式”的原生安装包，主要依赖 **Docker**、**Python 原生安装** 或 **WSL/Vagrant** 几种方案。

### 🐳 方案一：Docker Desktop（最推荐，成功率最高）

这是目前在 Windows 上部署 Nominatim **最稳妥、最省心**的方式，能有效避开 Windows 原生环境下复杂的依赖和路径问题。

#### 1. 安装 Docker Desktop

从 Docker 官网下载并安装 **Docker Desktop for Windows**，安装后启动并确保其正常运行。

#### 2. 准备 OSM 数据

从 Geofabrik 下载所需区域的 `.osm.pbf` 文件，例如以印度为例：`india-latest.osm.pbf`。建议从较小的区域（如一个省或小国家）开始测试。

#### 3. 通过 PowerShell 启动容器

以**管理员身份**打开 PowerShell，执行以下命令（需将数据文件路径替换为实际位置）：

```powershell
# 拉取镜像
docker pull mediagis/nominatim:latest

# 创建数据卷（用于持久化数据库，可选但推荐）
docker volume create nominatim-data

# 启动容器并初始化数据库
docker run -d --name nominatim `
  -v nominatim-data:/var/lib/postgresql/12/main `
  -v "C:/path/to/india-latest.osm.pbf:/data.osm.pbf" `
  -e NOMINATIM_MODE=init `
  -e NOMINATIM_PBF_URL=/data.osm.pbf `
  -e PBF_UPDATE=false `
  -e REPLICATION_URL=https://download.geofabrik.de/asia/india-updates/ `
  -e IMPORT_WIKIPEDIA=false `
  -e THREADS=4 `
  mediagis/nominatim:latest
```

> **提示**：`mediagis/nominatim` 是社区维护的镜像，文档和社区讨论中广泛使用。官方镜像的用法请参考 [Docker Hub](https://hub.docker.com/r/mediagis/nominatim)。

#### 4. 验证与使用

导入过程可能持续数小时，取决于数据大小和机器性能。可通过以下命令查看进度：

```powershell
docker logs -f nominatim
```

导入完成后，使用 `docker ps` 查看端口映射，然后在浏览器访问 `http://localhost:[端口]` 即可看到界面。

### 🐍 方案二：Python 原生安装（需自行解决依赖）

官方发布的 Python 包（`nominatim-db` 和 `nominatim-api`）理论上可以直接在 Windows 上安装。**但前提是必须先手动装好所有底层依赖**，这是整个流程中最容易出问题的环节。

#### 1. 手动安装核心依赖

在 Windows 上逐一安装以下软件，并确保其可执行文件（如 `psql`、`osm2pgsql`）被添加到系统 `PATH` 环境变量中：

- **PostgreSQL (13+)** 及 **PostGIS (3.2+)** 扩展
- **osm2pgsql (1.8+)**
- **Python 3.10+**（官方特别指明 Windows 需要 3.10 及以上版本）

#### 2. 通过 pip 安装 Nominatim

依赖就绪后，创建一个虚拟环境并在其中安装 Nominatim：

```bash
# 创建并激活虚拟环境
python -m venv nominatim-venv
nominatim-venv\Scripts\activate

# 安装核心包
pip install nominatim-db nominatim-api
```

_来源：_

#### 3. 初始化项目与导入数据

```bash
# 创建项目目录
mkdir nominatim-project
cd nominatim-project

# 导入 OSM 数据（将路径替换为你的 .pbf 文件）
nominatim import --osm-file C:\path\to\your-data.osm.pbf
```

_来源：_

#### 4. 启动 Web 服务

```bash
pip install uvicorn falcon
nominatim serve
```

_来源：_

> **注意**：原生安装需要自行处理 PostgreSQL 的调优、扩展启用、用户权限等一系列问题，**对新手极不友好**。如果选择此路，请做好遇到各种依赖错误的准备。

### 📦 方案三：Vagrant 虚拟机（最隔离）

如果不想在主力 Windows 系统中安装一堆可能冲突的依赖，可以使用 **Vagrant + VirtualBox** 在 Windows 上启动一个 Ubuntu 虚拟机，然后在虚拟机内部按照 Linux 的裸机安装步骤操作。官方文档明确指出，Vagrant 和 VirtualBox 可以正常安装在 64 位 Windows 上。这种方式环境隔离最彻底，但需要额外的虚拟机资源开销。

### ⚠️ 无论哪种方案，都需留意的核心要点

- **硬件资源是硬门槛**：Nominatim 对内存和磁盘要求很高。**最低需要 2GB RAM**（仅安装，不保证流畅运行），完整全球数据强烈建议 **128GB 以上内存**和 **1TB 以上 NVMe 磁盘空间**，全球数据导入在高端机器上也需 **约 2.5 天**。务必从**小区域数据**（如摩纳哥、单个省份）开始测试。
- **磁盘性能至关重要**：Nominatim 的核心是数据库随机读写，官方文档强调**快盘是必须的，推荐 NVMe**。如果在 Windows 上使用 WSL2 或虚拟机，确保虚拟磁盘文件存放在 SSD 上。
- **WSL2 是可行的折中方案**：有用户反馈在 Windows + WSL2 环境下成功运行过 Nominatim（虽在 HDD 上性能受限）。如果你熟悉 Linux 命令，在 WSL2 中按 Linux 方式部署，可以结合 Windows 的易用性和 Linux 的兼容性。

### 💎 总结

| 你的情况                                          | 推荐方案                 | 核心理由                                                                                               |
| :------------------------------------------------ | :----------------------- | :----------------------------------------------------------------------------------------------------- |
| **绝大多数 Windows 用户**                         | **Docker Desktop**       | 路径最平滑，社区验证充分，能规避大量 Windows 原生环境特有的坑。                                        |
| **开发者，希望直接在 Windows 上调试 Python 代码** | **Python 原生安装**      | 可直接在 IDE 中调试，但**必须自行解决 PostgreSQL/PostGIS/osm2pgsql 的 Windows 安装与配置**，挑战较大。 |
| **不想污染主机环境，愿意使用虚拟机**              | **Vagrant + VirtualBox** | 环境完全隔离，可复用 Linux 部署经验。                                                                  |
| **熟悉 Linux，想在 Windows 上获得接近原生的体验** | **WSL2**                 | 在 Windows 内运行一个完整的 Linux 内核，兼容性好，性能优于传统虚拟机。                                 |

## 2 安装前置依赖的详细步骤

在 Windows 上为 Nominatim 手动安装前置依赖，核心是三个组件：**PostgreSQL、PostGIS 和 osm2pgsql**。其中 **osm2pgsql 是 `pip` 不会自动安装的关键项**，也最可能是之前 `nominatim import` 失败的根源。下面按顺序逐一完成安装与配置。

---

### 🐘 第一步：安装 PostgreSQL（数据库引擎）

Nominatim 要求 PostgreSQL **13 或更高版本**，推荐直接从 EnterpriseDB 获取 Windows 安装器。

1. 访问 PostgreSQL 官方 Windows 下载页：`https://www.postgresql.org/download/windows/`，点击进入 EnterpriseDB 的下载页面，获取与你的系统架构（64 位）匹配的 **.exe 安装包**。
2. 运行安装向导，注意以下几个关键设置：
   - **超级用户密码**：为 `postgres` 用户设置密码，务必记住，后续配置 Nominatim 时会用到。
   - **端口**：保持默认 **5432**（如果本机已有其他 PostgreSQL 实例占用该端口，需记下新端口）。
   - **安装路径**：默认通常为 `C:\Program Files\PostgreSQL\<版本号>`，建议保持默认，便于后续定位。
3. 安装完成后，**必须将 PostgreSQL 的 `bin` 目录添加到系统 `PATH`**。默认路径类似 `C:\Program Files\PostgreSQL\16\bin`（版本号以实际安装为准）。这一步是让 `psql`、`createdb` 等命令在任意命令行窗口中可直接调用的前提。
4. 验证安装：**打开一个全新的命令行窗口**（使 PATH 生效），执行：

```bash
psql --version
```

如果输出 `psql (PostgreSQL) 16.x` 之类的版本信息，说明 PostgreSQL 已就绪。

---

### 🗺️ 第二步：安装 PostGIS（空间数据库扩展）

PostGIS 是 PostgreSQL 的扩展，赋予其空间数据类型和函数。Nominatim 要求 **PostGIS 3.0+**。Windows 上有两种安装方式，**任选其一即可**。

#### 方式 A：通过 Stack Builder 安装（与 PostgreSQL 安装器集成）

如果你在安装 PostgreSQL 时保留了“启动 Stack Builder”选项，可以直接用它安装 PostGIS：

1. 从开始菜单启动 **Stack Builder**，在下拉列表中选择刚安装的 PostgreSQL 实例。
2. 在组件列表中展开 **“Spatial Extensions”** 节点，勾选 **PostGIS** 对应的版本，按向导完成下载和安装。

#### 方式 B：从 OSGeo 下载独立 Bundle（更直接）

如果 Stack Builder 不可用或你希望手动控制，从 OSGeo 下载对应版本的 PostGIS Bundle：

1. 访问 `https://download.osgeo.org/postgis/windows/`，进入与你的 PostgreSQL 主版本号匹配的目录（例如 PostgreSQL 16 对应 `pg16` 目录）。
2. 下载形如 `postgis-bundle-pg16x64-setup-x.x.x.exe` 的安装程序，运行并按默认选项完成安装。

#### 验证 PostGIS 是否可用

安装完成后，**还不是“启用”状态**。需要用 `psql` 连接到 PostgreSQL，在目标数据库中显式启用扩展：

```sql
CREATE EXTENSION postgis;
```

随后用以下查询确认 PostGIS 已出现在可用扩展列表中：

```sql
SELECT * FROM pg_available_extensions WHERE name = 'postgis';
```

如果能查到记录（`installed_version` 可能为空，表示尚未在**当前库**中启用，但扩展本身已就绪），说明 PostGIS 安装成功。

---

### ⚙️ 第三步：安装 osm2pgsql（最关键的缺失项）

**`pip install nominatim-db` 不会安装 `osm2pgsql`**，但 `nominatim import` 必须调用它来读取 `.pbf` 文件并写入数据库。Windows 上使用**预编译二进制包**即可，无需编译。

1. 前往 osm2pgsql 官方文档的 Windows 安装页：`https://osm2pgsql.org/doc/install/windows.html`，获取预编译二进制包的下载链接（或从其 GitHub Releases 页面下载 `osm2pgsql.zip` 之类的压缩包）。
2. 将 ZIP 文件解压到一个**路径简单、无空格**的目录，例如 `C:\osm2pgsql\`。解压后应能看到 `osm2pgsql.exe`。
3. **将该目录添加到系统 `PATH`**。这是让 `nominatim import` 能在子进程中找到 `osm2pgsql` 的必要条件。
4. **验证**：打开一个全新的命令行窗口，运行：

```bash
osm2pgsql --version
```

必须看到版本号 **≥ 1.8** 的输出。如果命令找不到，说明 PATH 未生效或目录配错。

---

### ✅ 汇总检查清单（在同一命令行窗口中逐项执行）

完成上述安装后，**不要复用之前的旧窗口**，新开一个命令行，依次运行以下命令，确保三项全部通过：

| 检查项     | 命令                                           | 通过标准              |
| :--------- | :--------------------------------------------- | :-------------------- |
| PostgreSQL | `psql --version`                               | 输出 `13` 或更高版本  |
| PostGIS    | 连接到数据库后执行 `SELECT PostGIS_Version();` | 输出 PostGIS 版本号   |
| osm2pgsql  | `osm2pgsql --version`                          | 输出 `1.8` 或更高版本 |

三项全部确认后，再回到 Nominatim 项目目录，设置 `PYTHONUTF8=1` 并配置 `NOMINATIM_DATABASE_DSN`，然后重新执行 `nominatim import`。之前导入失败的首要原因，通常就是 **`osm2pgsql` 未安装或未加入 PATH**，其次是 Windows 下的 UTF-8 编码问题。

## 3 导入 PBF 数据文件

```bash
cd D:\Jackie\Art\Nominatim\Project
# python.exe ..\..\Art-of-Algorithm\.venv-pytorch\Scripts\nominatim import --osm-file "E:\Jackie\Nominatim\morocco-261017.osm.pbf"

python -c "import asyncio,sys; asyncio.set_event_loop_policy(asyncio.WindowsSelectorEventLoopPolicy()); from nominatim_db import cli; sys.argv=['nominatim','import','--osm-file',r'E:\Jackie\Nominatim\antarctica-261016.osm.pbf']; raise SystemExit(cli.nominatim())"

python -c "import asyncio,sys; asyncio.set_event_loop_policy(asyncio.WindowsSelectorEventLoopPolicy()); from nominatim_db import cli; sys.argv=['nominatim','import','--osm-file',r'E:\Jackie\Nominatim\africa-261017.osm.pbf','--osm-file',r'E:\Jackie\Nominatim\asia-261017.osm.pbf','--osm-file',r'E:\Jackie\Nominatim\north-america-latest.osm.pbf']; raise SystemExit(cli.nominatim())"

# 刷新邮政编码数据（如果你的新数据包含邮编，这步是必要的）
python -c "import asyncio,sys; asyncio.set_event_loop_policy(asyncio.WindowsSelectorEventLoopPolicy()); from nominatim_db import cli; sys.argv=['nominatim','refresh','--postcodes']; raise SystemExit(cli.nominatim())"

# 重建索引，-j 参数指定线程数以加速
python -c "import asyncio,sys; asyncio.set_event_loop_policy(asyncio.WindowsSelectorEventLoopPolicy()); from nominatim_db import cli; sys.argv=['nominatim','index','-j','4']; raise SystemExit(cli.nominatim())"

# python.exe ..\..\Art-of-Algorithm\.venv-pytorch\Scripts\nominatim serve

python -c "import asyncio,sys; asyncio.set_event_loop_policy(asyncio.WindowsSelectorEventLoopPolicy()); from nominatim_db import cli; sys.argv=['nominatim','serve']; raise SystemExit(cli.nominatim())"
```

### Error - loading lua config

```bash
...te-packages\nominatim_db\resources\lib-lua\flex-base.lua:5: attempt to concatenate a nil value.
```

这次不是 .env 配置缺失，而是 Lua 脚本处理 Windows 路径时出错。flex-base.lua 用 match("(.*/)") 从文件路径提取目录，只识别 /；实际路径是 D:\...，匹配结果为 nil，随后拼接时报错。

可靠的方案是在 WSL2/Linux 下运行 Nominatim。若要先尝试修补当前 Windows 环境，在 flex-base.lua:4 把路径反斜杠转成正斜杠：

```lua
local topic_file = debug.getinfo(1, "S").source:sub(2):gsub("\\", "/"):match("(.*/)") .. 'themes/nominatim/topics/'.. name .. '.lua'
```

这只处理当前报错，不能保证 Nominatim 在 Windows 上的其他步骤也兼容。另外，本次失败前数据库已创建；修补后不要直接重跑原命令，否则可能因数据库已存在而失败。清理本次导入创建的数据库后再重新导入，或改在 WSL/Linux 中重新建库。

### Error - Load data into placex table

```bash
psycopg.InterfaceError: Psycopg cannot use the 'ProactorEventLoop' to run in async mode. Please use a compatible event loop, for instance by setting 'asyncio.set_event_loop_policy(WindowsSelectorEventLoopPolicy())'
```

这次 PBF 已经被 osm2pgsql 成功读入；失败发生在后续异步加载数据库时。错误原因是 Windows 默认的 ProactorEventLoop 与 psycopg 异步连接不兼容。

在当前 Project 目录运行下面命令：它会切换到兼容的 WindowsSelectorEventLoopPolicy，并从 load-data 阶段继续，不必重新读 PBF：

```bash
& ..\..\Art-of-Algorithm\.venv-pytorch\Scripts\python.exe -c "import asyncio,sys; asyncio.set_event_loop_policy(asyncio.WindowsSelectorEventLoopPolicy()); from nominatim_db import cli; sys.argv=['nominatim','import','--continue','load-data']; raise SystemExit(cli.nominatim())"
```

### Error - Waiting for application startup

```bash
psycopg.InterfaceError: Psycopg cannot use the 'ProactorEventLoop' to run in async mode. Please use a compatible event loop, for instance by setting 'asyncio.set_event_loop_policy(WindowsSelectorEventLoopPolicy())'
```

这次是同一个 Windows 事件循环兼容问题，只是发生在 serve 启动时连接数据库。可以在调用 Nominatim CLI 前先设置 WindowsSelectorEventLoopPolicy；我给你一条保持当前 Project 工作目录的 PowerShell 命令。

serve 启动时也用了 psycopg 异步连接，因此遇到同样的 ProactorEventLoop 不兼容错误。在当前 Project 目录执行下面命令，先设置兼容的事件循环策略再启动服务：

```bash
python -c "import asyncio,sys; asyncio.set_event_loop_policy(asyncio.WindowsSelectorEventLoopPolicy()); from nominatim_db import cli; sys.argv=['nominatim','serve']; raise SystemExit(cli.nominatim())"
```
