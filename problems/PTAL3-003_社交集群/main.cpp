#include<bits/stdc++.h>
using namespace std;

int find(int*parent,int num,int i){
    if(parent[i]!=i){
        parent[i]=find(parent,num,parent[i]);
    }
    return parent[i];
}

void myUnion(int*parent,int*rank,int num,int i,int j){
    int ip=find(parent,num,i);
    int jp=find(parent,num,j);
    if(ip==jp) return;
    if(rank[ip]<rank[jp]) parent[ip]=jp;
    else if(rank[jp]<rank[ip]) parent[ip]=jp;
    else{
        parent[ip]=jp;
        ++rank[jp];
    }
}

void solve(){
    int parent[1005]; //person's group
    int rank[1005]; //to union
    int hobby[1005];    //to locate person
    int gronum[1005];   //to count member numnber of group
    //init
    int n;
    cin>>n;
    for(int i=0;i<1005;++i){
        parent[i]=i;
        rank[i]=0;
        hobby[i]=-1;
        gronum[i]=0;
    }
    //main logic
    for(int i=0;i<n;++i){
        int num=1;
        char tra;
        cin>>num>>tra;
        for(int j=0;j<num;++j){
            int tmp;
            cin>>tmp;
            if(hobby[tmp]==-1)
                hobby[tmp]=i;
            else{
                myUnion(parent,rank,num,i,hobby[tmp]);
            }
        }
    }
    //count member num in group
    for(int i=0;i<n;++i){
        int gn=find(parent,n,i);
        ++gronum[gn];
    }
    vector<int>ans;
    for(int i=0;i<n;++i){
        if(gronum[i]>0) ans.push_back(gronum[i]);
    }
    printf("%d\n",(int)ans.size());
    sort(ans.begin(),ans.end(),[](int a,int b){return a>=b;});
    for(int i=0;i<ans.size();++i){
        if(i!=ans.size()-1) printf("%d ",ans[i]);
        else printf("%d",ans[i]);
    }
}

int main(){
    solve();

    return 0;
}
