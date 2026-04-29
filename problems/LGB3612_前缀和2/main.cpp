//前缀和
#include <bits/stdc++.h>
using namespace std;

int n,m;
int vec[100005];
int sum[100005];

int main() {
    //init
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d",&vec[i]);
    scanf("%d",&m);

    //main logic
    sum[1]=vec[1];
    for(int i=2;i<=n;++i){
        sum[i]=sum[i-1]+vec[i];
    }

    for(int i=0;i<m;++i){
        int l,r;
        scanf("%d %d",&l,&r);
        printf("%d\n",sum[r]-sum[l-1]);
    }

    return 0;
}
