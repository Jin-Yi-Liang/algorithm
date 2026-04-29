# LC787 - K站中转内最便宜的航班

**平台：** LeetCode
**分类：** 图论-BellmanFord
**难度：** 困难
**状态：** 30天间隔 · 8次复习

---

## 题目描述

最多经过 k 次中转，求 src 到 dst 最小成本。Bellman-Ford。

注意：k 是中转次数（不是边的条数），循环 k+1 次。

---

## 参考代码

```cpp
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
};
```

---

## 错误记录

k 是中转次数不是边数，要循环 k+1 次
