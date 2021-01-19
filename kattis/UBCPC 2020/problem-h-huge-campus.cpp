// ./problem-h-huge-campus.yml
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

const int MN = 1e4 + 1, MK = 30 + 1;
int N, K,
    A[MN], B[MN],
    dp[2][4][MK][MK];
string ss[MN];

template <typename T> void mina(T &a, T b) { a = min(a, b); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (K);
    for (auto i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;
        A[i] = a - 1; B[i] = b - 1;
    }
    for (auto i = 0; i < N; i++) {
        string s;
        cin >> s;
        ss[i] = s;
    }

    memset(dp, 0x3f, sizeof dp);
    dp[0][3][K][K] = 0;
    for (auto i = 0; i < N; i++) {
        int c = i & 1, n = c ^ 1;
        memset(dp[n], 0x3f, sizeof dp[n]);
        for (auto j = 0; j <= K; j++)
            for (auto k = 0; k <= K; k++)
                dp[n][0][j][k] = dp[c][3][j][k];

        vector<int> loc{K, A[i], B[i], K};
        for (auto j = 0; j < 3; j++) { // part
            int a = loc[j], b = loc[j + 1];
            for (auto k = 0; k <= K; k++) { // u loc
                for (auto l = 0; l <= K; l++) { // u loc
                    int cdp = dp[n][j][k][l];
                    // cout<<"i="<<(i)<<", "; cout<<"j="<<(j)<<", "; cout<<"k="<<(k)<<", "; cout<<"l="<<(l)<<", "; cout<<"cdp="<<(cdp)<<", "; cout << endl; // db i,j,k,l,cdp

                    // take 0
                    if (ss[i][j] == 'S')
                        mina(dp[n][j + 1][k][l], cdp);

                    // take 1
                    if (k == a) {
                        mina(dp[n][j + 1][b][l], cdp + 1);
                    }
                    if (l == a) {
                        mina(dp[n][j + 1][k][b], cdp + 1);
                    }

                    // take 2
                    if (k == a && l == a) {
                        mina(dp[n][j + 1][b][b], cdp + 1);
                    }
                }
            }
        }
    }

    int a = N & 1, ans = INF;
    for (auto i = 0; i <= K; i++)
        for (auto j = 0; j <= K; j++)
            mina(ans, dp[a][3][i][j]);
    cout << (ans) << '\n';

    return 0;
}

