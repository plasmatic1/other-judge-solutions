// ./bobs-sequences-on-a-tree.yml
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

const int MLEN = 1e6;
struct SAM {
    struct state {
        int len, link;
        map<char, int> to;
    };
    state st[MLEN*2];
    int last, sz = 0;
    void init() {
        for (auto i = 0; i < MLEN*2; i++) st[i] = {0, 0, map<char, int>()};
        st[0] = {0, -1, map<char, int>()};
        sz = 1; last = 0;
    }
    int extend(int last, char c) {
        int cur = sz++, p = last;
        st[cur].len = st[last].len + 1;
        for (; p != -1 && !st[p].to.count(c); p = st[p].link)
            st[p].to[c] = cur;
        if (p == -1) st[cur].link = 0;
        else {
            int q = st[p].to[c];
            if (st[p].len + 1 == st[q].len) st[cur].link = q; // transition is continuous, we can link directly to Q as the parent in the prefix trie
            else { // transition is discontinuous, we must split node q into p+1, 
                int clone = sz++; 
                st[clone] = st[q]; st[clone].len = st[p].len + 1;
                for (; p != -1 && st[p].to[c] == q; p = st[p].link)
                    st[p].to[c] = clone;
                st[cur].link = st[q].link = clone;
            }
        }

        return last = cur;
    }
};

const int MN = 1e5 + 1;
int N, C,
    A[MN];
vector<int> g[MN];
SAM sam;

int node[MN];
void dfs(int c, int p) {
    node[c] = sam.extend(p == -1 ? 0 : node[p], A[c]);
    for (auto to : g[c])
        if (to != p)
            dfs(to, c);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> C;
    for (auto i = 1; i <= N; i++)
        cin >> A[i];
    for (auto i = 0; i < N-1; i++) {
        int a, b; cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }
    sam.init();
    for (auto i = 1; i <= N; i++) {
        if (SZ(g[i]) == 1) {
            dfs(i, -1);
        }
    }
    ll ans = 0;
    for (auto i = 1; i < sam.sz; i++) ans += sam.st[i].len - sam.st[sam.st[i].link].len;
    cout << (ans) << '\n';

    return 0;
}

