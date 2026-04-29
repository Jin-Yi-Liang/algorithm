#include<bits/stdc++.h>
using namespace std;
int w[2005][2005],sum[2005][2005];

void solve(){
    int n,m,lx,ly,rx,ry;
    cin>>n>>m;
    for(int i=0;i<m;++i){
        cin>>lx>>ly>>rx>>ry;
        ++w[lx][ly];
        --w[lx][ry+1];
        --w[rx+1][ly];
        ++w[rx+1][ry+1];
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+w[i][j];
            if(sum[i][j]%2==0) printf("0");
            else printf("1");
        }
        printf("\n");
    }

}

int main(){
    solve();

    return 0;
}