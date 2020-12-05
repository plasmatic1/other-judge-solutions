// B.yml
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
// PBDS order statistic tree
#include <ext/pb_ds/assoc_container.hpp> // Common file 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds; 
template <typename T, class comp = less<T>> using os_tree = tree<T, null_type, comp, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename V, class comp = less<K>> using treemap = tree<K, V, comp, rb_tree_tag, tree_order_statistics_node_update>;
// HashSet
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
const ll RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { ll operator()(ll x) const { return x ^ RANDOM; } };
template <typename T, class Hash> using hashset = gp_hash_table<T, null_type, Hash>;
template <typename K, typename V, class Hash> using hashmap = gp_hash_table<K, V, Hash>;
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

int tri(int x) { return (x * (x - 1)) / 2; }

/*

Possiblities:

- l (# of worse), (you), r (# of better)

1 -> 2 worse people tri(l)
2 -> 2 better people tri(r)
3 -> worse and better (l*r)
4 -> you and worse (l)
5 -> you and better (r)

*/

void solve() {
    int N; ld P;
    cin >> N >> P;

    vector<vector<ld>> dp(N, vector<ld>(N, -1.0));
    function<ld(int, int)> solve = [&] (int l, int r) -> ld {
        if (l == 0 && r == 0) return 0; // you are winnar!!!!111!!
        ld &res = dp[l][r];
        if (res != -1.0f) return res;
        res = 0;

        ld aleft = tri(l + r + 1);
        if (l >= 1) {
            res += solve(l - 1, r) * (tri(l) / aleft); // 1
            res += P * solve(l - 1, r) * (l / aleft); // 4
        }
        if (r >= 1) {
            res += solve(l, r - 1) * (tri(r) / aleft); // 2
            res += (1 - P) * solve(l, r - 1) * (r / aleft); // 5
        }
        if (l >= 1 && r >= 1) {
            res += ((1 - P) * solve(l, r - 1) + P * solve(l - 1, r)) * ((l * r) / aleft); // 3
        }

        res += 1.0;
        return res;
    };

    for (auto i = 1; i <= N; i++) {
        int l = i - 1, r = N - l - 1;
        cout << (solve(l, r)) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_file_io();
    cout << setprecision(8) << fixed;

    int T;
    cin >> T;
    for (int caseno = 1; caseno <= T; caseno++) {
        // Input
       
        cout << "Case #" << caseno << ":\n";
        solve();

        // Reset
#ifndef LOCAL
        cerr << "Done case #" << caseno << endl;
#endif
    }

    return 0;
}

