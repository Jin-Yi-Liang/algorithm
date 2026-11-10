#include<bits/stdc++.h>
using namespace std;
bool isprime[100005];
int prime[100005];
int cnt;

void solve(){
    int n;
    cnt=1;
    cin>>n;
    if(n>100000) return;
    isprime[1]=1;
    for(int i=2;i<=n;++i){
        if(isprime[i]==0){
            prime[cnt++]=i;
        }
        for(int j=1;j<cnt;++j){
            int tmp=i*prime[j];
            if(tmp>n)break;
            isprime[tmp]=1;
            if(i%prime[j]==0)break;
        }
    }
    for(int i=1;i<cnt;++i)printf("%d ",prime[i]);
}

int main(){
    solve();
    return 0;
}