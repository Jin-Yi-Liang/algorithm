#include<bits/stdc++.h>
using namespace std;
long long num[200005],sum[200005];

void solve(){
    long long n,ans=0;
    //pre-sum
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>num[i];
    }
    for(int i=1;i<=n;++i){
        sum[i]=sum[i-1]+num[i];
    }
    for(int i=1;i<n;++i){
        ans+=num[i]*(sum[n]-sum[i]);
    }
    printf("%lld",ans);

}

int main(){

    solve();

    return 0;
}
