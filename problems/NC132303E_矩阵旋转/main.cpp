#include<bits/stdc++.h>
using namespace std;
typedef struct{
    int tag,x,y,len;
}Act;
Act act[100005];

bool isin(long long dx,long long dy,int j){
    Act cur=act[j];
    return dx>=cur.x && dx<=cur.x+cur.len-1 &&
            dy>=cur.y && dy<=cur.y+cur.len-1;
}

void dotrans(long long&dx,long long&dy,int j){
    Act cur=act[j];
    long long x=dx-cur.x,y=dy-cur.y,newx=0,newy=0;
    if(cur.tag==2){
        newx=y;
        newy=cur.len-x-1;
    }
    else if(cur.tag==1){
        newx=cur.len-y-1;
        newy=x;
    }
    dx=newx+cur.x;
    dy=newy+cur.y;
}

void solve(){
    long long n=0;
    int q=0,d=0;
    long long dx=0,dy=0;
    cin>>n>>q;
    for(int i=0;i<q;++i){
        cin>>act[i].tag>>act[i].x>>act[i].y>>act[i].len;
    }
    cin>>d;
    for(int i=0;i<d;++i){
        cin>>dx>>dy;
        for(int j=q-1;j>=0;--j){
            if(isin(dx,dy,j)==false) continue;
            dotrans(dx,dy,j);
        }
        long long ans=n*(dx-1)+dy;
        cout<<ans<<"\n";
    }
}

int main(){
    solve();
    return 0;
}
