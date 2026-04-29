#include<bits/stdc++.h>
using namespace std;
#define MAXSIZE 10000000
int a[MAXSIZE+5],b[MAXSIZE+5],c[MAXSIZE+5];
string as,bs;

int init(int*num,string&s){
    cin>>s;
    int size=s.size();
    for(int i=s.size()-1;i>=0;--i){
        num[size-1-i]=s[i]-'0'; //reverse saved number
    }
    return size;
}

void solve_add(){
    int la=init(a,as);
    int lb=init(b,bs);
    int lc=max(la,lb)+1;
    //add
    for(int i=0;i<lc;++i){
        c[i]+=a[i]+b[i];
        if(c[i]>=10){
            c[i]-=10;
            ++c[i+1];
        }
    }
    //address pre-zero
    --lc;
    while(lc>0 && c[lc]==0) --lc;
    for(int i=lc;i>=0;--i) printf("%d",c[i]);
    printf("\n");
}

void solve_minus(){
    int la=init(a,as);
    int lb=init(b,bs);
    int lc=max(la,lb);
    int*big=a,*small=b;
    //judge which one is greater
    if(la<lb||(la==lb && as<bs)){
        big=b;
        small=a;
    }
    //minus
    for(int i=0;i<lc;++i){
        c[i]+=big[i]-small[i];
        if(c[i]<0){
            c[i]+=10;
            --c[i+1];
        }
    }
    //address pre-zero
    --lc;
    while(lc>0&&c[lc]==0) --lc;
    if(c[lc]!=0) printf("-");
    for(int i=lc;i>=0;--i) printf("%d",c[i]);
    printf("\n");
}

int main(){
    int num;
    cin>>num;
    if(num==0) solve_add();
    else solve_minus();
    return 0;
}