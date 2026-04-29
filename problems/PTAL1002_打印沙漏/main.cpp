#include<bits/stdc++.h>
using namespace std;

void solve(){
    int n=0,remain=0,h=0;
    char ch;
    cin>>n>>ch;
    h=sqrt((n+1)/2);
    remain=n-(2*h*h-1);
    for(int i=h;i>=1;--i){
        for(int j=0;j<h-i;++j) printf(" ");
        for(int j=0;j<2*i-1;++j) printf("%c",ch);
        if(n>=7)printf("\n");
    }
    for(int i=2;i<=h;++i){
        for(int j=0;j<h-i;++j) printf(" ");
        for(int j=0;j<2*i-1;++j) printf("%c",ch);
        if(i!=h)printf("\n");
    }
    printf("\n%d",remain);
}

int main(){
    solve();

    return 0;
}
