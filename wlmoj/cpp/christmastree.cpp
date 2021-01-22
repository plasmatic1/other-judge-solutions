// ./rachels-christmas-tree.yml
#include "bits/stdc++.h"
using namespace std;

// Defines
#define fs first
#define sn second
#define pb push_back
#define eb emplace_back
#define mpr make_pair
#define mtp make_tuple
#define all(x) (x).begin(), (x).end()
// Basic type definitions
using ll = long long; using ull = unsigned long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<long long, long long>;
// PBDS order statistic tree
#include <ext/pb_ds/assoc_container.hpp> // Common file 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds; 
template <typename T, class comp = less<T>> using os_tree = tree<T, null_type, comp, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename V, class comp = less<K>> using treemap = tree<K, V, comp, rb_tree_tag, tree_order_statistics_node_update>;
// HashSet
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
const ll RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { ll operator()(ll x) const { return x ^ RANDOM; } };
template <typename T, class Hash> using hashset = gp_hash_table<T, null_type, Hash>;
template <typename K, typename V, class Hash> using hashmap = gp_hash_table<K, V, Hash>;
// More utilities
int SZ(string &v) { return v.length(); }
template <typename C> int SZ(C &v) { return v.size(); }
template <typename C> void UNIQUE(vector<C> &v) { sort(v.begin(), v.end()); v.resize(unique(v.begin(), v.end()) - v.begin()); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const ll MOD = 1e9 + 7;
ll fix(ll &&x) { x %= MOD; if (x < 0) x += MOD; return x; }
ll fix(ll &x) { x %= MOD; if (x < 0) x += MOD; return x; }
ll fpow(ll x, ll y, ll mod = MOD) {
    if (!y) return 1LL;
    return fpow(x * x % mod, y >> 1, mod) * ((y & 1) ? x : 1LL) % mod;
}
ll inv(ll x, ll mod = MOD) { return fpow(x, mod - 2, mod); }

const int MN = 1e4+10, MOD2 = 1e4+7;
int N, K;
int dp[2][MN];
string s;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (K) >> (s);
    dp[0][0] = 1;
    ll ans = 0;
    for (auto i = 0; i < N; i++) {
        int c = i&1, n = !c;
        memset(dp[n], 0, sizeof dp[n]);
        for (auto j = 0; j < MOD2; j++) {
            dp[n][j] = (dp[n][j] + dp[c][j]) % MOD;
            int nxtmod = ((j*10)+(s[i]-'0')) % MOD2;
            // if (dp[c][j]) {
            //     cout<<"i="<<(i)<<", "; cout<<"j="<<(j)<<", "; cout<<"dp[c][j]="<<(dp[c][j])<<", "; cout<<"nxtmod="<<(nxtmod)<<", "; cout<<"s[i]-'0'="<<(s[i]-'0')<<", "; cout << endl; // db i,j,dp[c][j],nxtmod,s[i]-'0'
            // }
            if (nxtmod==K)
                ans+=dp[c][j];
            dp[n][nxtmod] = (dp[n][nxtmod] + dp[c][j]) % MOD;
        }
        // for (auto j = 0; j < MOD2; j++) {
        //     if (dp[n][j]) {
        //         cout<<"i="<<(i)<<", "; cout<<"j="<<(j)<<", "; cout<<"dp[n][j]="<<(dp[n][j])<<", "; cout << endl; // db i,j,dp[n][j]
        //     }
        // }
        // ans += dp[n][K];
    }

    cout << fix(ans) << '\n';

    return 0;
}