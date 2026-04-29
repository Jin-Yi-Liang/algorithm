"""
迁移脚本：从 LEETCODE_NOTES.md + REVIEW_TRACKING.md 迁移到新结构
运行一次即可，之后用 scanner.py 管理
"""

import json
import os
import re
import shutil
from datetime import date, timedelta

PROBLEMS_DIR = os.path.join(os.path.dirname(__file__), "problems")
BOX_INTERVALS = {1: 1, 2: 3, 3: 7, 4: 14, 5: 30}


def _make_url(problemId: str, platform: str) -> str:
    if "LeetCode" in platform or problemId.startswith("LC") or problemId.startswith("LCR"):
        num = problemId.replace("LC", "").replace("LCR", "")
        return f"https://leetcode.cn/problems/{num}/" if "CN" in platform else f"https://leetcode.com/problems/{num}/"
    if "洛谷" in platform or problemId.startswith("P"):
        num = problemId.replace("P", "")
        return f"https://www.luogu.com.cn/problem/P{num}"
    return ""

# ── 所有题目元数据（手工整理自 LEETCODE_NOTES.md） ──────────────────────────
PROBLEMS = [
    {
        "problemId": "LC256",
        "name": "粉刷房子",
        "platform": "LeetCode",
        "category": "动态规划",
        "difficulty": "简单",
        "reviewCount": 6,
        "lastReview": "2026-03-02",
        "nextReview": "2026-04-02",
        "errors": "无",
        "notes": "n 栋房子，三种颜色，相邻不能同色，求最小成本\n\ndp[i][c] = 刷到第 i 栋房子，第 i 栋刷颜色 c 的最小成本\n\n从后往前 DP，最后取三种颜色的最小值。",
        "code": '''
class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        int n = costs.size();
        if (n == 0) return 0;
        vector<vector<int>> dp(n, vector<int>(3));
        for (int c = 0; c < 3; c++) dp[n-1][c] = costs[n-1][c];
        for (int i = n-2; i >= 0; i--) {
            for (int c = 0; c < 3; c++) {
                dp[i][c] = costs[i][c] + min(dp[i+1][(c+1)%3], dp[i+1][(c+2)%3]);
            }
        }
        return min({dp[0][0], dp[0][1], dp[0][2]});
    }
};'''
    },
    {
        "problemId": "LC547",
        "name": "省份数量",
        "platform": "LeetCode",
        "category": "图论-并查集",
        "difficulty": "中等",
        "reviewCount": 16,
        "lastReview": "2026-03-05",
        "nextReview": "2026-04-05",
        "errors": "无",
        "notes": "n 个城市相连，求省份数量。并查集裸题。",
        "code": '''
class UnionFind {
    vector<int> parent, rank;
public:
    UnionFind(int n) { parent.resize(n); rank.assign(n, 0); iota(parent.begin(), parent.end(), 0); }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    void unite(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return;
        if (rank[ra] < rank[rb]) swap(ra, rb);
        parent[rb] = ra;
        if (rank[ra] == rank[rb]) rank[ra]++;
    }
};
class Solution {
public:
    int findCircleNum(vector<vector<int>>& is) {
        int n = is.size();
        UnionFind uf(n);
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (is[i][j]) uf.unite(i, j);
        unordered_set<int> s;
        for (int i = 0; i < n; i++) s.insert(uf.find(i));
        return s.size();
    }
};'''
    },
    {
        "problemId": "LC1135",
        "name": "最低成本建网络",
        "platform": "LeetCode",
        "category": "图论-MST",
        "difficulty": "中等",
        "reviewCount": 1,
        "lastReview": "2026-03-06",
        "nextReview": "2026-03-24",
        "errors": "无",
        "notes": "Kruskal 求 MST模板题。",
        "code": '''
class DSU {
    vector<int> parent, rank;
public:
    DSU(int n) { parent.resize(n); rank.assign(n, 0); iota(parent.begin(), parent.end(), 0); }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    bool unite(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return false;
        if (rank[ra] < rank[rb]) swap(ra, rb);
        parent[rb] = ra;
        if (rank[ra] == rank[rb]) rank[ra]++;
        return true;
    }
};
class Solution {
public:
    int minimumCost(int n, vector<vector<int>>& edges) {
        sort(edges.begin(), edges.end(), [](auto& a, auto& b){ return a[2] < b[2]; });
        DSU dsu(n);
        int cnt = 0, ans = 0;
        for (auto& e : edges) {
            if (dsu.unite(e[0], e[1])) {
                ans += e[2];
                if (++cnt == n - 1) break;
            }
        }
        return cnt == n - 1 ? ans : -1;
    }
};'''
    },
    {
        "problemId": "LC841",
        "name": "钥匙和房间",
        "platform": "LeetCode",
        "category": "图论-BFS",
        "difficulty": "简单",
        "reviewCount": 7,
        "lastReview": "2026-03-06",
        "nextReview": "2026-04-06",
        "errors": "无",
        "notes": "n 个房间有钥匙，从 0 号房间开始 BFS，能否打开所有房间。",
        "code": '''
class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size();
        vector<int> visited(n, 0);
        queue<int> q;
        q.push(0); visited[0] = 1;
        while (!q.empty()) {
            int room = q.front(); q.pop();
            for (int key : rooms[room]) {
                if (!visited[key]) { visited[key] = 1; q.push(key); }
            }
        }
        for (int v : visited) if (!v) return false;
        return true;
    }
};'''
    },
    {
        "problemId": "LC802",
        "name": "找到最终的安全状态",
        "platform": "LeetCode",
        "category": "图论-拓扑排序",
        "difficulty": "中等",
        "reviewCount": 14,
        "lastReview": "2026-03-05",
        "nextReview": "2026-04-05",
        "errors": "无",
        "notes": "安全节点：从该节点出发不会走到环。拓扑排序逆向删除法。",
        "code": '''
class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> outDeg(n);
        vector<vector<int>> rev(n);
        for (int i = 0; i < n; i++) {
            outDeg[i] = graph[i].size();
            for (int v : graph[i]) rev[v].push_back(i);
        }
        queue<int> q;
        for (int i = 0; i < n; i++) if (outDeg[i] == 0) q.push(i);
        vector<int> safe(n, 0);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            safe[v] = 1;
            for (int pre : rev[v]) {
                if (--outDeg[pre] == 0) q.push(pre);
            }
        }
        vector<int> ans;
        for (int i = 0; i < n; i++) if (safe[i]) ans.push_back(i);
        return ans;
    }
};'''
    },
    {
        "problemId": "LC743",
        "name": "网络延迟时间",
        "platform": "LeetCode",
        "category": "图论-Dijkstra",
        "difficulty": "中等",
        "reviewCount": 4,
        "lastReview": "2026-03-06",
        "nextReview": "2026-03-12",
        "errors": "无",
        "notes": "信号从 k 发出，到达最远节点的最短时间。Dijkstra 堆优化。",
        "code": '''
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        const int INF = 1e9;
        vector<vector<pair<int,int>>> g(n + 1);
        for (auto& t : times) g[t[0]].push_back({t[1], t[2]});
        vector<int> dist(n + 1, INF);
        dist[k] = 0;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
        pq.push({0, k});
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;
            for (auto [v, w] : g[u]) {
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) ans = max(ans, dist[i]);
        return ans == INF ? -1 : ans;
    }
};'''
    },
    {
        "problemId": "LC1514",
        "name": "最大概率路径",
        "platform": "LeetCode",
        "category": "图论-最短路",
        "difficulty": "中等",
        "reviewCount": 4,
        "lastReview": "2026-03-03",
        "nextReview": "2026-03-12",
        "errors": "无",
        "notes": "src 到 dst 的最大成功概率路径。边权是概率相乘，用大根堆（概率大的先出）。",
        "code": '''
class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges,
                         vector<double>& succProb, int src, int dst) {
        vector<vector<pair<int,double>>> g(n);
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0], v = edges[i][1];
            double p = succProb[i];
            g[u].push_back({v, p});
            g[v].push_back({u, p});
        }
        vector<double> prob(n, 0.0);
        prob[src] = 1.0;
        priority_queue<pair<double,int>> pq;
        pq.push({1.0, src});
        while (!pq.empty()) {
            auto [p, u] = pq.top(); pq.pop();
            if (u == dst) return prob[dst];
            for (auto [v, edgeProb] : g[u]) {
                if (prob[v] < prob[u] * edgeProb) {
                    prob[v] = prob[u] * edgeProb;
                    pq.push({prob[v], v});
                }
            }
        }
        return 0.0;
    }
};'''
    },
    {
        "problemId": "LC787",
        "name": "K站中转内最便宜的航班",
        "platform": "LeetCode",
        "category": "图论-BellmanFord",
        "difficulty": "困难",
        "reviewCount": 8,
        "lastReview": "2026-03-05",
        "nextReview": "2026-04-05",
        "errors": "k 是中转次数不是边数，要循环 k+1 次",
        "notes": "最多经过 k 次中转，求 src 到 dst 最小成本。Bellman-Ford。\n\n注意：k 是中转次数（不是边的条数），循环 k+1 次。",
        "code": '''
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights,
                          int src, int dst, int k) {
        const int INF = 1e9;
        vector<int> dist(n, INF);
        dist[src] = 0;
        for (int i = 0; i <= k; i++) {
            vector<int> backup = dist;
            for (auto& f : flights) {
                int u = f[0], v = f[1], w = f[2];
                if (dist[u] != INF)
                    backup[v] = min(backup[v], dist[u] + w);
            }
            dist = backup;
        }
        return dist[dst] == INF ? -1 : dist[dst];
    }
};'''
    },
    {
        "problemId": "P4779",
        "name": "单源最短路径",
        "platform": "洛谷",
        "category": "图论-Dijkstra",
        "difficulty": "普及+/提高",
        "reviewCount": 1,
        "lastReview": "2026-03-08",
        "nextReview": "2026-03-10",
        "errors": "head[u]存边编号不是顶点编号；遍历边时用u不是start；dis[s]要初始化；dijkstra内不能清空head",
        "notes": "单源最短路，n 点 m 边，链式前向星 + Dijkstra 堆优化。\n\n高频出错点：\n1. head[u] = cnt（存边编号）\n2. 遍历用 u 不是 start\n3. dis[s] = 0 不要忘\n4. dijkstra 内不要 memset(head,-1)",
        "code": '''
#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
int n, m, s, cnt = 0;
int head[100005];
bool vis[100005];
struct Edge { int to, w, next; } e[200005];
int dis[100005];

void add(int u, int v, int w) {
    e[cnt].to = v; e[cnt].w = w; e[cnt].next = head[u]; head[u] = cnt++;
}

void dij(int s) {
    fill(dis, dis + n, INF);
    fill(vis, vis + n, false);
    dis[s] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> q;
    q.push({0, s});
    while (!q.empty()) {
        auto [d, u] = q.top(); q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = e[i].next) {
            int v = e[i].to, w = e[i].w;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                q.push({dis[v], v});
            }
        }
    }
}

int main() {
    cin >> n >> m >> s;
    memset(head, -1, sizeof(head));
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        add(u-1, v-1, w);
    }
    dij(s-1);
    for (int i = 0; i < n; i++) cout << dis[i] << " ";
}'''
    },
    {
        "problemId": "P1119",
        "name": "灾后重建",
        "platform": "洛谷",
        "category": "图论-Floyd",
        "difficulty": "普及+/提高",
        "reviewCount": 1,
        "lastReview": "2026-03-09",
        "nextReview": "2026-03-16",
        "errors": "dist[i][i]忘记初始化0；重边要取min；order要按建成时间排序不是节点编号",
        "notes": "n 村庄有建成时间，q 查询 (u,v,t)：时间 t 时 u 到 v 最短路，只能用 t 前建成的村庄做中转。Floyd 逐层加点。\n\n高频出错点：\n1. dist[i][i] = 0 不要忘\n2. 重边取 min\n3. order 按 buildTime 排序，不是节点编号",
        "code": '''
#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
int n, m, q;
int dist[205][205];
struct Query { int u, v, t, id; };

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m >> q;
    vector<int> buildTime(n);
    for (int i = 0; i < n; i++) cin >> buildTime[i];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = (i == j) ? 0 : INF;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[v][u], w);
    }
    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].u >> queries[i].v >> queries[i].t;
        queries[i].id = i;
    }
    sort(queries.begin(), queries.end(),
         [](const Query& a, const Query& b) { return a.t < b.t; });
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(),
         [&](int a, int b) { return buildTime[a] < buildTime[b]; });
    vector<int> answer(q);
    int k = 0;
    for (const auto& qu : queries) {
        while (k < n && buildTime[order[k]] <= qu.t) {
            int cur = order[k];
            for (int i = 0; i < n; i++) {
                if (dist[i][cur] == INF) continue;
                for (int j = 0; j < n; j++) {
                    if (dist[cur][j] == INF) continue;
                    dist[i][j] = min(dist[i][j], dist[i][cur] + dist[cur][j]);
                }
            }
            k++;
        }
        answer[qu.id] = (dist[qu.u][qu.v] == INF) ? -1 : dist[qu.u][qu.v];
    }
    for (int i = 0; i < q; i++) cout << answer[i] << "\\n";
}'''
    },
    {
        "problemId": "LC1334",
        "name": "阈值距离内邻居最少的城市",
        "platform": "LeetCode",
        "category": "图论-Floyd",
        "difficulty": "中等",
        "reviewCount": 4,
        "lastReview": "2026-03-06",
        "nextReview": "2026-03-12",
        "errors": "无",
        "notes": "distanceThreshold 内可达邻居数最少，且编号最大的城市。Floyd 多源最短路。",
        "code": '''
class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        const int INF = INT_MAX;
        vector<vector<int>> dist(n, vector<int>(n, INF));
        for (int i = 0; i < n; i++) dist[i][i] = 0;
        for (auto& e : edges) {
            dist[e[0]][e[1]] = e[2];
            dist[e[1]][e[0]] = e[2];
        }
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++) {
                if (dist[i][k] == INF) continue;
                for (int j = 0; j < n; j++) {
                    if (dist[k][j] == INF) continue;
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        int answer = -1, minCount = INT_MAX;
        for (int i = 0; i < n; i++) {
            int cnt = 0;
            for (int j = 0; j < n; j++)
                if (i != j && dist[i][j] <= distanceThreshold) cnt++;
            if (cnt < minCount || (cnt == minCount && i > answer)) {
                minCount = cnt; answer = i;
            }
        }
        return answer;
    }
};'''
    },
    {
        "problemId": "LC1584",
        "name": "连接所有点的最小成本",
        "platform": "LeetCode",
        "category": "图论-MST",
        "difficulty": "中等",
        "reviewCount": 3,
        "lastReview": "2026-03-02",
        "nextReview": "2026-03-12",
        "errors": "无",
        "notes": "n 个点曼哈顿距离，求 MST。Prim 朴素实现。",
        "code": '''
class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        if (n <= 1) return 0;
        vector<int> dist(n, INT_MAX);
        vector<int> visited(n, 0);
        dist[0] = 0; int ans = 0;
        for (int i = 0; i < n; i++) {
            int u = -1;
            for (int v = 0; v < n; v++)
                if (!visited[v] && (u == -1 || dist[v] < dist[u])) u = v;
            visited[u] = 1;
            ans += dist[u];
            for (int v = 0; v < n; v++) {
                if (!visited[v]) {
                    int d = abs(points[u][0]-points[v][0]) + abs(points[u][1]-points[v][1]);
                    dist[v] = min(dist[v], d);
                }
            }
        }
        return ans;
    }
};'''
    },
    {
        "problemId": "P1558",
        "name": "现代战争",
        "platform": "洛谷",
        "category": "模拟-矩阵",
        "difficulty": "普及+/提高",
        "reviewCount": 1,
        "lastReview": "2026-03-23",
        "nextReview": "2026-03-24",
        "errors": "无（一次性 AC）",
        "notes": "n×m 矩阵，轰炸 k 次——每次炸掉当前最大值的整行整列，求最终矩阵。\n\n核心建模：不必真正合并矩阵，用 deletedRow[]/deletedCol[] 标记被炸掉的行/列，输出时跳过即可。",
        "code": '''
#include <bits/stdc++.h>
using namespace std;
#define INF 0xFFFFFFFF
int n, m, k;
vector<vector<int>> graph;
void findMax(vector<vector<int>>& graph, int& row, int& col) {
    int maxNum = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (graph[i][j] > maxNum) {
                maxNum = graph[i][j];
                row = i; col = j;
            }
}
int main() {
    scanf("%d %d %d", &n, &m, &k);
    graph.resize(n, vector<int>(m, INF));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) cin >> graph[i][j];
    int row = 0, col = 0;
    for (int t = 0; t < k; ++t) {
        findMax(graph, row, col);
        for (int i = 0; i < m; ++i) graph[row][i] = INF;
        for (int i = 0; i < n; ++i) graph[i][col] = INF;
    }
    for (int i = 0; i < n; ++i) {
        int cnt = 0;
        for (int j = 0; j < m; ++j)
            if (graph[i][j] != INF) {
                if (cnt == 0) printf("%d", graph[i][j]);
                else printf(" %d", graph[i][j]);
                ++cnt;
            }
        if (cnt != 0) printf("\\n");
    }
}'''
    },
]


def infer_leitner_box(review_count: int, review_date: str, next_review: str) -> int:
    """根据复习次数和日期推断当前盒子"""
    today = date.today()
    try:
        next_d = date.fromisoformat(next_review)
    except:
        next_d = today

    if review_count >= 5:
        return 5
    elif review_count >= 4:
        return 4
    elif review_count >= 3:
        return 3
    elif review_count >= 2:
        return 2
    elif review_count >= 1:
        return 1
    else:
        return 1


def create_problem(p: dict):
    folder = f"{p['problemId']}_{p['name']}"
    folder_path = os.path.join(PROBLEMS_DIR, folder)
    os.makedirs(folder_path, exist_ok=True)

    box = infer_leitner_box(p["reviewCount"], p["lastReview"], p["nextReview"])

    # review.json
    review_data = {
        "problemId": p["problemId"],
        "name": p["name"],
        "platform": p["platform"],
        "category": p["category"],
        "difficulty": p["difficulty"],
        "leitnerBox": box,
        "easeFactor": 2.5,
        "interval": BOX_INTERVALS[box],
        "repetitions": p["reviewCount"],
        "nextReview": p["nextReview"],
        "lastReview": p["lastReview"],
        "firstCompleted": p["lastReview"],
        "url": _make_url(p["problemId"], p["platform"]),
        "totalReviews": p["reviewCount"],
        "history": []
    }
    review_path = os.path.join(folder_path, "review.json")
    with open(review_path, "w", encoding="utf-8") as f:
        json.dump(review_data, f, ensure_ascii=False, indent=2)

    # notes.md
    notes_content = f"""# {p['problemId']} - {p['name']}

**平台：** {p['platform']}
**分类：** {p['category']}
**难度：** {p['difficulty']}
**状态：** {BOX_INTERVALS[box]}天间隔 · {p['reviewCount']}次复习

---

## 题目描述

{p['notes']}

---

## 参考代码

```{p.get('language', 'cpp')}
{p['code'].strip()}
```

---

## 错误记录

{p['errors']}
"""
    notes_path = os.path.join(folder_path, "notes.md")
    with open(notes_path, "w", encoding="utf-8") as f:
        f.write(notes_content)

    print(f"  ✅ {p['problemId']} -> {folder}/")


def run():
    os.makedirs(PROBLEMS_DIR, exist_ok=True)
    print(f"\n开始迁移 {len(PROBLEMS)} 道题目到 {PROBLEMS_DIR}\n")
    for p in PROBLEMS:
        create_problem(p)
    print(f"\n✅ 迁移完成！共 {len(PROBLEMS)} 道题目")


if __name__ == "__main__":
    run()
