// A.yml
#include "bits/stdc++.h"
using namespace std;

// Defines
#define pb push_back
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
        
        cout << "Case #" << caseno << ':' << '\n';

        int N; string s, t;
        cin >> N >> s >> t;
        
        vector<vector<bool>> adj(N, vector<bool>(N));
        for (auto i = 0; i < N; i++)
            adj[i][i] = true;
        for (auto i = 0; i < N; i++) {
            if (s[i] == 'Y') {
                if (i > 0 && t[i - 1] != 'N') adj[i - 1][i] = true;
                if (i < N - 1 && t[i + 1] != 'N') adj[i + 1][i] = true;
            }
            if (t[i] == 'Y') {
                if (i > 0 && s[i - 1] != 'N') adj[i][i - 1] = true;
                if (i < N - 1 && s[i + 1] != 'N') adj[i][i + 1] = true;
            }
        }
        for (auto k = 0; k < N; k++)
            for (auto i = 0; i < N; i++)
                for (auto j = 0; j < N; j++)
                    adj[i][j] = adj[i][j] || (adj[i][k] && adj[k][j]);
        for (auto i = 0; i < N; i++) {
            for (auto j = 0; j < N; j++)
                cout << "NY"[adj[i][j]];
            cout << '\n';
        }
    }
}

