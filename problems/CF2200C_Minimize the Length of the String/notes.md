# CF2200C - Minimize the Length of the String

## 题目链接
https://codeforces.com/contest/2200/problem/C

## 思路
What if you delete characters instead of replacing them with *?

Instead of replacing characters with \*s, just delete them from the string. Then, the operation becomes deleting two adjacent characters that are equal. AksLolCoding wins if the string becomes empty. Since deleting a pair can never disrupt another pair, the order in which we do the operations does not matter.

We search through the array $\frac{n}{2}$ times, removing a pair of equal elements whenever we find one. At the end, just output whether the string is empty.

The problem can also be solved in $O(n)$ using a stack.
贪心：反复删除相邻的相同字符对。

- 两层循环，外层控制轮数，内层从头扫描字符串
- 若发现 `str[j-1] == str[j]`，删除这一对 `erase(j-1, 2)`
- 删完后字符串缩短，继续从头扫描

**直到无法再删为止**，检查是否为空。

**为什么正确？**
- 删除相邻相同字符对后，字符串变得更短，且不会影响后续能删除的对
- 每一次删除都是局部最优，最终能得到唯一确定的结果
- 如果最后为空，说明所有字符都能配对消除

## 复杂度
- 时间：最坏 O(n²)（每次 erase 是 O(n)，最多删除 n/2 次）
- 空间：O(1) 原地操作

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    string str;
    scanf("%d", &n);
    cin >> str;

    for (int i = 0; i * 2 < n; ++i) {
        for (int j = 1; j < (int)str.size(); ++j) {
            if (str[j - 1] == str[j]) {
                str.erase(j - 1, 2);  // 删除这一对
            }
        }
    }

    cout << (str.empty() ? "YES\n" : "NO\n");
}

int main() {
    int t = 1;
    scanf("%d", &t);
    while (t--) solve();
    return 0;
}
```

## 关键点
- **`erase(pos, len)`**：C++ string 的 erase 是 O(n)，注意复杂度
- **外层循环上限 `i*2 < n`**：最多删除 n/2 对
- **判断 YES 的条件**：所有字符都能配对消除 → 字符串最终为空
