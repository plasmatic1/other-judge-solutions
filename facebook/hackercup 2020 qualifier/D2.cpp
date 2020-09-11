// D2.yml
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

/*
 * BIT indexed from 0..N-1
 */
struct BIT {
    vector<ll> bit;
    int N;
    BIT(int n0, ll def) : bit(n0 + 1, def), N(n0) {}
    void upd(int x, ll v) { x++;
        for (; x <= N; x += x & -x)
            mina(bit[x], v);
    }
    ll query(int x) { x++;
        ll res = LLINF;
        for (; x; x -= x & -x)
            mina(res, bit[x]);
        return res;
    }
};

void init_file_io() {
#ifndef LOCAL
    const string PROBLEM_ID = "prob";
    freopen((PROBLEM_ID + ".in").c_str(), "r", stdin);
    freopen((PROBLEM_ID + ".out").c_str(), "w", stdout);
#endif
}

const int MN = 1e6 + 1;
int N; ll M; int A, B;
vector<int> cost, dep;
vector<vector<int>> g;
vector<bool> mark;

int its;
void dfsInit(int c, int p, int cdep) {
    dep[c] = cdep;
    assert(--its >= 0);
    if (c == A) return void(mark[c] = true);
    for (int to : g[c]) {
        if (to != p) {
            dfsInit(to, c, cdep + 1);
            mark[c] = mark[c] | mark[to];
        }
    }
}

vector<vector<int>> subt;
BIT best(1, 1); // key by depth

void dfs(int c, int p) {
    if (c == A) return void(best.upd(dep[c], 0));

    // Returns only unmarked nodes
    if (!mark[c]) subt[c].pb(c);
    for (int to : g[c]) { // subtrees can't be marked either
        if (to != p) {
            dfs(to, c);
            if (!mark[to]) {
                if (SZ(subt[to]) > SZ(subt[c])) subt[to].swap(subt[c]);
                subt[c].insert(subt[c].end(), all(subt[to]));
                subt[to].resize(0);
            }
        }
    }

    if (mark[c]) {
        if (cost[c]) {
            ll cans = best.query(min(N - 1LL, dep[c] + M)) + cost[c];
            best.upd(dep[c], cans);
            // cout<<"c="<<(c)<<", "; cout<<"dep[c]="<<(dep[c])<<", "; cout<<"cans="<<(cans)<<", "; cout << endl; // db c,dep[c],cans
        }

        vector<ll> sans;
        for (auto x : subt[c]) {
            int delta = dep[x] - dep[c];
            if (M >= delta && cost[x]) {
                ll cans = best.query(min(N - 1LL, dep[c] + M - delta)) + cost[x];
                sans.pb(cans);
            }
            else sans.pb(LLINF);
        }
        for (auto i = 0; i < SZ(subt[c]); i++) {
            best.upd(dep[subt[c][i]], sans[i]); }
    }
}

int main() {
    init_file_io();
    int T;
    cin >> T;
    for (int caseno = 1; caseno <= T; caseno++) {
        // Input
       
        cout << "Case #" << caseno << ": ";

        cin >> N >> M >> A >> B;

        cost.assign(N, 0);
        g.assign(N, vector<int>());
        mark.assign(N, false);
        dep.assign(N, -1);

        subt.assign(N, vector<int>());
        best = BIT(N, LLINF);

        A--; B--;
        for (auto i = 0; i < N; i++) {
            int p;
            cin >> (p) >> (cost[i]);
            if (p) {
                g[p - 1].pb(i);
                g[i].pb(p - 1);
            }
        }
        its=N;
        dfsInit(B, -1, 0);
        dfs(B, -1);

        ll ans = best.query(min(N - 1LL, M));
        cout << (ans == LLINF ? -1 : ans) << '\n';

        cerr << "Done case " << caseno << endl;
    }
}

