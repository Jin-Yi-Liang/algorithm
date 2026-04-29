// CFA - Eating Soup
// Platform: Codeforces
// Category: 模拟
// Date: 2026-03-24

#include <bits/stdc++.h>
using namespace std;

int t, n;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        vector<int> food(n, 0);
        for (int i = 0; i < n; ++i)
            scanf("%d", &food[i]);

        int maxnum = food[0];
        vector<int> index;
        index.push_back(0);
        for (int i = 1; i < n; ++i) {
            if (food[i] > maxnum) {
                maxnum = food[i];
                index.clear();
                index.push_back(i);
            } else if (food[i] == maxnum) {
                index.push_back(i);
            }
        }
        printf("%d\n", (int)index.size());
    }

    return 0;
}
