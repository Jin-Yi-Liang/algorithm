#include<bits/stdc++.h>
using namespace std;
#define ll long long
void solve(){
    ll n,x,sum=1;
    cin>>n>>x;
    while(x>0){
        if(x&1)sum*=n;
        x>>=1;
        n*=n;
    }
    printf("%lld",sum);
}

int main(){
    solve();
    return 0;
}