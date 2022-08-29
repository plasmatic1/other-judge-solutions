// f.yml
#include <bits/stdc++.h>
#define DEBUG 0
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


// Example comparator: Range min + Range increment
// In the functions mergeLazy and applyLazy, objects are merged from `v` to `to`.  In the function merge, data is merged from left to right
struct Comp {
    using Data = ll;
    using Lazy = ll;
    const Data vdef = 0;
    const Lazy ldef = 0;
    Data merge(Data l, Data r) const { return max(l, r); }
    Lazy mergeLazy(Lazy to, Lazy v) const { return to + v; }
    void applyLazy(Data &to, Lazy &v, int l, int r) { to += v; }
};
#define MID int mid = (l + r) / 2, lhs = i + 1, rhs = i + (mid - l + 1) * 2;
template <class Comp> struct LazySegmentTree {
    using Data = typename Comp::Data; using Lazy = typename Comp::Lazy; Comp C;
    int N;
    vector<Data> seg; vector<Lazy> lazy;
    void init(int n0) {
        N = n0;
        seg.assign(2 * N + 2, C.vdef);
        lazy.assign(2 * N + 2, C.ldef);
    }
    void push(int i, int l, int r) {
        if (lazy[i] != C.ldef) {
            MID;
            C.applyLazy(seg[i], lazy[i], l, r);
            if (l != r) {
                lazy[lhs] = C.mergeLazy(lazy[lhs], lazy[i]);
                lazy[rhs] = C.mergeLazy(lazy[rhs], lazy[i]);
            }
            lazy[i] = C.ldef;
        }
    }
    Data _query(int ql, int qr, int i, int l, int r) {
        if (ql > r || qr < l) return C.vdef;
        push(i, l, r);
        if (l >= ql && r <= qr) return seg[i];
        MID;
        return C.merge(_query(ql, qr, lhs, l, mid), _query(ql, qr, rhs, mid + 1, r));
    }
    Data _update(int ql, int qr, Lazy v, int i, int l, int r) {
        push(i, l, r);
        if (ql > r || qr < l) return seg[i];
        if (l >= ql && r <= qr) {
            lazy[i] = v;
            push(i, l, r);
            return seg[i];
        }
        MID;
        return seg[i] = C.merge(_update(ql, qr, v, lhs, l, mid), _update(ql, qr, v, rhs, mid + 1, r));
    }
    Data _setPoint(int q, Data v, int i, int l, int r) {
        push(i, l, r);
        if (q > r || q < l) return seg[i];
        if (l >= q && r <= q) return seg[i] = v;
        MID;
        return seg[i] = C.merge(_setPoint(q, v, lhs, l, mid), _setPoint(q, v, rhs, mid + 1, r));
    }
    Data query(int ql, int qr) { return _query(ql, qr, 1, 1, N); }
    void update(int ql, int qr, Lazy v) { _update(ql, qr, v, 1, 1, N); }
    void setPoint(int q, Data v) { _setPoint(q, v, 1, 1, N); }
};

using T = tuple<int, int, int>; // i, l, r
const int MN = 3e5 + 1;
int N, Q;
ll A[MN], ans[MN];
vector<T> queriesAtRightEndpoint[MN];

int par[MN], in[MN], out[MN], ctr = 0;
LazySegmentTree<Comp> seg;
vector<int> g[MN];

void dfs(int c) {
    in[c] = ++ctr;
    for (auto to : g[c])
        dfs(to);
    out[c] = ctr;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    for (auto i = 1; i <= N; i++)
        cin >> A[i];

    for (auto i = 0; i < Q; i++) {
        int l, r; cin >> l >> r;
        queriesAtRightEndpoint[r].eb(i, l, r);
    }

    // build par array
    {
        deque<int> idxs;
        for (auto i = N; i >= 1; i--) {
            while (!idxs.empty() && A[idxs.back()] <= A[i]) {
                idxs.pop_back();
            }

            if (!idxs.empty())
                par[i] = idxs.back();
            else
                par[i] = -1;

            idxs.pb(i);

            if (DEBUG) { cout<<"i="<<(i)<<", "; cout<<"par[i]="<<(par[i])<<", "; cout << endl; } //__RAW_DEBUG_LINE__:db i,par[i]
        }
    }

    // build euler tour tree
    for (auto i = N; i >= 1; i--)
        g[par[i]].pb(i);
    for (auto i = N; i >= 1; i--)
        if (par[i] == -1)
            dfs(i);

    // build BIT
    seg.init(N);
    for (auto i = 1; i <= N; i++) {
        seg.update(in[i], out[i], A[i]);
        if (DEBUG) { cout<<"i="<<(i)<<", "; cout<<"in[i]="<<(in[i])<<", "; cout<<"out[i]="<<(out[i])<<", "; cout<<"A[i]="<<(A[i])<<", "; cout << endl; } //__RAW_DEBUG_LINE__:db i,in[i],out[i],A[i]
    }

    // for (auto i = 1; i <= N; i++) {
    //     if (DEBUG) { cout<<"i="<<(i)<<", "; cout<<"[initial DP]: "; cout<<"bit.query(in[i])="<<(bit.query(in[i]))<<", "; cout << endl; } //__RAW_DEBUG_LINE__:db i,l:initial DP,bit.query(in[i])
    // }

    // answer queries
    for (auto i = N; i >= 1; i--) {
        for (auto [qi, ql, qr] : queriesAtRightEndpoint[i]) {
            ans[qi] = seg.query(1, in[ql]);
        }

        seg.update(in[i], out[i], -A[i]);
    }

    for (auto i = 0; i < Q; i++)
        cout << (ans[i]) << '\n';

    return 0;
}
