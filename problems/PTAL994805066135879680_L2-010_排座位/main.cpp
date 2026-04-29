//find-union
#include<bits/stdc++.h>
using namespace std;
#define INF 200005

int parent[105]; //friend relationship
int my_rank[105];
int haster[105][105];

int find(int i){
    if(parent[i]!=i){
        parent[i]=find(parent[i]);
    }
    return parent[i];
}

void my_union(int i,int j){
    int pi=find(i),pj=find(j);
    if(pi==pj) return;
    if(my_rank[pi]<my_rank[pj]){
        parent[pi]=pj;
    }
    else if(my_rank[pj]<my_rank[pi]){
        parent[pj]=pi;
    }
    else{
        parent[pi]=pj;
        ++my_rank[pj];
    }
}

void giveAns(int i,int j){
    int pi=find(i),pj=find(j);
    if(pi==pj && haster[i][j]!=1){
        printf("No problem\n");
    }
    else if(pi!=pj && haster[i][j]!=1){
        printf("OK\n");
    }
    else if(pi==pj && haster[i][j]==1){
        printf("OK but...\n");
    }
    else if(haster[i][j]==1){
        printf("No way\n");
    }
}

void solve(){
    int n,m,k;
    cin>>n>>m>>k;
    //init find-union
    for(int i=0;i<n;++i){
        parent[i]=i;
        my_rank[i]=0;
    }
    //get data
    int u,v,w;
    for(int i=0;i<m;++i){
        cin>>u>>v>>w;
        if(w==1) my_union(u-1,v-1);
        else if(w==-1){
            haster[u-1][v-1]=1;
            haster[v-1][u-1]=1;
        }
    }
    //ask
    for(int i=0;i<k;++i){
        int u,v;
        cin>>u>>v;
        giveAns(u-1,v-1);
    }
}

int main(){
    solve();

    return 0;
}