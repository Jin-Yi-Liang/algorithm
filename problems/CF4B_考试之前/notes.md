# 每日时间 - 思路分析

## 关键观察

每天的时间有一个**范围** `[min_i, max_i]`，我们需要让所有天的总和恰好等于 `sumTime`。

**贪心策略：先给每天分配最少时间，再把剩余时间往里塞。**

## 步骤拆解

### 第一步：先分配最少时间，判断是否有解

```
sumMin = Σ min_i
sumMax = Σ max_i

如果 sumMin > sumTime → NO（怎么减都不够少）
如果 sumMax < sumTime → NO（怎么加都不够多）
```

### 第二步：计算还需要额外分配多少小时

```
remain = sumTime - sumMin
```

### 第三步：逐天贪心往里加

```
每天能额外加的量 = max_i - min_i
如果 remain >= 能加的量 → 加满，remain 减去加的量
如果 remain < 能加的量  → 加 remain，remain 归零，结束
```

## 模拟样例2

```
d=2, sumTime=5
第1天: [0,1]   第2天: [3,5]

先分配最少: schedule = [0, 3], sum = 3
remain = 5 - 3 = 2

第1天能额外加: 1-0=1, remain=2 >= 1, 加满 → schedule[1]=1, remain=1
第2天能额外加: 5-3=2, remain=1 < 2,  加1  → schedule[2]=4, remain=0

结果: 1 4  ✓
```

## 复杂度

| 项目 | 值 |
|---|---|
| 时间复杂度 | O(d) |
| 空间复杂度 | O(d) |

整体思路：**先满足下界，再贪心填上界**，两端一夹就能判断有无解。
