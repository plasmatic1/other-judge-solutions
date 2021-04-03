// ./problem-1-sum-of-distances.yml
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

struct Graph {
    int N, M;
    vector<vector<int>> g;
    vector<vector<int>> dis;
    void init(int n0, int m0) {
        N = n0; M = m0;
        g.resize(N+1);
        dis.assign(N+1, vector<int>(2, INF));
        dis[1][0] = 0;
    }
    void bfs() {
        queue<pii> q;
        q.emplace(1, 0);
        while (!q.empty()) {
            auto c = q.front(); q.pop();
            int alt = dis[c.fs][c.sn] + 1;
            for (auto to : g[c.fs]) {
                int altm = !c.sn;
                if (dis[to][altm] == INF) {
                    dis[to][altm] = alt;
                    q.emplace(to, altm);
                }
            }
        }
    }
};

struct DIS {
    int dis, gno, u, m; 
    bool operator<(const DIS &o) const {
        return dis < o.dis;
    }
};

const int MK = 5e4 + 1, MN = 1e5 + 1;
int K;
vector<bool> use[MK];
Graph gs[MK];

int cnt[MK][2], ready[2], cntBoth[MK], readyBoth;
ll prod[2] = {1, 1}, prodBoth = 1;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<DIS> ds;
    int maxdis = 0;

    cin >> (K);
    for (auto i = 0; i < K; i++) {
        auto &g = gs[i];
        int n, m;
        cin >> n >> m;
        g.init(n, m);
        use[i].resize(n+1);
        for (auto j = 0; j < m; j++) {
            int a, b;
            cin >> a >> b;
            g.g[a].pb(b);
            g.g[b].pb(a);
        }
        g.bfs();
        for (auto j = 1; j <= n; j++) {
            for (auto k = 0; k < 2; k++) {
                if (g.dis[j][k] != INF) {
                    ds.pb({g.dis[j][k], i, j, k});
                    maxa(maxdis, g.dis[j][k]);
                }
            }
        }
    }
    sort(all(ds));

    int ptr = 0;
    ll ans = 0, pre = 0;
    for (auto i = 0; i <= maxdis; i++) {
        while (ptr < SZ(ds) && ds[ptr].dis <= i) {
            auto &nd = ds[ptr];

            // update prods
            if (!cnt[nd.gno][nd.m]) ready[nd.m]++;
            else prod[nd.m] = fix(prod[nd.m] * inv(cnt[nd.gno][nd.m]));
            cnt[nd.gno][nd.m]++;
            prod[nd.m] = fix(prod[nd.m] * cnt[nd.gno][nd.m]);

            // update both prods
            if (use[nd.gno][nd.u]) {
                if (!cntBoth[nd.gno]) readyBoth++;
                else prodBoth = fix(prodBoth * inv(cntBoth[nd.gno]));
                cntBoth[nd.gno]++;
                prodBoth = fix(prodBoth * cntBoth[nd.gno]);
            }

            use[nd.gno][nd.u] = true;
            ptr++;
        }
        // cout<<"i="<<(i)<<", "; cout << endl; // db i
        // for (auto j = 0; j < K; j++) {
        //     cout<<"j="<<(j)<<", "; cout<<"cnt[j][0]="<<(cnt[j][0])<<", "; cout<<"cnt[j][1]="<<(cnt[j][1])<<", "; cout<<"cntBoth[j]="<<(cntBoth[j])<<", "; cout << endl; // db j,cnt[j][0],cnt[j][1],cntBoth[j]
        // }
        // cout<<"prod[0]="<<(prod[0])<<", "; cout<<"prod[1]="<<(prod[1])<<", "; cout<<"prodBoth="<<(prodBoth)<<", "; cout<<"ready[0]="<<(ready[0])<<", "; cout<<"ready[1]="<<(ready[1])<<", "; cout<<"readyBoth="<<(readyBoth)<<", "; cout << endl; // db prod[0],prod[1],prodBoth,ready[0],ready[1],readyBoth

        ll cprod[2], cprodBoth;
        for (auto j = 0; j < 2; j++)
            cprod[j] = (ready[j] == K) * prod[j];
        cprodBoth = (readyBoth == K) * prodBoth;
        
        ll cur = cprod[0] + cprod[1] - cprodBoth;
        ans = fix(ans + i * (cur - pre));
        // cout<<"cprod[0]="<<(cprod[0])<<", "; cout<<"cprod[1]="<<(cprod[1])<<", "; cout<<"cprodBoth="<<(cprodBoth)<<", "; cout<<"cur="<<(cur)<<", "; cout<<"pre="<<(pre)<<", "; cout << endl; // db cprod[0],cprod[1],cprodBoth,cur,pre
        pre = cur;
    }
    assert(ptr == SZ(ds));
    
    cout << (ans) << '\n';

    return 0;
}

