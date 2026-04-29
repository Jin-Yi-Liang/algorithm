#include<bits/stdc++.h>
using namespace std;
#define INF 200005

void solve(){
    int w,m,r,wr,mr;
    cin>>w>>m>>r;
    vector<pair<int,int>>vec;
    for(wr=1;wr<r;++wr){
        mr=r-wr;
        if(w%wr==0 && m%mr==0 && w/wr!=1 && m/mr!=1){
            vec.push_back({wr,mr});
        }
    }

    int mindis=INF,ans=-1;
    for(auto&[wr,mr]:vec){
        int wn=w/wr,mn=m/mr;
        if(abs(wn-mn)<mindis){
            mindis=abs(wn-mn);
            ans=wr;
        }
    }
    if(ans==-1){
        printf("No Solution");
        return;
    }
    printf("%d %d",ans,r-ans);

}

int main(){
    solve();

    return 0;
}