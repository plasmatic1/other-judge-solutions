// ./lccmoose-20-contest-2-s2-squares-nah.yml
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

ostream& operator<<(ostream& out, const pii o) {
    out << "(fs=" << o.fs << ", sn=" << o.sn << ")";
    return out;
}

int radius(int x, int y) {
    return x * x + y * y;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int R, Q;
    cin >> R >> Q;

    set<pii> ps;
    pii c{R, 0};
    // int its=100;
    while (1) {
        // assert(its--);
        ps.insert(c);
        int best = INF; 
        // vector<pii> bestp;
        pii bestp;
        // cout<<"c="<<(c)<<", "; cout << endl; // db c
        for (auto i = -1; i <= 1; i++) {
            for (auto j = -1; j <= 1; j++) {
                if (i || j) {
                    int x = c.fs + i, y = c.sn + j, d = abs(R*R - radius(x, y));
                    // if (d < best) {
                    //     best = d;
                    //     bestp.clear();
                    //     bestp.pb(mpr(x, y));
                    // }
                    // else if (d == best)
                    //     bestp.pb(mpr(x, y));
                    // cout<<"x="<<(x)<<", "; cout<<"y="<<(y)<<", "; cout<<"d="<<(d)<<", "; cout<<"best="<<(best)<<", "; cout << endl; // db x,y,d,best
                    if (x == R && y == 0 && SZ(ps) > 2) goto after;
                    if (!ps.count(mpr(x, y)) && d < best) {
                        best = d;
                        bestp = mpr(x, y);
                    }
                }
            }
        }
        if (best == INF) break;
        c = bestp;
        // bool bad = true;
        // for (auto p : bestp) {
        //     if (!ps.count(p)) {
        //         bad = false;
        //         c = p;
        //         break;
        //     }
        // }
        // if (bad)
        //     break;
    }
after:

    for (auto i = 0; i < Q; i++) {
        int x, y;
        cin >> x >> y;
        if (!ps.count(mpr(x, y)))
            cout << i << ' ';
    }
    cout << '\n';

    return 0;
}

