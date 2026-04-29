#include<bits/stdc++.h>
using namespace std;
int a[100005],b[100005],ans[100005];
string as,bs;
bool tag=0; //0-positive     1-negative

void init(int*num,string&str){
    cin>>str;
    if(str[0]=='-'){
        tag==0?tag=1:tag=0;
        str.erase(0,1);
    }
    for(int i=1;i<=str.size();++i){
        num[i]=str[str.size()-i]-'0';
    }
    //address pre-zero and update length of num
    int l=str.size();
    while(l>0&&num[l]==0)--l;
    num[0]=l;
}

//a[i]>=b[i] return true;
//       else false;
bool check(int*n,int*m){
    if(n[0]<m[0]) return false;
    else if(n[0]>m[0]) return true;
    for(int i=n[0];i>=1;--i){
        if(n[i]<m[i]) return false;
        else if(n[i]>m[i]) return true;
    }
    return true;
}

//garantee n>=m
void my_minus(int*n,int*m){
    for(int i=1;i<=n[0];++i){
        n[i]-=m[i];
        if(n[i]<0){
            n[i]+=10;
            --n[i+1];
        }
    }
    //address pre-zero
    int l=n[0];
    while(l>0&&n[l]==0) --l;
    n[0]=l;
}

void solve(){
    init(a,as);
    init(b,bs);
    if(!check(a,b)){
        printf("0\n");
        return;
    }
    ans[0]=a[0]-b[0]+1;
    for(int i=ans[0];i>=1;--i){
        int tmp[100005]={0};
        //pair the digit
        for(int j=1;j<=b[0];++j){
            tmp[j+i-1]=b[j];
        }
        tmp[0]=b[0]+i-1;
        while(check(a,tmp)){
            my_minus(a,tmp);
            ++ans[i];
        }
    }
    //address pre-zero
    int l=ans[0];
    while(l>0&&ans[l]==0) --l;
    ans[0]=l;
    if(tag==1) printf("-");
    for(int i=ans[0];i>=1;--i) printf("%d",ans[i]);
    printf("\n");
}

int main(){
    solve();

    return 0;
}