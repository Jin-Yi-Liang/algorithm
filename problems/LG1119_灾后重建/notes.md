# P1119 - 灾后重建

**平台：** 洛谷
**分类：** 图论-Floyd
**难度：** 普及+/提高
**状态：** 1天间隔 · 1次复习

---

## 题目描述

n 村庄有建成时间，q 查询 (u,v,t)：时间 t 时 u 到 v 最短路，只能用 t 前建成的村庄做中转。Floyd 逐层加点。

高频出错点：
1. dist[i][i] = 0 不要忘
2. 重边取 min
3. order 按 buildTime 排序，不是节点编号

---

## 参考代码

```cpp
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
    for (int i = 0; i < q; i++) cout << answer[i] << "\n";
}
```

---

## 错误记录

dist[i][i]忘记初始化0；重边要取min；order要按建成时间排序不是节点编号
