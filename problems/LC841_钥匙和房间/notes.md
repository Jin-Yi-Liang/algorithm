# LC841 - 钥匙和房间

**平台：** LeetCode
**分类：** 图论-BFS
**难度：** 简单
**状态：** 30天间隔 · 7次复习

---

## 题目描述

n 个房间有钥匙，从 0 号房间开始 BFS，能否打开所有房间。

---

## 参考代码

```cpp
class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size();
        vector<int> visited(n, 0);
        queue<int> q;
        q.push(0); visited[0] = 1;
        while (!q.empty()) {
            int room = q.front(); q.pop();
            for (int key : rooms[room]) {
                if (!visited[key]) { visited[key] = 1; q.push(key); }
            }
        }
        for (int v : visited) if (!v) return false;
        return true;
    }
};
```

---

## 错误记录

无
