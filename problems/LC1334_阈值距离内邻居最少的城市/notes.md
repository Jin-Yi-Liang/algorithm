# LC1334 - 阈值距离内邻居最少的城市

**平台：** LeetCode
**分类：** 图论-Floyd
**难度：** 中等
**状态：** 14天间隔 · 4次复习

---

## 题目描述

distanceThreshold 内可达邻居数最少，且编号最大的城市。Floyd 多源最短路。

---

## 参考代码

```cpp
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
};
```

---

## 错误记录

无
