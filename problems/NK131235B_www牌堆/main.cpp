// B - www牌堆
// Platform: 牛客网
// Category: 模拟
// Date: 2026-03-24

#include <bits/stdc++.h>
using namespace std;

int T,n;

int main() {
    scanf("%d",&T);
    while(T--){
        //init
        long long x=0,cur=0,delta=0,card=0,maxneed=0;
        bool canrun=1;
        scanf("%d %d",&n,&x);
        vector<int>a(n,0),b(n,0);
        for(int i=0;i<n;++i)
            scanf("%d",&a[i]);
        for(int i=0;i<n;++i)
            scanf("%d",&b[i]);

        //main logic
        for(int i=0;i<n;++i){
            if(x-cur>=a[i]){
                cur+=a[i]-b[i];
                delta+=(a[i]-b[i]);
                maxneed=max(maxneed,cur);
                ++card;
            }
            else{
                canrun=0;
                break;
            }
        }
        //can not finish one loop
        if(canrun==0)
            printf("%lld\n",card);
        //infinity
        else if(delta<=0)
            printf("Infinity\n");
        //will stop soon
        else{
            //calculate remain loop
            //two devide to find the boundary
            long long lo=0,hi=2e13;
            while(lo<hi){
                long long mid=(lo+hi+1)/2;
                if(x-mid*delta>=a[0])
                    lo=mid;
                else
                    hi=mid-1;
            }
            
            //can run lo loops,and run the last loop
            long long remX=x-lo*delta;
            long long last=0;
            for(int i=0;i<n;++i){
                if(remX<a[i]) break;
                remX+=b[i]-a[i];
                last++;
            }
            printf("%lld\n",lo*n+last);
        }
    }   

    return 0;
}
