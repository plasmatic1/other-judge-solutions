// ./bobs-liar-spotting-game.yml
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

// template is 1-indexed
template <typename T> struct Ranks {
    vector<T> ranks;
    void init() {
        sort(ranks.begin(), ranks.end());
        ranks.resize(unique(ranks.begin(), ranks.end()) - ranks.begin());
    }
    template <typename It> void init(It st, It en) { ranks = vector<T>(st, en); init(); }
    void add(T v) { ranks.pb(v); }
    int get(T v) { return lower_bound(ranks.begin(), ranks.end(), v) - ranks.begin(); }
    int size() { return ranks.size(); }
};

const int MM = 2e4 + 1;
int N, M;
vector<pii> g[MM];
Ranks<int> rs;
tuple<int, int, int> es[MM];

int clr[MM];
void dfs(int c, int cclr, int cM) {
    if (clr[c] != -1) {
        if (cclr != clr[c]) {
            cout << (cM) << '\n';
            exit(0);
        }
        return;
    }
    clr[c] = cclr;
    for (auto to : g[c])
        dfs(to.fs, cclr ^ to.sn, cM);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M);
    for (auto i = 0; i < M; i++) {
        int a, b; string _s;
        cin >> a >> b >> _s;
        es[i] = mtp(a, b+1, _s == "odd");
        rs.add(a); rs.add(b);
    }
    rs.init();

    for (auto i = 0; i < M; i++) {
        int a, b, s; tie(a, b, s) = es[i];
        a = rs.get(a); b = rs.get(b);
        g[a].eb(b, s);
        g[b].eb(a, s);

        memset(clr, -1, sizeof clr);
        for (auto j = 0; j < MM; j++) 
            if (clr[j] == -1)
                dfs(j, 0, i);
    }

    cout << (M) << '\n';

    return 0;
}

