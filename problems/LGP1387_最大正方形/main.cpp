#include<bits/stdc++.h>
using namespace std;

int num[105][105];
int sum[105][105];

void solve(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            cin>>num[i][j];
            sum[i][j]=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1]+num[i][j];
        }
    }
    int l=0,ans=0;
    int x=0,y=0;//left top point;
    //for right bottom point
    for(int l=1;l<=min(n,m);++l){
        for(int i=l;i<=n;++i){
            for(int j=l;j<=m;++j){
                x=i-l+1;y=j-l+1;
                if(sum[i][j]-sum[i][y-1]-sum[x-1][j]+sum[x-1][y-1]==l*l){
                    ans=max(ans,l);
                }
            }
        }
    }
    printf("%d\n",ans);
}

int main(){
    solve();

    return 0;
}
