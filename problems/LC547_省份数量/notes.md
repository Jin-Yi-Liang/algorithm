# LC547 - 省份数量

**平台：** LeetCode
**分类：** 图论-并查集
**难度：** 中等
**状态：** 30天间隔 · 16次复习

---

## 题目描述

n 个城市相连，求省份数量。并查集裸题。

---

## 参考代码

```cpp
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
};
```

---

## 错误记录

无
