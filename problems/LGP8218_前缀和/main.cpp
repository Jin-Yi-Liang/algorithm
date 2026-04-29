#include<bits/stdc++.h>
using namespace std;

int num[100005];
long long sum[100005];

void solve(){
    int n,m;
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>num[i];
    }
    //pre sum
    sum[0]=0;
    for(int i=1;i<=n;++i){
        sum[i]=sum[i-1]+num[i];
    }
    cin>>m;
    for(int i=0;i<m;++i){
        int l,r;
        cin>>l>>r;
        printf("%lld\n",sum[r]-sum[l-1]);
    }
}

int main(){
    solve();

    return 0;
}