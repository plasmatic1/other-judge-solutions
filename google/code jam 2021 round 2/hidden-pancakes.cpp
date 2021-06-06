// ./hidden-pancakes.yml
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
#ifdef __GNUG__
// PBDS order statistic tree
#include <ext/pb_ds/assoc_container.hpp> // Common file 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds; 
template <typename T, class comp = less<T>> using os_tree = tree<T, null_type, comp, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename V, class comp = less<K>> using treemap = tree<K, V, comp, rb_tree_tag, tree_order_statistics_node_update>;
// HashSet
#include <ext/pb_ds/assoc_container.hpp>
template <typename T, class Hash> using hashset = gp_hash_table<T, null_type, Hash>;
template <typename K, typename V, class Hash> using hashmap = gp_hash_table<K, V, Hash>;
const ll RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { ll operator()(ll x) const { return x ^ RANDOM; } };
#endif
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
// N choose R
vector<ll> fact, invf;
void init_nchooser(int MN) {
    fact.resize(MN + 1); invf.resize(MN + 1);
    fact[0] = 1LL;
    for (int i = 1; i <= MN; i++) fact[i] = fix(fact[i - 1] * i);
    invf[MN] = inv(fact[MN]);
    for (auto i = MN-1; i >= 0; i--) invf[i] = fix(invf[i + 1] * (i + 1));
}
ll choose(ll N, ll K) { return fix(fact[N] * fix(invf[K] * invf[N - K])); }
ll permute(ll N, ll K) { return fix(fact[N] * invf[N - K]); }

const int MN = 1e5 + 1;
int N,
    V[MN];

int sz[MN], dp[MN], par[MN];
vector<int> g[MN], rg[MN];
ll ans;

void dfs(int c) {
    if (dp[c] != -1) return;
    dp[c] = -INF;
    for (auto to : rg[c]) {
        dfs(to);
        int alt = dp[to]+1;
        // printf("c=%d to=%d dpto=%d alt=%d\n", c,to,dp[to],alt);
        if (alt > dp[c]) {
            dp[c] = alt;
            par[c] = to;
        }
    }
}
void dfs2(int c) {
    sz[c] = 1;
    ll comb = 1;
    for (auto to : g[c]) {
        if (par[to] == c) {
            dfs2(to);
            sz[c] += sz[to];

            comb = comb * invf[sz[to]] % MOD;
        }
    }
    comb = comb * fact[sz[c]-1] % MOD;
    ans = ans * comb % MOD;
}

void solve() {
    cin >> N;
    for (auto i = 1; i <= N; i++) cin >> V[i];
    for (auto i = 2; i <= N; i++) {
        if (V[i]-V[i-1] >= 2) {
            cout << "0\n";
            return;
        }
    }

    vector<int> stk{0};
    for (auto i = 1; i <= N; i++) {
        int lst = -1;
        while (stk.size() > V[i]) {
            lst = stk.back();
            stk.pop_back();
        }
        g[stk.back()].push_back(i);
        rg[i].push_back(stk.back());

        if (lst != -1) {
            g[i].push_back(lst);
            rg[lst].push_back(i);
        }

        stk.push_back(i);
    }

    ans = 1;
    fill(dp, dp+N+1, -1);
    dp[0] = 0;
    for (auto i = 1; i <= N; i++)
        dfs(i);
    // for (auto i = 1; i <= N; i++)
    //     printf("i=%d par=%d\n", i,par[i]);
    dfs2(0);
    cout << ans << '\n';

    // clearing things
    ans = 0;
    for (auto i = 0; i <= N; i++) {
        g[i].clear();
        rg[i].clear();
        sz[i] = dp[i] = par[i] = 0;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_nchooser(MN+10);

    int T;
    cin >> T;
    for (int caseno = 1; caseno <= T; caseno++) {
        // Input
       
        cout << "Case #" << caseno << ": ";
        solve();

        // Reset
    }
}

