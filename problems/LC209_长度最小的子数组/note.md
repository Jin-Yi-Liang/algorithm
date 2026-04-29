# LC209 长度最小的子数组

## 题目描述

给定正整数 target 和数组 nums，找长度最小的连续子数组，使和 ≥ target。返回其长度，无则返回 0。

## 核心算法：滑动窗口（双指针）

**窗口内和 `cur`**：右指针扩展窗口累加和，左指针收缩窗口减去左侧元素

```cpp
int minSubArrayLen(int target, vector<int>& nums) {
    int l = 0, r, len = INF, cur = 0, n = nums.size();
    for (r = 0; r < n; ++r) {
        cur += nums[r];              // 右指针扩展
        while (cur >= target) {     // 收缩直到不满足条件
            len = min(len, r - l + 1);
            cur -= nums[l++];        // 左指针收缩
        }
    }
    return len == INF ? 0 : len;
}
```

## 关键点

- **右指针扩展**：遍历数组，累加 nums[r]
- **左指针收缩**：当 cur ≥ target 时，更新最小长度，然后减去 nums[l] 并右移 l
- **时间复杂度**：每个元素最多被左右指针访问一次，$O(N)$
- **初始化**：len 用 INF（如 100005）初始化，无解时返回 0
