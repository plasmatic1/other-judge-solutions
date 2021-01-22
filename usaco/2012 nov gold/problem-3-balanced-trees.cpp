// ./problem-3-balanced-trees.yml
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
    const string PROBLEM_ID = "btree";
    freopen((PROBLEM_ID + ".in").c_str(), "r", stdin);
    freopen((PROBLEM_ID + ".out").c_str(), "w", stdout);
#endif
}

const int MN = 4e4 + 1;
int N,
    val[MN];
vector<int> g[MN];

// cent
int sz[MN];
bool block[MN];

int gsz(int c, int p) {
    sz[c] = 1;
    for (auto to : g[c])
        if (to != p && !block[to])
            sz[c] += gsz(to, c);
    return sz[c];
}
int gcent(int c, int p, int h) {
    for (auto to : g[c])
        if (to != p && !block[to] && sz[to] > h)
            return gcent(to, c, h);
    return c;
}

int ans = 0;
// type=0->update, type=1->query
void dfs(int c, int p, int dep, int minv, int maxv, unordered_map<int, int> &um, bool type) {
    if (type == 0) {
        dep += val[c];
        minv = min(minv + val[c], val[c]);
        maxv = max(maxv + val[c], val[c]);
    }
    else {
        int adep = dep + val[c];
        dep = adep;
        mina(minv, adep);
        maxa(maxv, adep);
    }

    if (type == 0 && minv >= 0) {
        maxa(um[dep], maxv);
    }
    else if (type == 1 && dep <= 0 && minv >= dep && um.count(-dep)) { // if minv < dep, then a sequence cannot be completed
        int cans = max(um[-dep], -dep + maxv);
        maxa(ans, cans);
    }
    
    for (auto to : g[c]) {
        if (to != p && !block[to]) {
            dfs(to, c, dep, minv, maxv, um, type);
        }
    }
}

void decomp(int c) {
    gsz(c, -1);
    if (sz[c] == 1) return;

    int cent = gcent(c, -1, sz[c] / 2);
    unordered_map<int, int> um;
    if (val[cent] >= 0) um[val[cent]] = val[cent];
    for (auto to : g[cent]) {
        if (!block[to]) {
            dfs(to, cent, 0, 0, 0, um, 1);
            dfs(to, cent, val[cent], val[cent], val[cent], um, 0);
        }
    }
    um.clear();
    if (val[cent] >= 0) um[val[cent]] = val[cent];
    for (auto it = g[cent].rbegin(); it != g[cent].rend(); it++) {
        int to = *it;
        if (!block[to]) {
            dfs(to, cent, 0, 0, 0, um, 1);
            dfs(to, cent, val[cent], val[cent], val[cent], um, 0);
        }
    }
    ans = max(ans, um[0]);

    block[cent] = true;
    for (auto to : g[cent])
        if (!block[to])
            decomp(to);
}

int main() {
    init_file_io();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    for (auto i = 2; i <= N; i++) {
        int p;
        cin >> p;
        g[p].pb(i);
        g[i].pb(p);
    }
    for (auto i = 1; i <= N; i++) {
        char c;
        cin >> c;
        val[i] = c == ')' ? -1 : 1;
    }

    decomp(1);
    cout << (ans) << '\n';

    return 0;
}

