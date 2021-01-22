#include "bits/stdc++.h"
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
template<typename T>
int sz(const T &a){return int(a.size());}

int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    set<string> words;
    string a;
    for(int i=0;i<n;i++){
        cin>>a;
        words.insert(a);
    }
    for(int i=0;i<m;i++){
        cin>>a;
        if(!words.count(a))printf("%d ",i+1);
    }
    return 0;
}