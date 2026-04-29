//bellman-ford
#include<bits/stdc++.h>
using namespace std;

#define INF 1000005
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        int mindis[105],backup[105];
        for(int i=0;i<n;++i) mindis[i]=INF;
        mindis[src]=0;
        for(int i=0;i<=k;++i){
            for(int j=0;j<n;++j) backup[j]=mindis[j];
            for(auto&cur:flights){
                int u=cur[0],v=cur[1],w=cur[2];
                //always read from previoue round's distance
                backup[v]=min(backup[v],mindis[u]+w);
            }
            for(int j=0;j<n;++j) mindis[j]=backup[j];
        }
        return mindis[dst]>=INF?-1:mindis[dst];
    }
};

int main(){
    vector<vector<int>>vec({{0,1,100},{1,2,100},{2,0,100},{1,3,600},{2,3,200}});
    Solution s;
    int ans=s.findCheapestPrice(4,vec,0,3,1);
    printf("%d",ans);

    return 0;
}