## L1-009 N个数求和 解题笔记

### 核心算法：GCD（最大公因数）

```cpp
long long gcd(long long a, long long b){
    return b == 0 ? a : gcd(b, a % b);
}
```

**要点：**
- 参数用**值传参**，不能用引用（递归时 `a%b` 是临时值）
- 参数和返回值都用 `long long`，不能用 `int`
- 调用时必须传**绝对值**：`gcd(abs(sa), abs(sb))`，否则负数导致结果错误

---

### 分数累加

```cpp
sa = sa * b + a * sb;  // 通分相加
sb = sb * b;
long long num = gcd(abs(sa), abs(sb));
sa /= num;  sb /= num;  // 每步化简，防止溢出
```

---

### 输出逻辑（重点）

分四种情况，**按顺序判断**：

```
结果为 0         → 输出 "0"
|分子| < 分母    → 纯分数，直接输出 "sa/sb"（含负分数如 -1/3）
否则             → 分离整数部分
    remain < 0 时修正：sn--, remain+=sb
    remain != 0  → 输出 "sn remain/sb"
    remain == 0  → 输出 "sn"
```

**为什么要 `remain < 0` 修正？**

C++ 除法向零取整，`-4/3 = -1` 余 `-1`，但数学上应该是 `-2` 余 `2`：
```
-4/3 → sn=-1, remain=-1  （错）
修正 → sn=-2, remain=2   （对，即 -2 + 2/3）
```

**为什么先判 `abs(sa) < sb`？**

避免负分数（如 `-1/3`）被错误地进入整数分离逻辑：
```
-1/3 → sn=0, remain=-1 → 修正后 sn=-1, remain=2 → 输出 "-1 2/3"  （错）
abs(-1) < 3 → 直接输出 "-1/3"  （对）
```

AC code:
```
#include<bits/stdc++.h>
using namespace std;
int N;
long long sa=0,sb=1;
long long gcd(long long sa,long long sb){
    return sb==0?sa:gcd(sb,sa%sb);
}
int main(){
    //init
    scanf("%d",&N);
    long long a=0,b=0;
    char trash;

    //main logic
    for(int i=0;i<N;++i){
        scanf("%lld%c%lld",&a,&trash,&b);
        sa=sa*b+a*sb;
        sb=sb*b;
        long long num=gcd(abs(sa),abs(sb));
        sa/=num;sb/=num;
    }

    //output
    if(sa==0){
        printf("0");
        return 0;
    }
    if(abs(sa)<sb){
        printf("%lld/%lld",sa,sb);
        return 0;
    }
    long long sn=sa/sb;
    long long remain=sa%sb;
    if(remain<0){
        --sn;
        remain+=sb;
    }
    if(remain!=0) printf("%lld %lld/%lld",sn,remain,sb);
    else printf("%lld",sn);
    
    return 0;
}
```