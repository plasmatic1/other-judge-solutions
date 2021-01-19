// ./an-extraordinarily-coordinated-christmas.yml
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

struct ed {
    int v, w;
};
struct Graph {
    using Edge = ed; // Edge object in adjacency list (i.e. vector<int> g[MN], Edge type would be int)
    int v(Edge &e) { return e.v; } // Returns the adjacent node in an edge object
};
template <class Graph> struct LCA {
    using Edge = typename Graph::Edge; Graph G;
    vector<int> dep;
    vector<Edge> *g;
    vector<vector<int>> tb;
    int N, lg;
    void dfs(int c, int p) {
        tb[0][c] = p;
        for (auto to : g[c]) {
            int v = G.v(to);
            if (v != p) {
                dep[v] = dep[c] + 1;
                dfs(v, c);
            }
        }
    }
    void init(int N0, vector<Edge> *g0) {
        N = N0; g = g0;
        lg = 31 - __builtin_clz(N) + 1;
        tb.assign(lg, vector<int>(N + 1, -1)); dep.assign(N + 1, 0);
        dfs(1, -1);
        for (auto i = 1; i < lg; i++) {
            for (auto j = 1; j <= N; j++) {
                int pp = tb[i - 1][j];
                tb[i][j] = pp == -1 ? -1 : tb[i - 1][pp];
            }
        }
    }
    int lca(int a, int b) {
        if (a == b) return a;
        if (dep[a] > dep[b]) swap(a, b);
        int delta = dep[b] - dep[a];
        for (auto i = 0; i < lg; i++)
            if ((delta >> i) & 1)
                b = tb[i][b];
        if (a == b) return a;
        for (auto i = lg-1; i >= 0; i--) {
            if (tb[i][a] != tb[i][b]) {
                a = tb[i][a];
                b = tb[i][b];
            }
        }
        return tb[0][a];
    }
};

const int MN = 1e5 + 1;
int N, Q;
vector<ed> g[MN];
LCA<Graph> lca;
ll dis1[MN], dis2[MN];

void dfs(int c, int p, ll dis[MN]) {
    for (auto to : g[c]) {
        if (to.v != p) {
            dis[to.v] = dis[c] + to.w;
            dfs(to.v, c, dis);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (Q);
    for (auto i = 0; i < N-1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].pb({b, c});
        g[b].pb({a, c});
    }
    lca.init(N, g);

    dfs(1, -1, dis1);
    int d1 = max_element(dis1, dis1 + N + 1) - dis1;
    dfs(d1, -1, dis1);
    int d2 = max_element(dis1, dis1 + N + 1) - dis1;
    dfs(1, -1, dis1);

    while (Q--) {
        int x;
        cin >> x;
        ll ans = 0;
        for (auto v : vector<int>{d1, d2}) {
            ll d = dis1[v] + dis1[x] - 2 * dis1[lca.lca(v, x)];
            maxa(ans, d);
        }
        cout << (ans) << '\n';
    }

    return 0;
}

