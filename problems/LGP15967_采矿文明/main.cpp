#include<bits/stdc++.h>
using namespace std;

void solve(){
    int n,m,k;
    long long ans=0,preSum=0,topKSum=0;
    long long mine[100005];
    int cost[100005];
    cost[0]=0;
    cin>>n>>m>>k;
    for(int i=1;i<n;++i)
        cin>>cost[i];
    for(int i=0;i<n;++i)
        cin>>mine[i];

    priority_queue<int,vector<int>,greater<>>pq;
    for(int i=0;i<n;++i){
        preSum+=cost[i];
        if(pq.size()<k){
            pq.push(mine[i]);
            topKSum+=mine[i];
        }
        else if(mine[i]>pq.top()){
            topKSum-=pq.top();
            pq.pop();
            pq.push(mine[i]);
            topKSum+=mine[i];
        }

        long long budget=m-preSum;
        if(budget>=0)
            ans=max(ans,min(budget,topKSum));
    }
    printf("%lld",ans);
}

int main(){
    solve();

    return 0;
}
