// CF2200C - Minimize the Length of the String
// Platform: Codeforces
// Category: 贪心
// Date: 2026-03-24

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
                str.erase(j - 1, 2);
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
