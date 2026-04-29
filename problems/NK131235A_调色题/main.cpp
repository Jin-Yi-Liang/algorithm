// A - 调色题
// Platform: 牛客网
// Category: 贪心
// Date: 2026-03-24

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
                vec[i] = vec[i - 1] + 1;
                ans += vec[i] - tmp;
            }
        }
        printf("%lld\n", ans);
    }

    return 0;
}
