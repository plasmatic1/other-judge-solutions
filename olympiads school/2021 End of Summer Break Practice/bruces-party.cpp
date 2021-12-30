// ./bruces-party.yml
#include <bits/stdc++.h>
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
#if __cplusplus == 201703L // CPP17 only things
template <typename T> using opt_ref = optional<reference_wrapper<T>>; // for some templates
#endif
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

struct Edge {
    using EdgeType = int;
    int v(EdgeType e) { return e; }
    int w(EdgeType e) { return 1; }
    int i(EdgeType e) { throw domain_error("no information on edge indices"); }
    EdgeType swapNode(EdgeType e, int v) { return v; }
};
template <typename T> struct WeightedEdge {
    using EdgeType = pair<int, T>; using WeightType = T;
    int v(EdgeType e) { return e.first; }
    T w(EdgeType e) { return e.second; }
    int i(EdgeType e) { throw domain_error("no information on edge indices"); }
    EdgeType swapNode(EdgeType e, int v) { return {v, w(e)}; }
};
struct IndexedEdge {
    using EdgeType = pair<int, int>;
    int v(EdgeType e) { return e.first; }
    int w(EdgeType e) { return 1; }
    int i(EdgeType e) { return e.second; }
    EdgeType swapNode(EdgeType e, int v) { return {v, i(e)}; }
};
template <typename T> struct WeightedIndexedEdge {
    using EdgeType = tuple<int, T, int>; using WeightType = T;
    int v(EdgeType e) { return get<0>(e); }
    T w(EdgeType e) { return get<1>(e); }
    int i(EdgeType e) { return get<2>(e); }
    EdgeType swapNode(EdgeType e, int v) { return {v, w(e), i(e)}; }
};

template <typename GraphType, typename EdgeType> vector<typename EdgeType::WeightType> dijkstra(int N, GraphType &g, initializer_list<int> start, typename EdgeType::WeightType initDis) {
    static EdgeType E;
    using w_t = typename EdgeType::WeightType; using st = pair<w_t, int>;
    vector<w_t> dis(N+1, initDis);
    priority_queue<st, vector<st>, greater<st>> pq;
    for (auto s : start) {
        pq.emplace(0, s);
        dis[s] = 0;
    }
    while (!pq.empty()) {
        auto [w, c] = pq.top(); pq.pop();
        if (w > dis[c]) continue;
        for (auto _to : g[c]) {
            int to = E.v(_to); w_t alt = dis[c] + E.w(_to);
            if (alt < dis[to]) {
                dis[to] = alt;
                pq.emplace(alt, to);
            }
        }
    }
    return dis;
}

// template is 1-indexed
template <typename T> struct Ranks {
    vector<T> ranks;
    void init() {
        sort(ranks.begin(), ranks.end());
        ranks.resize(unique(ranks.begin(), ranks.end()) - ranks.begin());
    }
    template <typename It> void init(It st, It en) { ranks = vector<T>(st, en); init(); }
    void add(T v) { ranks.push_back(v); }
    int get(T v) { return lower_bound(ranks.begin(), ranks.end(), v) - ranks.begin() + 1; }
    int size() { return ranks.size(); }
};

const int MN = 2e5 + 1;
int N, M, K, Q,
    G[MN];
vector<pair<int, ll>> g[MN];
Ranks<ll> rs;
Ranks<int> crs;

const int MNODE = 8500001;
struct Node {
    int l, r;
    int sum;
} ns[MNODE];

int ptr = 0;
int mk(int v) {
    ptr++;
    assert(ptr < MNODE);
    ns[ptr].sum = v;
    return ptr;
}
int mk(int l, int r) {
    ptr++;
    assert(ptr < MNODE);
    ns[ptr].sum = ns[l].sum + ns[r].sum;
    ns[ptr].l = l;
    ns[ptr].r = r;
    return ptr;
}

int build(int l=1, int r=SZ(rs)) {
    if (l == r) return mk(0);
    int mid = (l+r) / 2;
    return mk(build(l, mid), build(mid+1, r));
}
int update(int rt, int q, int v, int l=1, int r=SZ(rs)) {
    if (q == l && q == r) return mk(ns[rt].sum + v);
    int mid = (l+r) / 2;
    if (q <= mid) return mk(update(ns[rt].l, q, v, l, mid), ns[rt].r);
    else return mk(ns[rt].l, update(ns[rt].r, q, v, mid+1, r));
}
int query(int rt, int ql, int qr, int l=1, int r=SZ(rs)) {
    if (ql > r || qr < l) return 0;
    if (ql <= l && r <= qr) return ns[rt].sum;
    int mid = (l+r) / 2;
    return query(ns[rt].l, ql, qr, l, mid) + query(ns[rt].r, ql, qr, mid+1, r);
}

int rt[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> K >> Q;
    for (auto i = 2; i <= N; i++) {
        cin >> G[i];
        crs.add(G[i]);
    }
    for (auto i = 0; i < K; i++) {
        int b, t; cin >> b >> t;
        b++;
        g[1].eb(b, t);
    }
    for (auto i = 0; i < M; i++) {
        int u, v, w; cin >> u >> v >> w;
        u++; v++;
        g[v].eb(u, w);
    }

    // dijk and rank compress
    auto dis = dijkstra<vector<pair<int, ll>>[MN], WeightedEdge<ll>>(N, g, {1}, LLINF);
    for (auto i = 2; i <= N; i++)
        rs.add(dis[i]);
    rs.init();
    crs.init();

    // build pseg
    rt[0] = build();
    vector<set<int>> gs(N+1);
    for (auto i = 2; i <= N; i++) {
        int c = crs.get(G[i]), v = rs.get(dis[i]);
        gs[v].insert(c);
    }
    vector<int> lst(N+1, -1);
    for (auto i = 1; i <= SZ(rs); i++) {
        rt[i] = rt[i-1];
        for (auto v : gs[i]) {
            if (lst[v] != -1)
                rt[i] = update(rt[i], lst[v], -1);
            rt[i] = update(rt[i], lst[v] = i, 1);
        }
    }

    // cout << "dis=["; for (auto __x:dis)cout<<__x<<", "; cout<<"], "; cout << endl; // db I:dis

    ll lastAns = 0;

    while (Q--) {
        ll l, r; cin >> l >> r; l ^= lastAns; r ^= lastAns;

        l = lower_bound(all(rs.ranks), l) - rs.ranks.begin() + 1;
        r = upper_bound(all(rs.ranks), r) - rs.ranks.begin();

        // cout<<"l="<<(l)<<", "; cout<<"r="<<(r)<<", "; cout << "rs.ranks=["; for (auto __x:rs.ranks)cout<<__x<<", "; cout<<"], "; cout << endl; // db l,r,I:rs.ranks

        int cnt = query(rt[r], l, r);

        cout << (cnt) << '\n';
#ifndef LOCAL
        lastAns = cnt;
#endif
    }

    return 0;
}
