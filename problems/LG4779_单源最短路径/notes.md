# P4779 - 单源最短路径

**平台：** 洛谷
**分类：** 图论-Dijkstra
**难度：** 普及+/提高
**状态：** 1天间隔 · 1次复习

---

## 题目描述

单源最短路，n 点 m 边，链式前向星 + Dijkstra 堆优化。

高频出错点：
1. head[u] = cnt（存边编号）
2. 遍历用 u 不是 start
3. dis[s] = 0 不要忘
4. dijkstra 内不要 memset(head,-1)

---

## 参考代码

```cpp
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
}
```

---

## 错误记录

head[u]存边编号不是顶点编号；遍历边时用u不是start；dis[s]要初始化；dijkstra内不能清空head
