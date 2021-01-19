// F.yml
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

const int MN = 51;
int N;
#ifdef LOCAL
int ANS[MN][MN];
int query(vector<int> v) {
    unordered_set<int> a(all(v));
    vector<int> w;
    for (auto i = 1; i <= N; i++)
        if (!a.count(i))
            w.pb(i);
    int res = 0;
    for (auto x : v)
        for (auto y : w)
            res += ANS[x][y];
    return res;
}
#else
int query(vector<int> v) {
    cout << "? " << SZ(v) << ' ';
    for (auto x : v) cout << x << ' ';
    cout << '\n';
    cout.flush();
    int res;
    cin >> res;
    assert(res != -1);
    return res;
}
#endif
int ans[MN][MN], deg[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
#ifdef LOCAL
    for (auto i = 1; i <= N; i++)
        for (auto j = 1; j <= N; j++)
            cin >> (ANS[i][j]);
#endif

    for (auto i = 1; i <= N; i++)
        deg[i] = query({i});
    for (auto i = 1; i <= N; i++) {
        for (auto j = i+1; j <= N; j++) {
            int q = query({i, j});
            if (q < deg[i] + deg[j])
                ans[i][j] = ans[j][i] = true;
        }
    }
    cout << ("!") << '\n';
    for (auto i = 1; i <= N; i++) {
        for (auto j = 1; j <= N; j++)
            cout << ans[i][j] << ' ';
        cout << '\n';
    }
    cout.flush();

    return 0;
}

