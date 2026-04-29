# 洛谷 B3612 - 前缀和（入门）

## 题目链接
https://www.luogu.com.cn/problem/B3612

## 思路
**一维前缀和**

### 构建前缀和
```cpp
sum[1] = vec[1];
for(int i=2;i<=n;++i)
    sum[i] = sum[i-1] + vec[i];
```

### 查询区间和 [l, r]
```cpp
ans = sum[r] - sum[l-1];
```

## 复杂度
- 构建：O(n)
- 查询：O(1) × m

## 关键点
- 数组下标从 1 开始，`sum[0] = 0` 自然成立
- `sum[r] - sum[l-1]` 即为区间 [l, r] 的和
