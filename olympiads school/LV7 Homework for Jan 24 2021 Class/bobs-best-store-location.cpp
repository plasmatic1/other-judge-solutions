// ./bobs-best-store-location.yml
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

struct Graph {
    using Edge = pii; // Edge object in adjacency list (i.e. vector<int> g[MN], Edge type would be int)
    int v(Edge &e) { return e.fs; } // Returns the adjacent node in an edge object
    int w(Edge &e) { return e.sn; } // Returns the adjacent node in an edge object
};
template <class Graph> struct LCA {
    using Edge = typename Graph::Edge; Graph G;
    vector<int> dep, dis;
    vector<Edge> *g;
    vector<vector<int>> tb;
    int N, lg;
    void dfs(int c, int p) {
        tb[0][c] = p;
        for (auto to : g[c]) {
            int v = G.v(to);
            if (v != p) {
                dep[v] = dep[c] + 1;
                dis[v] = dis[c] + G.w(to);
                dfs(v, c);
            }
        }
    }
    void init(int N0, vector<Edge> *g0) {
        N = N0; g = g0;
        lg = 31 - __builtin_clz(N) + 1;
        tb.assign(lg, vector<int>(N + 1, -1)); dep.assign(N + 1, 0); dis.assign(N+1, 0);
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
    int qdis(int a, int b) {
        return dis[a] + dis[b] - 2 * dis[lca(a, b)];
    }
};

// Template is 1-indexed (by default).  Can be made 0-indexed by modifying Comp
// Default: Point increment and prefix sum query
struct Comp {
    using Data = ll;
    const Data vdef = 0;
    void applyUpdate(Data &to, Data &v) { to += v; }
    int transformInd(int idx, int N) { return idx; }
};
template <typename Comp> struct BIT {
    using Data = typename Comp::Data; Comp C;
    int N; vector<Data> bit;
    void init(int n0) {
        N = n0;
        bit.assign(N + 1, C.vdef);
    }
    void update(int x, Data v) {
        x = C.transformInd(x, N);
        for (; x <= N; x += x & -x)
            C.applyUpdate(bit[x], v);
    }
    Data query(int x) {
        x = C.transformInd(x, N);
        Data res = C.vdef;
        for (; x; x -= x & -x)
            C.applyUpdate(res, bit[x]);
        return res;
    }
};

const int MN = 1e5 + 1;
int N, Q;
vector<pii> g[MN];

LCA<Graph> lca;
int P[MN], dis[MN], sz[MN], in[MN], out[MN], cpos = 0;
ll parw[MN];
void dfs(int c, int p) {
    P[c] = p;
    in[c] = ++cpos;
    sz[c] = 1;
    for (auto to : g[c]) {
        if (to.fs != p) {
            dis[to.fs] = dis[c] + to.sn;
            parw[to.fs] = to.sn;
            dfs(to.fs, c);
            sz[c] += sz[to.fs];
        }
    }
    out[c] = cpos;
}
BIT<Comp> bit;

ll cans = 0;
int V = 1;

ll subt(int u) { return bit.query(out[u]) - bit.query(in[u] - 1); }
bool anc(int up, int dn) { return in[up] <= in[dn] && in[dn] <= out[up]; }

// move once!!!
void move(int k) {
    if (anc(V, k)) { // move down
        ll upa = subt(1) - subt(k);
        cans += upa * parw[k];
        cans -= subt(k) * parw[k];
    }
    else { // move up
        ll upa = subt(1) - subt(V);
        cans += subt(V) * parw[V];
        cans -= upa * parw[V];
    }
    V = k;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (Q);
    for (auto i = 0; i < N-1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].eb(v, w);
        g[v].eb(u, w);
    }

    lca.init(N, g);
    dfs(1, -1);
    bit.init(N);

    while (Q--) {
        int u; ll x;
        cin >> u >> x;
        bit.update(in[u], x);
        cans += x * lca.qdis(u, V);

        while (true) {
            int prenode = V;
            ll pre = cans;
            
            ll alt = LLINF;
            int best = -1;
            for (auto to : g[V]) {
                move(to.fs);
                if (cans < alt) {
                    alt = cans;
                    best = to.fs;
                }
                move(prenode);
            }

            if (alt < pre)
                move(best);
            else
                break;
        }

        cout << (cans) << '\n';
    }

    return 0;
}

