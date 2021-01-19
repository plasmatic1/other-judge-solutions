// ./problem-d-drowning-combinatorist.yml
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

ll MOD;
ll fix(ll &&x) { x %= MOD; if (x < 0) x += MOD; return x; }
ll fix(ll &x) { x %= MOD; if (x < 0) x += MOD; return x; }
ll fpow(ll x, ll y, ll mod = MOD) {
    if (!y) return 1LL;
    return fpow(x * x % mod, y >> 1, mod) * ((y & 1) ? x : 1LL) % mod;
}
ll inv(ll x, ll mod = MOD) { return fpow(x, mod - 2, mod); }

/*
 * 1-7 (increasing)
 * 8-14 (decreasing)
 *
 * subtract 7 to get dec amt
 */
const int MN = 2011, MK = 8;
int N, K;
ll dp[MN][MN][MK*2], psum[MK*2][MN];

ll q(int k, int l, int r) {
    return fix(psum[k][r] - psum[k][l - 1]);
}

void makecheese(int i) {
    memset(psum, 0, sizeof psum);
    for (auto j = 1; j <= K+7; j++) {
        for (auto k = 1; k <= i+1; k++) {
            psum[j][k] = fix(psum[j][k - 1] + dp[i][k][j]);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (K) >> (MOD);
    dp[1][1][1] = 1LL;

    for (auto i = 2; i <= N; i++) {
        // build psum
       makecheese(i - 1);

        // for (auto j = 1; j <= i; j++) {
        for (auto j = 1; j <= i; j++) {
            for (auto k = 2; k <= K; k++) {
                // continuing inc
                // for (auto l = 1; l < j; l++)
                //     dp[i][j][k] += dp[i - 1][l][k - 1];
                dp[i][j][k] = q(k - 1, 1, j - 1);

                // continuing dec
                int dk = k + 7;
                // for (auto l = j; l <= i; l++) {
                //     int pre = k == 2 ? 1 : dk - 1;
                //     dp[i][j][dk] += dp[i - 1][l][pre];
                // }
                dp[i][j][dk] = q(k == 2 ? 1 : dk - 1, j, i);

                fix(dp[i][j][k]);
                fix(dp[i][j][dk]);
            }

            // breaking to dec
            // for (auto l = j; l <= i; l++)
            //     for (auto m = 2; m <= K; m++)
            //         dp[i][j][9] += dp[i - 1][l][m];
            for (auto l = 2; l <= K; l++)
                dp[i][j][9] += q(l, j, i);

            // breaking to inc
            // for (auto l = 1; l < j; l++)
            //     for (auto m = 2; m <= K; m++)
            //         dp[i][j][2] += dp[i - 1][l][7 + m];
            for (auto l = 2; l <= K; l++)
                dp[i][j][2] += q(7 + l, 1, j - 1);

            fix(dp[i][j][2]);
            fix(dp[i][j][9]);
        }

        // for (auto j = 1; j <= N; j++) {
        //     for (auto k = 1; k <= K+7; k++) {
        //         if (k == 8) continue;
        //         cout<<"i="<<(i)<<", "; cout<<"j="<<(j)<<", "; cout<<"k="<<(k)<<", "; cout<<"dp[i][j][k]="<<(dp[i][j][k])<<", "; cout << endl; // db i,j,k,dp[i][j][k]
        //         // cout<<"j="<<(j)<<", "; cout<<"k="<<(k)<<", "; cout<<"psum[j][k]="<<(psum[j][k])<<", "; cout << endl; // db j,k,psum[j][k]
        //     }
        // }
    }

    ll ans = 0;
    for (auto i = 1; i <= N; i++) {
        for (auto j = 1; j <= K; j++)
            ans += dp[N][i][j];
        for (auto j = 9; j <= 7 + K; j++)
            ans += dp[N][i][j];
    }
    cout << (fix(ans)) << '\n';

    return 0;
}

