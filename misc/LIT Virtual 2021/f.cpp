// f.yml
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
template <typename GraphType, typename EdgeType> struct LCABinaryLift {
    EdgeType E;
    int lg;
    vector<int> dep;
    vector<vector<int>> tb;
    void init(int N, GraphType &g, int rt) {
        lg = 31 - __builtin_clz(N) + 1;
        tb.assign(lg, vector<int>(N + 1, -1)); dep.assign(N + 1, 0);
        function<void(int, int)> dfs = [&] (int c, int p) {
            tb[0][c] = p;
            for (auto to : g[c]) {
                int v = E.v(to);
                if (v != p) {
                    dep[v] = dep[c] + 1;
                    dfs(v, c);
                }
            }
        };
        dfs(rt, -1);
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

    int kth(int u, int k) {
        for (auto i = 0; i < lg; i++)
            if ((k >> i) & 1)
                u = tb[i][u];
        return u;
    }

#if __cplusplus == 201703L // CPP17 only things
    void bind(opt_ref<vector<int>> dep0, opt_ref<vector<vector<int>>> tb0) {
        if (dep0) dep.swap(*dep0);
        if (tb0) tb.swap(*tb0);
    }
#endif
};

/*
 * ax + by = gcd(a, b)
 *
 * we know
 * bx' + (a%b)y' = gcd(a, b)
 *
 * bx' + (a-b*(a//b))y' = gcd(a, b)
 * bx' + ay' - b*(a//b)y' = gcd(a, b)
 * ay' + b(x' - (a//b)y') = gcd(a, b)
 */
template <typename T> T extgcd(T a, T b, T &x, T &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    T x0, y0, res = extgcd(b, a%b, x0, y0);
    x = y0;
    y = x0 - (a / b) * y0;
    return res;
}
// based on Tourist modInt orz
template <typename MD> struct _ModInt {
    using T = typename decay<decltype(MD::value)>::type;
    static_assert(sizeof(T) >= 4, "size of T must be at least 32 bits");
    static_assert(sizeof(T) <= 8, "size of T must be at most 64 bits");
    static_assert(is_integral<T>::value, "T must be an integral type");
#ifdef __SIZEOF_INT128__
    using mul_t = typename conditional<sizeof(T) <= 4, int64_t, __int128>::type;
#else
    using mul_t = int64_t;
    static_assert(sizeof(T) <= 4, "int128 not available, cannot use 64-bit size of T");
#endif

    constexpr static T mod() { return MD::value; }

    template <typename U> static T normalize(const U& x) {
        T res = x;
        res %= mod();
        if (res < 0) res += mod();
        return res;
    }

    T value;
    constexpr _ModInt() : value() {}
    template <typename U> _ModInt(const U& x) { value = normalize(x); }
    const T& operator()() const { return value; }
    template <typename U> operator U() const { return static_cast<U>(value); }

    // FastPow
    template <typename U> static _ModInt pow(_ModInt x, U y) {
        _ModInt res(1);
        for (; y; y /= 2) {
            if (y & 1) res *= x;
            x *= x;
        }
        return res;
    }
    static _ModInt inv(const _ModInt &x) {
        T inv, _; extgcd(x.value, mod(), inv, _);
        return _ModInt(inv);
    }

    // Arithmetic Operators w/ _ModInt
    // Assignment operators here
    _ModInt& operator+=(const _ModInt &o) { if ((value += o.value) >= mod()) value -= mod(); return *this; }
    template <typename U> _ModInt& operator+=(const U &o) { return *this += _ModInt(o); }
    _ModInt& operator-=(const _ModInt &o) { if ((value -= o.value) < 0) value += mod(); return *this; }
    template <typename U> _ModInt& operator-=(const U &o) { return *this -= _ModInt(o); }
    _ModInt& operator++() { return *this += 1; }
    _ModInt operator++(int) { _ModInt res(*this); *this += 1; return res; }
    _ModInt& operator--() { return *this -= 1; }
    _ModInt operator--(int) { _ModInt res(*this); *this -= 1; return res; }
    _ModInt& operator*=(const _ModInt &o) { value = (mul_t)value * o.value % mod(); if (value < 0) value += mod(); return *this; } // make sure cast to mul_t!!!
    template <typename U> _ModInt& operator*=(const U &o) { return *this *= _ModInt(o); }
    _ModInt& operator/=(const _ModInt &o) { return *this *= inv(o.value); }
    template <typename U> _ModInt& operator/=(const U &o) { return *this /= _ModInt(o); }
    _ModInt operator-() const { return _ModInt(value); }
    // Other Operators
    T& operator()() { return value; }
    // Definitions of some operators
};
// Binary operators
#define OP_CMP(op) template <typename T> bool operator op(const _ModInt<T> &lhs, const _ModInt<T> &rhs) { return lhs.value op rhs.value; } \
    template <typename T, typename U> bool operator op(const _ModInt<T> &lhs, U rhs) { return lhs op _ModInt<T>(rhs); } \
    template <typename T, typename U> bool operator op(U lhs, const _ModInt<T> &rhs) { return _ModInt<T>(lhs) op rhs; }
#define OP_ARI(op) template <typename T> _ModInt<T> operator op(const _ModInt<T> &lhs, const _ModInt<T> &rhs) { return _ModInt<T>(lhs) op##= rhs; } \
    template <typename T, typename U> _ModInt<T> operator op(U lhs, const _ModInt<T> &rhs) { return _ModInt<T>(lhs) op##= rhs; } \
    template <typename T, typename U> _ModInt<T> operator op(const _ModInt<T> &lhs, U rhs) { return _ModInt<T>(lhs) op##= rhs; }
OP_CMP(==) OP_CMP(!=) OP_CMP(<) OP_CMP(>) OP_CMP(<=) OP_CMP(>=)
OP_ARI(+) OP_ARI(-) OP_ARI(*) OP_ARI(/)
#undef OP_CMP
#undef OP_ARI
template <typename T> istream& operator>>(istream& in, _ModInt<T> &o) { return in >> o(); }
template <typename T> ostream& operator<<(ostream& out, _ModInt<T> &o) { return out << o(); }

// Definitions
template <typename T, T mod> using ModInt = _ModInt<integral_constant<T, mod>>;
template <typename T> struct VarMod {
    static T value;
    static void read(istream& in) { in >> value; }
    static void set(T v0) { value = v0; }
};
template <typename T> using VarModInt = _ModInt<VarMod<T>>;

using MI = ModInt<int, 998244353>;

const int MN = 1e5 + 1, MK = 501;
int N, Q,
    sz[MN], par[MN];
vector<int> g[MN];
LCABinaryLift<vector<int>[MN], Edge> lca;

void dfs(int c, int p) {
    sz[c] = 1;
    par[c] = p;
    for (auto to : g[c]) {
        if (to != p) {
            dfs(to, c);
            sz[c] += sz[to];
        }
    }
}

MI sto[MN][MK];
void rundp(MI dp[MK], int v) {
    for (auto i = MK-1; i >= 1; i--) dp[i] += dp[i-1] * v;
}

MI C[MK][MK], F[MK];

MI sumundp(MI dp[MK], int v, int k) {
    // cout<<"[undo]: "; cout<<"dp=["; for(int __i=0; __i<(6); __i++)cout<<(dp)[__i]<<", "; cout<<"], ";cout << endl; // db l:undo,A:6:dp
    // cout<<"v="<<(v)<<", "; cout<<"k="<<(k)<<", "; cout << endl; // db v,k

    MI pre = dp[0], res = dp[0];
    // cout<<"dp[0]="<<(dp[0])<<", "; cout << endl; // db dp[0]
    for (auto i = 1; i <= k; i++) {
        pre = dp[i] - pre*v;
        res += C[k][i] * F[i] * pre;

        // cout<<"i="<<(i)<<", "; cout<<"pre="<<(pre)<<", "; cout << endl; // db i,pre
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    for (auto i = 0; i < N-1; i++) {
        int a, b; cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }
    lca.init(N, g, 1);
    dfs(1, -1);

    // choose table
    for (auto i = 0; i < MK; i++) C[i][0] = 1;
    for (auto i = 1; i < MK; i++)
        for (auto j = 1; j < MK; j++)
            C[i][j] = C[i-1][j] + C[i-1][j-1];
    F[0] = 1;
    for (auto i = 1; i < MK; i++) F[i] = F[i-1] * i;
    
    // init DP
    for (auto i = 1; i <= N; i++) {
        sto[i][0] = 1;
        for (auto to : g[i])
            if (to != par[i])
                rundp(sto[i], sz[to]);
        rundp(sto[i], sz[1]-sz[i]);

        // cout<<"i="<<(i)<<", "; cout << endl; // db i
        // cout<<"sto[i]=["; for(int __i=0; __i<(6); __i++)cout<<(sto[i])[__i]<<", "; cout<<"], ";cout << endl; // db A:6:sto[i]
    }

    while (Q--) {
        int u, v, k; cin >> u >> v >> k;

        int l = lca.lca(u, v), c1, c2;

        if (u != l) c1 = sz[1] - sz[u];
        else c1 = sz[lca.kth(v, lca.dep[v]-lca.dep[l]-1)];

        if (v != l) c2 = sz[1] - sz[v];
        else c2 = sz[lca.kth(u, lca.dep[u]-lca.dep[l]-1)];

        // cout<<"[query]: "; cout<<"u="<<(u)<<", "; cout<<"v="<<(v)<<", "; cout<<"k="<<(k)<<", "; cout<<"l="<<(l)<<", "; cout<<"c1="<<(c1)<<", "; cout<<"c2="<<(c2)<<", "; cout << endl; // db l:query,u,v,k,l,c1,c2

        MI ans = sumundp(sto[u], c1, k) * sumundp(sto[v], c2, k);
        cout << (ans) << '\n';
    }

    return 0;
}
