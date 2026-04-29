#include<bits/stdc++.h>
using namespace std;
int n[35],m[35],num[35];

void solve(){
    int d,sumtime,cur=0;
    cin>>d>>sumtime;
    for(int i=0;i<d;++i){
        cin>>n[i]>>m[i];
        num[i]=n[i];
        cur+=num[i];
    }
    if(sumtime<cur){
        printf("NO");
        return;
    }
    int dis=sumtime-cur,tmp=dis;
    for(int i=0;i<d;++i){
        tmp=dis;
        tmp-=(m[i]-n[i]);
        if(tmp>0){
            num[i]=m[i];
            dis=tmp;
        }
        else if(tmp<=0){
            num[i]+=dis;
            dis=0;
            break;
        }
    }
    if(dis>0){
        printf("NO");
        return;
    }
    else{
        printf("YES\n");
        for(int i=0;i<d;++i) printf("%d ",num[i]);
    }
}

int main(){
    solve();
    return 0;
}
