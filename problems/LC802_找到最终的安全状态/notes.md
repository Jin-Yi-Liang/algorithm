# LC802 - 找到最终的安全状态

**平台：** LeetCode
**分类：** 图论-拓扑排序
**难度：** 中等
**状态：** 30天间隔 · 14次复习

---

## 题目描述

安全节点：从该节点出发不会走到环。拓扑排序逆向删除法。

---

## 参考代码

```cpp
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
};
```

---

## 错误记录

无
