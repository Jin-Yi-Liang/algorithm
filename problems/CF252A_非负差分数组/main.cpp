#include<bits/stdc++.h>
using namespace std;
int num[105];

void solve(){
    int n,cur,ans=-1;
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>cur;
        num[i]=num[i-1]^cur;
    }
    for(int i=1;i<=n;++i){
        for(int j=i;j<=n;++j){
            ans=max(ans,num[j]^num[i-1]);
        }
    }
    printf("%d",ans);
}

int main(){
    solve();
    return 0;
}
