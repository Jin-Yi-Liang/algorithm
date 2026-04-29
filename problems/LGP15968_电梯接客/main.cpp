#include<bits/stdc++.h>
using namespace std;

void solve(){
    // 统一使用 long long，防止数据量大时计算溢出
    long long n, x, y, w, ans = 0;
    cin >> n >> x >> y >> w;

    // 使用优先队列，按楼层从小到大排序
    priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<>> pq;

    for(int i = 0; i < n; ++i){
        long long f, a;
        cin >> f >> a;
        pq.push({f, a});
    }

    long long cur_fl = x; // 电梯当前所在楼层
    long long space = w;  // 电梯当前剩余空间

    while(!pq.empty()){
        auto [fl, cur] = pq.top();
        pq.pop();

        // 【核心优化：数学批量计算 (解决 TLE)】
        // 触发条件：电梯目前是全空的，且这一层的人数足够装满至少一整趟
        if(space == w && cur >= w){
            long long full_trips = cur / w;  // 完整的满载趟数
            long long leftover = cur % w;    // 剩下的零星人数

            // 第一趟比较特殊：从当前位置 cur_fl 跑到接人层 fl，再送到终点 y
            ans += abs(cur_fl - fl) + abs(y - fl);

            // 剩下的满载趟数：全都是从 y 跑到 fl，再从 fl 送回 y
            if(full_trips > 1){
                ans += (full_trips - 1) * 2 * abs(y - fl);
            }

            cur_fl = y; // 这一大批人全送完后，电梯最后停在 y 层

            // 如果还有剩下不够凑满一趟的人，把他们重新塞回队列排队
            if(leftover > 0){
                pq.push({fl, leftover});
            }
        }
        // 【原本的模拟逻辑 (处理不足一趟的零星接送)】
        else {
            ans += abs(cur_fl - fl); // 电梯开到当前接人层
            cur_fl = fl;

            // 【核心修复：加上等号 (解决 WA)】
            if(space >= cur){
                // 电梯装得下这层剩下的所有人
                space -= cur;
            } else {
                // 电梯装不下了，装满就走
                cur -= space;
                pq.push({fl, cur}); // 剩下没上电梯的人重新进堆
                space = 0;          // 电梯满载
            }

            // 如果电梯满载了，立刻送去终点 y
            if(space == 0){
                ans += abs(y - cur_fl);
                cur_fl = y; // 更新当前楼层为 y
                space = w;  // 卸客后电梯重新空出来
            }
        }
    }

    // 扫尾工作：所有楼层的人都接完了，如果电梯里还有人，最后送一趟去 y
    if(space < w){
        ans += abs(y - cur_fl);
    }

    printf("%lld\n", ans);
}

int main(){
    solve();
    return 0;
}
