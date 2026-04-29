#include<bits/stdc++.h>
using namespace std;

void solve(){
    int n=0,k=0,num=0;
    cin>>n;
    vector<string>str(n);
    string words;
    for(int i=0;i<n;++i){
        cin>>str[i];
    }
    cin>>k;
    cin.ignore();
    getline(cin,words);
    vector<int>jump(words.size(),0);
    for(auto&cur:str){
        int index=0,len=cur.length();
        while((index=words.find(cur,index))!=string::npos){
            bool overwrite=0;
            for(int i=0;i<len;++i){
                if(jump[index+i]>0){
                    overwrite=1;
                    break;
                }
            }
            if(overwrite==0){
                ++num;
                for(int i=0;i<len;++i)jump[index+i]=len;
                index+=len;
            }
            else if(overwrite>0) ++index;
        }
    }
    if(num<k){
        int i=0;
        while(i<words.length()){
            if(jump[i]>0){
                printf("<censored>");
                i+=jump[i];
            }
            else{
                cout<<words[i];
                ++i;
            }
        }
    }
    else printf("%d\nHe Xie Ni Quan Jia!",num);
}

int main(){
    solve();

    return 0;
}
