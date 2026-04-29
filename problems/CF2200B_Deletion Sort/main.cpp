// CF2200B - Deletion Sort
// Platform: Codeforces
// Category: 贪心
// Date: 2026-03-24

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
