#include<bits/stdc++.h>
using namespace std;

void solve(){
    int n;
    cin>>n;
    vector<int>vec(n,0);
    for(int i=0;i<n;++i) cin>>vec[i];
    sort(vec.begin(),vec.end(),[](int a,int b){return a<b;});
    if(n%2==0){
        double mid=(vec[n/2]+vec[n/2-1])/2.0;
        printf("中位数为：%.2f\n",mid);
    }
    else{
        double mid=vec[n/2];
        printf("中位数为：%.2f\n",mid);
    }
}

int main(){
    solve();
    return 0;
}