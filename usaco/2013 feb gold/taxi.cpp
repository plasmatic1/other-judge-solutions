// ./uber-driver.yml
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

struct seg {
    int s, e;
    int l() const { return min(s, e); }
    int r() const { return max(s, e); }
    bool operator<(const seg &o) const {
        return l() < o.l();
    }
};
istream& operator>>(istream& in, seg &o) {
    return in >> o.s >> o.e;
}
ostream& operator<<(ostream& out, const seg o) {
    out << "(s=" << o.s << ", e=" << o.e << ")";
    return out;
}

const int MN = 1e5 + 1;
int N, L,
    fwd[MN*2], rev[MN*2];
seg segs[MN];
vector<int> rnk;

int get(int x) {
    return lower_bound(all(rnk), x) - rnk.begin() + 1;
}

void init_file_io() {
#ifndef LOCAL
    const string PROBLEM_ID = "taxi";
    freopen((PROBLEM_ID + ".in").c_str(), "r", stdin);
    freopen((PROBLEM_ID + ".out").c_str(), "w", stdout);
#endif
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_file_io();
    cin >> (N) >> (L);

    for (auto i = 0; i < N; i++) {
        cin >> (segs[i]);
        rnk.pb(segs[i].s);
        rnk.pb(segs[i].e);
    }
    rnk.pb(0); rnk.pb(L);
    UNIQUE(rnk);

    for (auto i = 0; i < N; i++) {
        auto &ss = segs[i];
        if (ss.s > ss.e) 
            rev[get(ss.e)]++, rev[get(ss.s)]--;
        else
            fwd[get(ss.s)]++, fwd[get(ss.e)]--;
    }

    ll ans = 0;
    for (auto i = 1; i < SZ(rnk); i++) {
        fwd[i] += fwd[i - 1];
        rev[i] += rev[i - 1];

        ll delta = rnk[i] - rnk[i - 1];
        ans += max(fwd[i] - 1, rev[i]) * 2LL * delta + delta;
    }
    cout << (ans) << '\n';

    return 0;
}

