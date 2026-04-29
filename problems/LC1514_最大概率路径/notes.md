# LC1514 - 最大概率路径

**平台：** LeetCode
**分类：** 图论-最短路
**难度：** 中等
**状态：** 14天间隔 · 4次复习

---

## 题目描述

src 到 dst 的最大成功概率路径。边权是概率相乘，用大根堆（概率大的先出）。

---

## 参考代码

```cpp
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
};
```

---

## 错误记录

无
