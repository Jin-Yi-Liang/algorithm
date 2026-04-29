# P1558 - 现代战争

**平台：** 洛谷
**分类：** 模拟-矩阵
**难度：** 普及+/提高
**状态：** 1天间隔 · 1次复习

---

## 题目描述

n×m 矩阵，轰炸 k 次——每次炸掉当前最大值的整行整列，求最终矩阵。

核心建模：不必真正合并矩阵，用 deletedRow[]/deletedCol[] 标记被炸掉的行/列，输出时跳过即可。

---

## 参考代码

```cpp
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
        if (cnt != 0) printf("\n");
    }
}
```

---

## 错误记录

无（一次性 AC）
