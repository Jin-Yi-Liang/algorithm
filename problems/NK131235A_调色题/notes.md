# A - 调色题

## 题目链接
https://ac.nowcoder.com/acm/contest/131235/A

## 思路
贪心：排序后从左到右处理相邻元素。
- 若 `vec[i] <= vec[i-1]`，说明重复，需要把 `vec[i]` 提升到 `vec[i-1] + 1`
- 操作次数累加差值 `vec[i] - tmp`

**为什么正确？**
- 排序后，要使每个元素不同且增量最小，最优策略是让每个元素刚好比左边的大 1
- 局部最优 → 全局最优：每一步都选最小可行值，不影响后续决策

## 复杂度
- 时间：O(n log n)（排序）
- 空间：O(n)

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int T, n;
long long ans;

int main() {
    scanf("%d", &T);
    while (T--) {
        ans = 0;
        scanf("%d", &n);
        vector<int> vec(n, 0);
        for (int i = 0; i < n; ++i)
            cin >> vec[i];

        sort(vec.begin(), vec.end());
        for (int i = 1; i < n; ++i) {
            if (vec[i] <= vec[i - 1]) {
                int tmp = vec[i];
                vec[i] = vec[i - 1] + 1;   // 提升到最小可行值
                ans += vec[i] - tmp;       // 累计操作次数
            }
        }
        printf("%lld\n", ans);
    }

    return 0;
}
```

## 关键点
- **排序是核心**：保证相邻元素是当前最小候选
- **增量最小**：每次只提升到 `prev + 1`，不多也不少
- **long long**：n≤2×10⁵，ai≤10⁹，累计操作可能超过 int 范围
