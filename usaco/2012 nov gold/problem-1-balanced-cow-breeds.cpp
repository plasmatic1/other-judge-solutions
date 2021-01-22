// ./problem-1-balanced-cow-breeds.yml
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
    const string PROBLEM_ID = "bbreeds";
    freopen((PROBLEM_ID + ".in").c_str(), "r", stdin);
    freopen((PROBLEM_ID + ".out").c_str(), "w", stdout);
#endif
}

const int MN = 1001, MOD = 2012;
int N,
    dp[MN][MN], psum[MN];

int main() {
    init_file_io();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> (s);
    N = s.length();
    for (auto i = 0; i < N; i++)
        psum[i+1] = psum[i] + (s[i] == ')' ? -1 : 1);

    if (psum[N]) {
        cout << (0) << '\n';
        return 0;
    }

    dp[0][0] = 1;
    for (auto i = 0; i < N; i++) {
        for (auto j = 0; j < N; j++) {
            int osum = psum[i] - j, v = psum[i+1] - psum[i];
            // assign to cur
            if (j + v >= 0)
                dp[i+1][j+v] = (dp[i+1][j+v] + dp[i][j]) % MOD;
            // assign to oth
            if (osum + v >= 0)
                dp[i+1][j] = (dp[i+1][j] + dp[i][j]) % MOD;
        }
    }

    cout << (dp[N][0]) << '\n';

    return 0;
}

