# LC1584 - 连接所有点的最小成本

**平台：** LeetCode
**分类：** 图论-MST
**难度：** 中等
**状态：** 7天间隔 · 3次复习

---

## 题目描述

n 个点曼哈顿距离，求 MST。Prim 朴素实现。

---

## 参考代码

```cpp
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
};
```

---

## 错误记录

无
