#include<bits/stdc++.h>
using namespace std;
int num[1000005];

void solve(){
    int c,p;
    long long ans=0;
    cin>>c>>p;
    //init contest
    for(int i=0;i<c;++i){
        int m,s;
        cin>>m>>s;
        num[m]=max(num[m],s);
    }
    //get max contest return value
    for(int i=1;i<1000005;++i){
        num[i]=max(num[i],num[i-1]);
    }
    //get questions
    for(int i=0;i<p;++i){
        int q,d;
        cin>>q>>d;
        ans+=max(0,num[q]-d);
    }
    printf("%lld",ans);
}

int main(){
    solve();

    return 0;
}