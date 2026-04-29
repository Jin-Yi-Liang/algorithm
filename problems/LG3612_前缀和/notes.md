# B3612 前缀和

## 题目链接
https://www.luogu.com.cn/problem/B3612

## 思路
预处理前缀和数组 `sum[i] = vec[1] + vec[2] + ... + vec[i]`，区间 [l,r] 的和直接用 `sum[r] - sum[l-1]` O(1) 计算。

## 复杂度
- 时间：O(n + m)
- 空间：O(n)

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m;
int vec[100005];   // 原数组
int sum[100005];   // 前缀和数组，sum[i] = vec[1] + ... + vec[i]

int main() {
    // 读取 n 个数
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &vec[i]);

    // 预处理前缀和
    sum[1] = vec[1];
    for (int i = 2; i <= n; ++i)
        sum[i] = sum[i - 1] + vec[i];

    // 读取 m 次查询
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int l, r;
        scanf("%d %d", &l, &r);
        // 区间 [l, r] 的和 = sum[r] - sum[l-1]
        printf("%d\n", sum[r] - sum[l - 1]);
    }

    return 0;
}
```

## 关键点
- 前缀和下标从 1 开始，sum[0] = 0（可省略不存）
- 区间查询公式：`sum[r] - sum[l-1]`
