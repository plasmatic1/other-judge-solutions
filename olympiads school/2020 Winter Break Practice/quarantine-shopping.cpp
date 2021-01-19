// ./quarantine-shopping.yml
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

const int MW = 1001;
int N, D;
struct dp_struct {
    int pw, pi, pcnt, v;
    bool operator<(const dp_struct &o) const {
        return v < o.v;
    }
} dp[MW];

void rundp(int w, int v, int idx, int c) {
    for (auto i = D; i >= w; i--) {
        if (dp[i-w].v+v > dp[i].v)
            dp[i] = dp_struct{i-w, idx, c, dp[i-w].v + v};
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (D);
    // assert(1 <= N && N <= 1000);
    // assert(1 <= D && D <= 1000);
    for (auto i = 0; i < N; i++) {
        int c, v, k;
        cin >> c >> v >> k;
        if (k < 0) continue;
        // assert(1 <= c && c <= 100);
        // assert(-1000000 <= v && v <= 1000000);
        // assert(1 <= k && k <= 100);
        for (auto j = 0; j < __lg(k)-1; j++) {
            int cnt = 1 << j;
            rundp(cnt*c, cnt*v, i, cnt);
        }
        int cnt = k - (1 << __lg(k)) + 1;
        rundp(cnt*c, cnt*v, i, cnt);
    }

    vector<int> cnt(N);
    int c = max_element(dp, dp + D + 1) - dp;
    cout << (dp[c].v) << '\n';
    for (; c; c = dp[c].pw) {
        assert(dp[c].pi >= 0 && dp[c].pi < N);
        cnt[dp[c].pi] += dp[c].pcnt;
    }
    for (auto i = 0; i < N; i++)
        cout << (cnt[i]) << '\n';

    return 0;
}

