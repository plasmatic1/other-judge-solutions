// C.yml
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

int main() {
    init_file_io();

    int T;
    cin >> T;
    for (int caseno = 1; caseno <= T; caseno++) {
        // Input
       
        cout << "Case #" << caseno << ": ";

        int N;
        cin >> N;
        vector<pll> trees(N);
        for (auto &p : trees)
            cin >> (p.fs) >> (p.sn);
        trees.eb(-LLINF, -1);
        trees.eb(LLINF, -1);
        sort(all(trees));

        vector<vector<ll>> dp(N + 1, vector<ll>(2)); // back, forward
        map<ll, ll> best;
        for (auto i = 1; i <= N; i++) {
            auto &t = trees[i];
            for (auto j = 0; j < 2; j++)
                dp[i][j] = t.sn;
            maxa(dp[i][0], best[t.fs - t.sn] + t.sn);
            maxa(dp[i][1], best[t.fs] + t.sn);
            maxa(best[t.fs], dp[i][0]);
            maxa(best[t.fs + t.sn], dp[i][1]);
            // cout<<"i="<<(i)<<", "; cout<<"dp[i][0]="<<(dp[i][0])<<", "; cout<<"dp[i][1]="<<(dp[i][1])<<", "; cout << endl; // db i,dp[i][0],dp[i][1]
        }

        ll ans = -LLINF;
        for (auto i = 0; i <= N; i++)
            for (auto j = 0; j < 2; j++)
                maxa(ans, dp[i][j]);
        cout << (ans) << '\n';
    }
}

