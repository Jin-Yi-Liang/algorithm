#include<bits/stdc++.h>
using namespace std;
typedef struct{
    int tag,x,y,len;
}Act;
Act act[100005];

bool isin(int tx,int ty,int index){
    if(tx>=act[index].x && tx<=act[index].x+act[index].len-1
        && ty>=act[index].y && ty<=act[index].y+act[index].len-1){
            return true;
    }
    return false;
}

void doact(int&tx,int&ty,int index){
    Act cur=act[index];

}

void solve(){
    int n=0,q=0,d=0,tx=0,ty=0;
    cin>>n>>q;
    for(int i=0;i<q;++i){
        cin>>act[i].tag>>act[i].x>>act[i].y>>act[i].len;
    }
    cin>>d;
    for(int i=0;i<d;++i){
        cin>>tx>>ty;    
        for(int j=q-1;j>=0;--j){
            if(!isin(tx,ty,j)) continue;
            doact(tx,ty,j);
        }
    }
}

int main(){
    solve();
    return 0;
}