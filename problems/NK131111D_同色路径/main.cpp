#include<bits/stdc++.h>
using namespace std;
//link front star
int head[200005],len[200005],c[200005],cnt;
bool visited[200005];
struct Edge{
    int v,next;
}edge[2*200005+5];

void addEdge(int u,int v){
    edge[cnt].v=v;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}

void solve(){
    //init
    int n=0;
    long long ans=0;
    cin>>n;
    fill(head,head+n+5,-1);
    fill(len,len+n+5,0);
    fill(c,c+n+5,-1);
    fill(visited,visited+n+5,false);
    cnt=0;
    //get color
    for(int i=1;i<=n;++i) cin>>c[i];
    //make link front star
    for(int i=0;i<n-1;++i){
        int u,v;
        cin>>u>>v;
        addEdge(u,v);
        addEdge(v,u);
    }
    //bfs
    queue<int>q;
    q.push(1);
    visited[1]=true;
    len[1]=1;
    while(!q.empty()){
        auto u=q.front();
        q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            int v=edge[i].v;
            if(visited[v]==true) continue; //ignore parent vertex
            visited[v]=true;
            if(c[v]==c[u]) len[v]=len[u]+1;
            else len[v]=1;
            ans+=len[v]-1;
            q.push(v);
        }
    }
    printf("%lld\n",ans);
}

int main(){
    int q;
    cin>>q;
    while(q--) solve();
}
