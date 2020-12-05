// ./problem-2-meetings.yml
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
    const string PROBLEM_ID = "meetings";
    freopen((PROBLEM_ID + ".in").c_str(), "r", stdin);
    freopen((PROBLEM_ID + ".out").c_str(), "w", stdout);
#endif
}

struct cow {
    int w, x, d;
    bool operator<(const cow &o) const {
        return x < o.x;
    }
};

const int MN = 5e4 + 1;
int N, L, need = 0;
cow cows[MN];
ll leave[MN];

int main() {
    init_file_io();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (L);
    for (auto i = 0; i < N; i++) {
        int w, x, d;
        cin >> w >> x >> d;
        cows[i] = {w, x, d};
        need += w;
    }
    need = (need + 1) / 2;
    sort(cows, cows + N);

    ll T = 0;
    multiset<ll> left; multiset<ll, greater<ll>> right;
    for (auto i = 0; i < N; i++) {
        if (cows[i].d == -1)
            left.insert(cows[i].x);
        else
            right.insert(L - cows[i].x);
    }

    copy(all(left), leave);
    copy(all(right), leave + SZ(left));

    map<int, ll> sums;
    ll csum = 0;
    for (auto i = 0; i < N; i++)
        sums[leave[i]] += cows[i].w;
    for (auto p : sums) {
        csum += p.sn;
        if (csum >= need) {
            T = p.fs;
            break;
        }
    }

    ll ans = 0;
    vector<int> pos;
    for (auto i = 0; i < N; i++) {
        auto &cc = cows[i];
        if (cc.d == -1) {
            int idx = lower_bound(all(pos), cc.x - 2 * T) - pos.begin();
            ans += SZ(pos) - idx;
        }
        else
            pos.pb(cc.x);
    }

    cout << (ans) << '\n';

    return 0;
}

