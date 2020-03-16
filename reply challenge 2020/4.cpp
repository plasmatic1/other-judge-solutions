#include <bits/stdc++.h>
using namespace std;
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef pair<int,int> pii;

#define MAXN 1005
#define MOD 1000000007
#define MOD2 1494318097

int T,N,dp[MAXN];
ll hsh[2][MAXN],power[2][MAXN];
ll tmp[2][MAXN];
vector<pair<int,ll>> v;
string s;

inline ll substrHash(int l, int r, ll (&hsh)[2][MAXN]){
    ll f = (hsh[0][r]-(hsh[0][l-1]*power[0][r-l+1]%MOD)+MOD)%MOD;
    ll s = (hsh[1][r]-(hsh[1][l-1]*power[1][r-l+1]%MOD2)+MOD2)%MOD2;
    return (f<<31LL)+s;
}

int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    freopen("data.txt","r",stdin);
    freopen("data.out","w",stdout);
    cin >> T;
    for(int t=1; t<=T; t++){
        cin >> N >> s;
        power[0][0] = power[1][0] = 1;
        for(int i=1; i<=s.size(); i++){
            hsh[0][i] = (hsh[0][i-1]*131+s[i-1])%MOD;
            power[0][i] = (power[0][i-1]*131)%MOD;

            hsh[1][i] = (hsh[1][i-1]*131+s[i-1])%MOD2;
            power[1][i] = (power[1][i-1]*131)%MOD2;
        }
        v.clear();
        for(int i=1; i<=N; i++){
            string s; cin >> s;
            tmp[0][0] = tmp[1][0] = 1;
            for(int k=1; k<=s.size(); k++){
                tmp[0][k] = (tmp[0][k-1]*131+s[k-1])%MOD;
                tmp[1][k] = (tmp[1][k-1]*131+s[k-1])%MOD2;
            }
            for(int k=1; k<=s.size(); k++){
                ll sub = substrHash(k,s.size(),tmp);
                v.pb(mp((int)s.size()-k+1,sub));
            }
        }
        sort(v.begin(),v.end());
        v.resize(unique(v.begin(),v.end())-v.begin());
        memset(dp,0x3f,sizeof dp);
        dp[0] = 0;
        for(int i=1; i<=s.size(); i++){
            for(pair<int,ll> check:v){
                if(check.first > i) break;
                ll sub = substrHash(i-check.first+1,i,hsh);
                if(sub == check.second)
                    dp[i] = min(dp[i],dp[i-check.first]+1);
            }
        }
        printf("Case #%d: ",t);
        if(dp[s.size()] == 0x3f3f3f3f) printf("-1\n");
        else printf("%d\n",dp[s.size()]);
    }
}