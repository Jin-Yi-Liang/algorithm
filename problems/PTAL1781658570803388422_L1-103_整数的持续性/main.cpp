#include<bits/stdc++.h>
using namespace std;
#define INF 200005

int func(int num){
    if(num<10) return 0;
    //use % to get every single number
    int nextNum=1;
    while(num>0){
        int tmp=num%10;
        num/=10;
        nextNum*=tmp;
    }
    return 1+func(nextNum);
}

void solve(){
    int a,b,len=0;
    vector<int>ans;
    cin>>a>>b;
    for(;a<=b;++a){
        int num=func(a);
        if(num>=len){
            if(num>len) ans.clear();
            len=num;
            ans.push_back(a);
        }
    }
    printf("%d\n",len);
    for(int i=0;i<ans.size();++i){
        if(i!=ans.size()-1) printf("%d ",ans[i]);
        else printf("%d",ans[i]);
    }
}

int main(){
    solve();

    return 0;
}