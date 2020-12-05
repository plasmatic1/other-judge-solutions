// ./boring-numbers.yml
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

const int MN = 19;
ll L, R,
   dp[MN][2];

ll cntd(int dc) {
    ll res = 1;
    for (auto i = 1; i <= dc; i++)
        res *= 5;
    return res;
}

ll f(ll x) {
    ll res = 0;
    string sx = to_string(x);
    for (auto i = 1; i < SZ(sx); i++)
        res += cntd(i);

    memset(dp, 0, sizeof dp);
    dp[0][1] = (sx[0] - '0') & 1;
    dp[0][0] = (sx[0] - '0') / 2;
    for (auto i = 0; i < SZ(sx) - 1; i++) {
        int dig = sx[i + 1] - '0';
        if ((dig & 1) == (i & 1))
            dp[i + 1][1] += dp[i][1];

        ll mul = (i & 1) ? dig / 2 : (dig + 1) / 2;
        dp[i + 1][0] += dp[i][1] * mul;
        dp[i + 1][0] += dp[i][0] * 5;
    }
    res += dp[SZ(sx) - 1][0] + dp[SZ(sx) - 1][1];

    // cout<<"x="<<(x)<<", "; cout<<"res="<<(res)<<", "; cout << endl; // db x,res

    return res;
}

void solve() {
    cin >> (L) >> (R);
    cout << (f(R) - f(L - 1)) << '\n';
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

