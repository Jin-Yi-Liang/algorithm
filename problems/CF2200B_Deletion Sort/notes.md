# CF2200B - Deletion Sort

## 题目链接
https://codeforces.com/contest/2200/problem/B

## 思路
贪心：检查数组是否已经非递减。

- 遍历时记录当前最大元素 `num`
- 若 `cur < num`，说明存在递减对，数组需要删除元素
  - If a is non-decreasing at the start, then the answer is trivially n. Otherwise, there exists an i such that ai>ai+1. We can delete all elements besides these two and then delete ai to get to 1 remaining element, so the answer is 1 in this case.
  - 若全程无递减 → 无法删除，返回 n

**为什么删除 1 个就够了？**
- 一旦发现某个 `cur` 比前面的最大值还小，删掉这个 `cur` 就恢复了递增
- 不需要删多个

## 复杂度
- 时间：O(n)
- 空间：O(1)

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int t, n;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        vector<int> vec(n, 0);
        for (int i = 0; i < n; ++i)
            scanf("%d", &vec[i]);

        int num = vec[0];
        bool canDel = false;
        for (int cur : vec) {
            if (cur < num) {
                canDel = true;
                break;
            }
            num = max(num, cur);
        }

        if (canDel)
            printf("1\n");
        else
            printf("%d\n", n);
    }

    return 0;
}
```

## 关键点
- **核心判断**：`cur < max_so_far` → 存在递减对
- **答案规律**：有递减 → 1；无递减 → n（一个都删不了）
