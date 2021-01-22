// ./problem-2-concurrently-balanced-strings.yml
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
    const string PROBLEM_ID = "cbs";
    freopen((PROBLEM_ID + ".in").c_str(), "r", stdin);
    freopen((PROBLEM_ID + ".out").c_str(), "w", stdout);
#endif
}

const int MN = 5e4 + 1, MK = 11;
int N, K,
    psum[MK][MN];

int main() {
    init_file_io();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (K) >> (N);
    for (auto i = 0; i < K; i++) {
        string s;
        cin >> s;
        for (auto j = 0; j < N; j++)
            psum[i][j+1] = psum[i][j] + (s[j] == ')' ? -1 : 1);
    }

    unordered_map<string, vector<int>> cnt;
    vector<pii> dq[K];
    for (auto i = 0; i < K; i++) dq[i].eb(-INF, 0);
    ll ans = 0;
    for (auto i = 1; i <= N; i++) {
        // update deque
        for (auto j = 0; j < K; j++) {
            while (dq[j].back().fs > psum[j][i])
                dq[j].pop_back();
            dq[j].eb(psum[j][i], i);
        }

        // binary search for range
        int mx = -INF;
        for (auto j = 0; j < K; j++) {
            auto ptr = lower_bound(all(dq[j]), pii{psum[j][i], -INF});
            maxa(mx, ptr->sn);
        }

        // encode stuff
        string s;
        for (auto j = 0; j < K; j++) s += to_string(psum[j][i]) + ",";
        vector<int> &v = cnt[s];
        ans += SZ(v) - (lower_bound(all(v), mx) - v.begin());
        v.pb(i);
    }
    cout << (ans) << '\n';

    return 0;
}

