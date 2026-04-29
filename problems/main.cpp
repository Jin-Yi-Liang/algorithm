#include<bits/stdc++.h>
using namespace std;
int lnum[205],onum[205];

void solve(){
    int n;
    string str;
    cin>>n>>str;
    for(int i=1;i<=n;++i){
        if(str[i-1]=='L'){
            lnum[i]=lnum[i-1]+1;
            onum[i]=onum[i-1];
        }
        else if(str[i]=='O'){
            onum[i]=onum[i-1]+1;
            lnum[i]=lnum[i-1];
        }
    }
    for(int i=1;i<=n;++i){
        int xl=lnum[i],yl=lnum[n]-lnum[i],
        xo=onum[i],yo=onum[n]-onum[i];
        if(xl!=yl&&xo!=yo){
            printf("%d",i);
            return;
        }
    }
    printf("-1");
}

int main(){
    solve();
    return 0;
}