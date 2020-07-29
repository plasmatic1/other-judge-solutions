// f-pure.yml
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
template <typename C> int SZ(C &v) { return v.size(); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 1001, MM = 2001;
int N, M,
    A[MM], B[MM];
vector<int> g[MN];

int len = INF;
vector<int> ans;
int dis[MN], par[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M);
    for (auto i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        A[i] = a; B[i] = b;
    }

    for (auto i = 0; i < M; i++) {
        memset(dis, 0x3f, sizeof dis);
        queue<int> q;
        q.push(B[i]); dis[B[i]] = 0; par[B[i]] = -1;
        while (!q.empty()) {
            int c = q.front(), cdis = dis[c]; q.pop();
            for (int to : g[c]) {
                if (dis[to] == INF) {
                    dis[to] = cdis + 1;
                    par[to] = c;
                    q.push(to);
                }
            }
        }
        if (dis[A[i]] + 1 < len) {
            len = dis[A[i]] + 1;
            ans.clear();
            for (int c = A[i]; c != -1; c = par[c])
                ans.pb(c);
        }
    }

    if (len == INF)
        cout << (-1) << '\n';
    else {
        cout << (len) << '\n';
        for (auto x : ans)
            cout << (x) << '\n';
    }

    return 0;
}

