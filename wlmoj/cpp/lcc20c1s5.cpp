#include "bits/stdc++.h"
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using ld = long double;
template<typename T>
int sz(const T &a){return int(a.size());}
const int MAXN=1e6+1;
vector<int> matrix[MAXN];
ld dp[MAXN][2];//probability that alan will reach i from its subtree. or from above;
int n;
void dfs(int loc, int par){
    dp[loc][0]=0;
    for(auto x:matrix[loc]){
        if(x!=par){
            dfs(x,loc);
            dp[loc][0]+=dp[x][0]*(ld(1)/ld(sz(matrix[x])))+(ld(1)/ld(n))*(ld(1)/ld(sz(matrix[x])+1));
        }
    }
}
void dfs2(int loc, int par){
    if(par==0)dp[loc][1]=0;
    else dp[loc][1]=(dp[par][1]+dp[par][0]-(dp[loc][0]*(ld(1)/ld(sz(matrix[loc])))+(ld(1)/ld(n))*(ld(1)/ld(sz(matrix[loc])+1))))*(ld(1)/ld(sz(matrix[par])))+(ld(1)/ld(n))*(ld(1)/ld(sz(matrix[par])+1));
    for(auto x:matrix[loc])if(x!=par)dfs2(x,loc);
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin>>n;
    int a,b;
    for(int i=1;i<n;i++){
        cin>>a>>b;
        matrix[a].push_back(b);
        matrix[b].push_back(a);
    }
    dfs(1,0),dfs2(1,0);
    for(int i=1;i<=n;i++){
        printf("%.11f ",(double)((dp[i][0]+dp[i][1])*(ld(1)/ld(sz(matrix[i])))+(ld(1)/ld(n))*ld(1)/ld(sz(matrix[i])+1)));
    }
    return 0;
}