#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll cal(ll n){
    ll ans=0;
    while(n>0){
        ans+=n%10;
        n/=10;
    }
    return ans;
}

void solve(){
    int n=0;
    ll ans=0;
    cin>>n;
    ll num[200005];
    //get input
    for(int i=0;i<n;++i){
        cin>>num[i];
    }
    //tanxin
    for(int i=n-1;i>0;--i){
        while(num[i-1]>=10 && num[i-1]>num[i]){
            num[i-1]=cal(num[i-1]);
            ++ans;
        }
        if(num[i-1]>num[i]){
            printf("-1\n");
            return;
        }
    }
    printf("%lld\n",ans);
}

int main(){
    int q;
    cin>>q;
    while(q--){
        solve();
    }

    return 0;
}
