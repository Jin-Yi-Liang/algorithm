//find-union
#include<bits/stdc++.h>
using namespace std;

void solve(){
    long long n;
    cin>>n;
    //calculate length
    int start=0,len=0;
    long long limitNum=sqrt(n);
    for(long long i=2;i<=limitNum;++i){
        long long prod=1;
        for(long long j=i;;++j){
            prod*=j;
            if(n%prod!=0) break;
            if(j-i+1>len){
                len=j-i+1;
                start=i;
            }
        }
    }
    if(len==0){
        printf("1\n%d\n",n);
    }
    else{
        printf("%d\n",len);
        for(int i=0;i<len;++i){
            if(i) printf("*");
            printf("%d",start+i);
        }
        printf("\n");
    }
}

int main(){
    solve();

    return 0;
}