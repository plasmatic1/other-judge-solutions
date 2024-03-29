// ./controlled-inflation.yml
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

const int MN = 1001, MP = 101;
int N, P;
ll dp[MN][MP], X[MN][MP];

ll getTransCost(int startP, int endP, int idx) {
    return min(abs(startP - X[idx][0]) + abs(endP - X[idx][P-1]),
                abs(startP - X[idx][P-1]) + abs(endP - X[idx][0])) + X[idx][P-1] - X[idx][0];
}

void solve() {
    cin >> N >> P;
    for (auto i = 0; i < N; i++) {
        for (auto j = 0; j < P; j++)
            cin >> X[i][j];
        sort(X[i], X[i]+P);
    }

    memset(dp, 0x3f, sizeof dp);
    for (auto i = 0; i < P; i++) {
        dp[0][i] = getTransCost(0, X[0][i], 0);
    }
    for (auto i = 1; i < N; i++) {
        for (auto j = 0; j < P; j++) {
            for (auto k = 0; k < P; k++) {
                mina(dp[i][j], dp[i-1][k] + getTransCost(X[i-1][k], X[i][j], i));
            }
        }
    }

    ll ans = LLINF;
    for (auto i = 0; i < P; i++)
        mina(ans, dp[N-1][i]);
    cout << (ans) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for (int caseno = 1; caseno <= T; caseno++) {
        // Input
       
        cout << "Case #" << caseno << ": ";
        solve();

        // Reset
    }
}

