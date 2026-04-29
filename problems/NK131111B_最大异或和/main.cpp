#include<bits/stdc++.h>
using namespace std;

void solve(){
    int x,y,xx,yy,ans=0;
    cin>>x>>y;
    for(int i=0;i<32;++i){
        xx=x>>i;
        for(int j=0;j<32;++j){
            yy=y>>j;
            ans=max(ans,xx^yy);
        }
    }
    printf("%d\n",ans);
}

int main(){
    int q;
    cin>>q;
    while(q--)
    solve();
}
