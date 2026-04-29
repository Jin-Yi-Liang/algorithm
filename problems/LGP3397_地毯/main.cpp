#include<bits/stdc++.h>
using namespace std;

int a[1005][1005];//差分数组
int sum[1005][1005];

void solve(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;++i){
        int lx,ly,rx,ry;
        cin>>lx>>ly>>rx>>ry;
        ++a[lx][ly];
        --a[rx+1][ly];
        --a[lx][ry+1];
        ++a[rx+1][ry+1];
    }

    //二维前缀和还原
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            sum[i][j]=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1]+a[i][j];
            printf("%d ",sum[i][j]);
        }
        printf("\n");
    }
}

int main(){
    solve();

    return 0;
}
