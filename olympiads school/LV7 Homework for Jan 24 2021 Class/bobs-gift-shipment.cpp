// ./bobs-gift-shipment.yml
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

const int MN = 1e5 + 1;
struct Line {
    ll m, b;
    ll eval(ll x) { return m * x + b; }
};
ostream& operator<<(ostream& out, const Line o) {
    out << "(m=" << o.m << ", b=" << o.b << ")";
    return out;
}
struct Node {
    Line val;
    int l, r;
};

Node seg[3100000];
int ptr = 0;
int make() {
    Node &n = seg[++ptr];
    n.l = n.r = 0; 
    n.val = {INF, INF};
    return ptr;
}

struct Change {
    int id;
    int idx;
    Node old;
};

int QID = 0, changeSz = -1;
Change cs[3100001];
void rollback(int first) {
    while (changeSz >= 0 && cs[changeSz].id > first) {
        auto &bk = cs[changeSz];
        seg[bk.idx] = bk.old;
        changeSz--;
    }
}

void update(int &rt, Line ln, int qid, int l = 0, int r = int(1e9)) {
    if (!rt) {
        rt = make();
        cs[++changeSz] = {qid, rt, seg[rt]};
        seg[rt].val = ln;
        return;
    }
    cs[++changeSz] = {qid, rt, seg[rt]};
    
    int mid = (l + r) / 2;
    bool lCmp = seg[rt].val.eval(l) > ln.eval(l),
         mCmp = seg[rt].val.eval(mid) > ln.eval(mid);
    if (mCmp) swap(seg[rt].val, ln);
    if (l != r) {
        if (lCmp != mCmp) update(seg[rt].l, ln, qid, l, mid);
        else update(seg[rt].r, ln, qid, mid+1, r);
    }
}
ll query(int &rt, int x, int l = 0, int r = int(1e9)) {
    if (rt == 0) return LLINF;
    int mid = (l + r) / 2;
    if (x <= mid) return min(seg[rt].val.eval(x), query(seg[rt].l, x, l, mid));
    return min(seg[rt].val.eval(x), query(seg[rt].r, x, mid+1, r));
}

int rt = 0;

int N;
ll P[MN], S[MN], dp[MN], dis[MN];
vector<pii> g[MN];

void dfs(int c, int p) {
    int cqid = ++QID;
    ll x = S[c], Const = S[c] * dis[c] + P[c];
    if (c != 1)
        dp[c] = query(rt, x) + Const;
    ll m = -dis[c], b = dp[c];
    update(rt, Line{m, b}, cqid);

    for (auto to : g[c]) {
        if (to.fs != p) {
            dis[to.fs] = dis[c] + to.sn;
            dfs(to.fs, c);
        }
    }

    rollback(cqid-1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    for (auto i = 0; i < N-1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].eb(v, w);
        g[v].eb(u, w);
    }
    for (int i = 2; i <= N; i++) cin >> P[i] >> S[i];

    dfs(1, -1);
    for (auto i = 2; i <= N; i++) cout << dp[i] << ' ';
    cout << '\n';

    return 0;
}

