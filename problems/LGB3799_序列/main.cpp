#include<bits/stdc++.h>
using namespace std;
#define ll long long

int n, m;
ll delta;                     // 全局累加值（注意用 long long 防止溢出）
int num[500005];              // 原始数组（排序后）
ll sum[500005];              // 原始数组的前缀和

// 二分查找第一个满足 num[i] + delta >= 0 的位置
int binarysearch() {
    int l = 1, r = n, mid, ans = n + 1;   // ans = n+1 表示没有元素满足条件
    while (l <= r) {
        mid = l + (r - l) / 2;
        if (num[mid] + delta >= 0) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> num[i];

    sort(num + 1, num + n + 1);                     // 排序，便于二分
    for (int i = 1; i <= n; ++i) sum[i] = sum[i-1] + num[i];   // 原始前缀和

    delta = 0;
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            ll k;
            cin >> k;
            delta += k;                // 全局累加
        } else {
            int pos = binarysearch();  // 第一个实际值 ≥ 0 的位置
            // 后缀和 = 原始后缀和 + 元素个数 × delta
            ll ans = sum[n] - sum[pos-1] + (n - pos + 1) * delta;
            cout << ans << '\n';
        }
    }
    return 0;
}
