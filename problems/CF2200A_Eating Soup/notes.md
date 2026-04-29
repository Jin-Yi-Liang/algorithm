# CFA - Eating Soup

## 题目链接
https://codeforces.com/contest/2200/problem/A

## 思路
找到所有可能获胜者。

**关键观察**：如果从某个玩家开始轮转，最终轮到拥有**最多食物**的玩家时，由于他吃的最慢，他一定最后一个吃完。其他拥有同样最多食物的玩家也都可能最后吃完。

因此答案为：**拥有最大食物数量的玩家数量**。

## 复杂度
- 时间：O(n)
- 空间：O(n)

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int t, n;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        vector<int> food(n, 0);
        for (int i = 0; i < n; ++i)
            scanf("%d", &food[i]);

        // 找最大值
        int maxnum = food[0];
        for (int i = 1; i < n; ++i)
            maxnum = max(maxnum, food[i]);

        // 统计有多少人拥有最大食物数
        int ans = 0;
        for (int i = 0; i < n; ++i)
            if (food[i] == maxnum) ++ans;

        printf("%d\n", ans);
    }

    return 0;
}
```

## 关键点
- **为什么拥有最大食物数的人一定赢或可能赢？** 因为每一轮每个人都吃 1，食物多的人轮次更多。当轮到这个最多食物的人时，其他人都空了（或者即将空），他最后吃的那碗一定最后被吃完
- **答案就是最大食物数量的人的数量**
