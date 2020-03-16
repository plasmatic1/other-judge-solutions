#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef pair<int,int> pii;
typedef pair<lli,lli> pll;
template<typename T>
int sz(const T &a){return (int)a.size();}
const int MAXN=1e5+1;
int n,k;
lli m;
pll servers[MAXN];
bool work(lli time){
    priority_queue<lli> machines;
    for(int i=0;i<n;i++){
        machines.push((time-servers[i].first)/servers[i].second);
    }
    lli am=0;
    for(int i=0;i<k;i++)am+=machines.top(),machines.pop();
    return am>=m;
}
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    freopen("input-scheduler-e703.txt","r",stdin);
    freopen("Ans.txt","w",stdout);
    int t;
    cin>>t;
    int cs=1;
    while(t--){
        cin>>n>>k>>m;
        for(int i=0;i<n;i++){
            cin>>servers[i].first>>servers[i].second;
        }
        lli lo=0;
        lli hi=1e15;
        while(lo!=hi){
            lli mid=(lo+hi)/2;
            if(work(mid))hi=mid;
            else lo=mid+1;
        }
        printf("Case #%d: %lli\n",cs,lo);
        cs++;
    }
    return 0;
}