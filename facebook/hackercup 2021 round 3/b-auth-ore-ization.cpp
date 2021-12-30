// ./b-auth-ore-ization.yml
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

void init_file_io() {
#ifndef LOCAL
    const string PROBLEM_ID = "prob";
    freopen((PROBLEM_ID + ".in").c_str(), "r", stdin);
    freopen((PROBLEM_ID + ".out").c_str(), "w", stdout);
#endif
}

template <typename T> void read_fhc_array(vector<T> &v, int k, int inc = 1) {
    for (auto i = 0; i < k; i++)
        cin >> v[i];
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    for (auto i = k; i < (int)v.size(); i++)
        v[i] = (a * v[i - 2] + b * v[i - 1] + c) % d + inc;
}

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
struct Mat {
    int m[3][3];

    Mat(const int c[3][3]) {
        memcpy(m, c, sizeof m);
    }
    Mat() {
        for (auto i = 0; i < 3; i++)
            for (auto j = 0; j < 3; j++)
                m[i][j] = INF;
    }

    Mat operator*(const Mat &o) const {
        Mat res;
        for (auto i = 0; i < 3; i++)
            for (auto j = 0; j < 3; j++)
                for (auto k = 0; k < 3; k++)
                    mina(res.m[i][j], m[i][k]+o.m[k][j]);
        return res;
    }
    Mat& operator*=(const Mat &o) {
        return *this = (*this) * o;
    }
};
ostream& operator<<(ostream& out, const Mat o) {
    out << "(";
    for (auto i = 0; i < 3; i++) {
        out << "(";
        for (auto j = 0; j < 3; j++) {
            out << o.m[i][j] << ", ";
        }
        out << "), ";
    }
    out << ")";

    return out;
} 

const int _ID[3][3] = {{0, INF, INF}, {INF, 0, INF}, {INF, INF, 0}};
const Mat ID(_ID), NONE;

// Template is 1-indexed
// Default Comp: RMQ + Set query
// Functions merge and applyUpdate should be implemented left to right
struct Comp {
    using Data = Mat;
    using Update = Mat;
    const Data vdef = ID;
    Data merge(Data l, Data r) { return l * r; }
    void applyUpdate(Data &l, Update &r) { l = r; }
};
struct IntMaxComp {
    using Data = int;
    using Update = int;
    const Data vdef = -INF;
    Data merge(Data l, Data r) { return max(l, r); }
    void applyUpdate(Data &l, Update &r) { l = r; }
};
#define MID int mid = (l + r) / 2, lhs = i + 1, rhs = i + (mid - l + 1) * 2;
template <class Comp> struct SegmentTree {
    using Data = typename Comp::Data; using Update = typename Comp::Update; Comp C;
    int N;
    vector<Data> seg;
    void init(int n0) {
        N = n0;
        seg.assign(2 * N + 2, C.vdef);
    }
    Data _query(int ql, int qr, int i, int l, int r) {
        if (ql > r || qr < l) return C.vdef;
        if (l >= ql && r <= qr) return seg[i];
        MID;
        return C.merge(_query(ql, qr, lhs, l, mid), _query(ql, qr, rhs, mid + 1, r));
    }
    Data _update(int q, Update v, int i, int l, int r) {
        if (q > r || q < l) return seg[i];
        if (l == q && r == q) {
            C.applyUpdate(seg[i], v);
            return seg[i];
        }
        MID;
        return seg[i] = C.merge(_update(q, v, lhs, l, mid), _update(q, v, rhs, mid + 1, r));
    }
    Data query(int ql, int qr) { return _query(ql+1, qr+1, 1, 1, N); }
    void update(int q, Update v) { _update(q+1, v, 1, 1, N); }
};

using MI = ModInt<int, 1000000007>;
using T = tuple<int, int, int, int, int>;
using T2 = tuple<int, int, int, int>;

const int MN = 1e6 + 1, TYPE_H = 0, TYPE_V = 1;
int N, M,
    A[MN][3], curRow[MN][3], nxtRow[MN][3];

Mat CurRow(int r) {
    Mat res(_ID);

    for (auto i = 0; i < 3; i++) {
        bool ok = true;
        for (auto j = i+1; j < 3; j++) {
            ok &= curRow[r][j-1];
            if (ok)
                res.m[i][j] = res.m[j][i] = j-i;
        }
    }

    return res;
}

Mat NxtRow(int r) {
    Mat res;
    for (auto i = 0; i < 3; i++)
        if (nxtRow[r][i])
            res.m[i][i] = 1;
    return res;
}

void solve() {
    cin >> N >> M;
    for (auto i = 0; i < N; i++)
        for (auto j = 0; j < 3; j++)
            cin >> A[i][j];

    // get queries
    vector<T> qs(M);
    for (auto &t : qs) {
        auto &[d, r1, c1, r2, c2] = t;
        cin >> r1 >> c1 >> r2 >> c2 >> d;
        r1--; c1--; r2--; c2--;
    }
    sort(all(qs));

    // get edges
    vector<T2> es;
    for (auto i = 0; i < N-1; i++) {
        for (auto j = 0; j < 3; j++) {
            es.eb(max(A[i][j], A[i+1][j]), i, j, TYPE_V);
        }
    }
    for (auto i = 0; i < N; i++) {
        for (auto j = 0; j < 2; j++) {
            es.eb(max(A[i][j], A[i][j+1]), i, j, TYPE_H);
        }
    }
    sort(all(es));

    // setup segtree
    SegmentTree<Comp> seg; seg.init(N);
    vector<SegmentTree<IntMaxComp>> maxt(3);
    for (auto i = 0; i < 3; i++)
        maxt[i].init(N);
    for (auto i = 0; i < N; i++) {
        seg.update(i, NONE);
        for (auto j = 0; j < 3; j++)
            maxt[j].update(i, A[i][j]);
    }
    set<int> filled;
    filled.insert(INF);
    filled.insert(-INF);

    // queries
    MI ans = 1;
    int ptr = 0, sz = SZ(es);
    for (auto [d, r1, c1, r2, c2] : qs) {
        while (ptr < sz && get<0>(es[ptr]) <= d) {
            auto [_, er, ec, et] = es[ptr];

            bool donebef = curRow[er][0] && curRow[er][1];
            if (et == TYPE_H)
                curRow[er][ec] = 1;
            else
                nxtRow[er][ec] = 1;
            bool doneaft = curRow[er][0] && curRow[er][1];

            if (!donebef && doneaft)
                filled.insert(er);

            seg.update(er, CurRow(er) * NxtRow(er));

            ptr++;
        }

        if (r1 > r2) {
            swap(r1, r2);
            swap(c1, c2);
        }

        // no up
        Mat dist = seg.query(r1, r2-1);

        auto ThroughPre = [&maxt, &filled] (int r, int a, int b, int d) {
            auto pre = prev(filled.upper_bound(r));
            if (*pre != -INF && maxt[a].query(*pre, r) <= d && maxt[b].query(*pre, r) <= d) {
                int alt = 2 * (r - *pre) + 2;
                return alt;
            }
            return (int)INF;
        };
        auto ThroughNxt = [&maxt, &filled] (int r, int a, int b, int d) {
            auto nxt = filled.lower_bound(r);
            if (*nxt != INF && maxt[a].query(r, *nxt) <= d && maxt[b].query(r, *nxt) <= d) {
                int alt = 2 * (*nxt - r) + 2;
                return alt;
            }
            return (int)INF;
        };

        Mat preL = CurRow(r1), nxtL = CurRow(r2);
        for (auto i = 0; i < 3; i++) {
            for (auto j = 0; j < 3; j++) {
                mina(preL.m[i][j], ThroughPre(r1, i, j, d));
                mina(nxtL.m[i][j], ThroughNxt(r2, i, j, d));
            }
        }
        Mat FINAL = preL * dist * nxtL;

        int cans = FINAL.m[c1][c2];
        if (cans == INF) cans = 1;
        ans *= cans;
    }

    cout << (ans) << '\n';

    // resetting
    for (auto i = 0; i <= N; i++) {
        for (auto j = 0; j < 3; j++) {
            curRow[i][j] = nxtRow[i][j] = 0;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_file_io();

    int T;
    cin >> T;
    for (int caseno = 1; caseno <= T; caseno++) {
        // Input

        cout << "Case #" << caseno << ": ";
        solve();

        // Reset
#ifndef LOCAL
        cerr << "Done case #" << caseno << endl;
#endif
    }

    return 0;
}
