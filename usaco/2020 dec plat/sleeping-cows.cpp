// sleeping-cows.yml
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

const ll MOD = 1e9 + 7;
ll fix(ll &x) { x %= MOD; if (x < 0) x += MOD; return x; }
ll fix(ll &&x) { x %= MOD; if (x < 0) x += MOD; return x; }

const int MN = 3005;
int N;
pair<int, bool> evt[MN*2]; // (size, is_barn) 
ll dp[MN*2][MN][2]; // dp[cur evt][number of unmatched cows][we can start skipping cows]
// Once we start max(unmatched barn) < min(unmatched cow)
// For events of the same size, barns go first--- we can turn on the last state only on the last event of a size
// You can no longer skip barns(?)

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    for (auto i = 1; i <= N; i++) {
        int x; cin >> x;
        evt[i] = mpr(x, false);
    }
    for (auto i = 1; i <= N; i++) {
        int x; cin >> x;
        evt[N+i] = mpr(x, true);
    }
    sort(evt + 1, evt + 2*N + 1);

    dp[0][0][0] = 1;
    for (auto i = 1; i <= 2*N; i++) {
        auto p = evt[i];
        for (auto j = 0; j <= N; j++) {
            if (p.sn) {
                // remove a queued cow with barn i
                if (j < N) {
                    for (auto k = 0; k < 2; k++)
                        dp[i][j][k] += fix((j+1) * dp[i-1][j+1][k]);
                }
                // Skip barn i
                dp[i][j][0] += dp[i-1][j][0];
            }
            else {
                // Queue cow i
                if (j > 0) {
                    for (auto k = 0; k < 2; k++)
                        dp[i][j][k] += dp[i-1][j-1][k];
                }
                // Skip cow i
                dp[i][j][1] += dp[i-1][j][1] + dp[i-1][j][0];
            }
            for (auto k = 0; k < 2; k++) fix(dp[i][j][k]);
        }
    }

    ll ans = fix(dp[2*N][0][0] + dp[2*N][0][1]);
    cout << (ans) << '\n';

    return 0;
}

