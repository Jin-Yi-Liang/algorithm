#include<bits/stdc++.h>
using namespace std;
int a[100005],b[100005],ans[200005];
string as,bs;
bool tag=1;

int init(int*num,string str){
    cin>>str;
    if(str[0]=='-'){
        tag==0?tag=1:tag=0;
        str.erase(0,1);
    }
    for(int i=0;i<str.size();++i){
        num[i]=str[str.size()-i-1]-'0';//reverse saved
    }
    return str.size();
}

void solve(){
    int la=init(a,as);
    int lb=init(b,bs);
    int lc=la+lb;
    for(int i=0;i<la;++i){
        for(int j=0;j<lb;++j){
            ans[i+j]+=a[i]*b[j];
        }
    }
    for(int i=0;i<lc;++i){
        ans[i+1]+=ans[i]/10;
        ans[i]%=10;
    }
    if(tag==0)printf("-");
    //address pre-zero
    --lc;
    while(lc>0&&ans[lc]==0)--lc;
    for(int i=lc;i>=0;--i)printf("%d",ans[i]);
    printf("\n");
}

int main(){
    solve();

    return 0;
}