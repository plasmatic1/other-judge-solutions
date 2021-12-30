// ./d1-expl-ore-ation-chapter-1.yml
#include <bits/stdc++.h>
#define DEBUG 1
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

struct DSU {
    vector<int> dsu, done;
    void init(int N) {
        dsu.resize(N + 1);
        done.assign(N + 1, 0);
        iota(dsu.begin(), dsu.end(), 0);
    }
    int rt(int x) { return dsu[x] == x ? x : dsu[x] = rt(dsu[x]); }
    void merge(int x, int y) { // x -> y
        x = rt(x); y = rt(y);
        if (x == y) return;
        done[y] |= done[x];
        dsu[x] = y;
    }
    void turn(int r) { done[rt(r)] = true; }
    bool check(int r) { return done[rt(r)]; }
    bool con(int x, int y) { return rt(x) == rt(y); }
};

using TP = tuple<int, int, int>;
const int MN = 1e6+1;
int R, C;

int conv(int r, int c) { return C*r + c; }

void solve() {
    cin >> R >> C;
    vector<vector<int>> H(R, vector<int>(C)), T(R, vector<int>(C));
    for (auto &r : H) for (auto &x : r) cin >> x;
    for (auto &r : T) for (auto &x : r) cin >> x;

    vector<TP> es, locs;
    for (auto i = 0; i < R; i++) {
        for (auto j = 0; j < C-1; j++)
            es.eb(min(H[i][j], H[i][j+1]), conv(i, j), conv(i, j+1));
    }
    for (auto i = 0; i < R-1; i++)
        for (auto j = 0; j < C; j++)
            es.eb(min(H[i][j], H[i+1][j]), conv(i, j), conv(i+1, j));
    sort(all(es));
    reverse(all(es));

    for (auto i = 0; i < R; i++)
        for (auto j = 0; j < C; j++)
            if (H[i][j] > T[i][j])
                locs.eb(T[i][j], i, j);
    sort(all(locs));
    reverse(all(locs));

    int sz = SZ(es), ptr = 0;
    int collect = SZ(locs), ans = 0;

    DSU dsu; dsu.init(R*C);
    for (auto [t, r, c] : locs) {
        while (ptr < sz && get<0>(es[ptr]) > t) {
            auto [w, a, b] = es[ptr];
            dsu.merge(a, b);
            ptr++;
        }

        int n = conv(r, c);
        if (!dsu.check(n)) {
            ans++;
            dsu.turn(n);
        }
    }

    cout << (collect) << ' ' << (ans) << '\n';
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
