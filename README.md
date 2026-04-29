# 算法刷题复习系统

基于 SM-2 + Leitner 间隔重复算法的刷题复习管理平台。

## 启动方式

```bash
cd /home/michael/workspace/algorithm
python3 server.py
```

然后打开浏览器访问：
- Dashboard: http://localhost:8080
- API: http://localhost:8080/api/problems

## 添加新题目

**通过 API 添加：**
```bash
curl -X POST http://localhost:8080/api/problems \
  -H "Content-Type: application/json" \
  -d '{
    "problemId": "LC999",
    "name": "题目名称",
    "platform": "LeetCode",
    "category": "分类",
    "difficulty": "难度",
    "url": "https://leetcode.cn/problems/xxx/"
  }'
```

**通过 Dashboard 界面：** 打开 Dashboard 后使用"新增题目"表单。

## 题目目录结构

每道题目一个文件夹：
```
problems/{id}_名称/
├── main.cpp       # 你的代码（本地练习用）
├── notes.md       # 题解、代码、错误分析
└── review.json    # 复习状态
```

### 题目文件夹命名规则

#### 普通题
**格式：`{平台前缀}{题号}_{题目名称}`**

| 平台 | 前缀 | 示例 |
|------|------|------|
| LeetCode | LK | `LK1254_Number of Closed Islands` |
| 洛谷 | LG | `LG3612_前缀和`、`LG1119_灾后重建` |
| PTA | PTA | `PTA1009_N个数求和` |

#### 比赛题
**格式：`{平台前缀}{场次}{题号}_{题目名称}`**

| 平台 | 前缀 | 示例 |
|------|------|------|
| Codeforces | CF | `CF2200A`、`CF2200B`、`CF2200C` |
| 牛客网 | NK | `NK131235A`、`NK131235B` |

**注意：**
- `problemId` 全系统唯一
- 新增时检查 `platform + problemId` 组合，重复会报错
- 题目名称用中文（简短）

## 复习算法

SM-2 + Leitner 混合算法：
- Leitner 盒子：L1=1天、L2=3天、L3=7天、L4=14天、L5=30天
- 评分 q ∈ [0,5]：q≥3 答对升级，q<3 答错降回 L1
- EaseFactor 根据答题质量动态调整

## API 端点

| 端点 | 方法 | 说明 |
|------|------|------|
| `/api/problems` | GET | 所有题目 |
| `/api/problems/due` | GET | 今日待复习 |
| `/api/problems/{id}` | GET | 单题详情 |
| `/api/problems/{id}` | DELETE | 删除题目 |
| `/api/review` | POST | 提交复习评分 |
| `/api/problems` | POST | 新增题目 |
| `/api/stats` | GET | 统计信息 |

## 文件说明

- `server.py` — HTTP 服务器（Python 标准库，无外部依赖）
- `scanner.py` — 核心业务逻辑
- `dashboard.html` — 可视化前端
- `archive/` — 迁移前的旧文档备份
