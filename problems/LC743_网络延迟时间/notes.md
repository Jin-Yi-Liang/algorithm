# LC743 - 网络延迟时间

**平台：** LeetCode
**分类：** 图论-Dijkstra
**难度：** 中等
**状态：** 14天间隔 · 4次复习

---

## 题目描述

信号从 k 发出，到达最远节点的最短时间。Dijkstra 堆优化。

---

## 参考代码

```cpp
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
};
```

---

## 错误记录

无
