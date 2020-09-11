// A2.yml
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
    const string PROBLEM_ID = "prob";
    freopen((PROBLEM_ID + ".in").c_str(), "r", stdin);
    freopen((PROBLEM_ID + ".out").c_str(), "w", stdout);
#endif
}

ostream& operator<<(ostream& out, const pll o) {
    out << "(fs=" << o.fs << ", sn=" << o.sn << ")";
    return out;
}

const ll MOD = 1e9 + 7;
ll madd(ll a, ll b, ll mod = MOD) { return (a + b) % mod; }
ll msub(ll a, ll b, ll mod = MOD) { return (a - b + mod) % mod; }
ll mmul(ll a, ll b, ll mod = MOD) { return (a * b) % mod; }
ll fpow(ll x, ll y, ll mod = MOD) {
    if (!y) return 1LL;
    return mmul(fpow(mmul(x, x, mod), y >> 1, mod), (y & 1) ? x : 1LL, mod);
}
ll mdiv(ll x, ll y, ll mod = MOD) { return mmul(x, fpow(y, mod - 2, mod), mod); }

template <typename T> void read_fhc_array(vector<T> &v, int sz, int k, int inc = 1) {
    for (auto i = 0; i < k; i++)
        cin >> v[i];
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    for (auto i = k; i < sz; i++)
        v[i] = (a * v[i - 2] + b * v[i - 1] + c) % d + inc;
}

// struct Seg {
//     ll l, r;
//     bool operator<(const Seg &o) const {
//         return l == o.l ? r < o.r : l < o.l;
//     }
// };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_file_io();

    int T;
    cin >> T;
    for (int caseno = 1; caseno <= T; caseno++) {
        // Input
       
        cout << "Case #" << caseno << ": ";
        int N, K;
        cin >> N >> K;
        vector<ll> L(N), W(N), H(N);
        read_fhc_array(L, N, K);
        read_fhc_array(W, N, K);
        read_fhc_array(H, N, K);

        set<pll> segs;
        segs.emplace(-INF, -INF);
        segs.emplace(INF, INF);

        vector<ll> dbperim;

        ll ans = 1, perim = 0;
        for (auto i = 0; i < N; i++) {
            ll l = L[i], r = l + W[i], tl = l, tr = r;
            auto ptr = segs.lower_bound(mpr(l, -INF)); ptr--;

            ll contrib = 0;
            if (ptr->sn < l) ptr++;
            vector<pll> rem;

            contrib += H[i] * 2; // left and right bounds
            while (ptr != segs.end() && ptr->fs <= r) {
                int numIn = (ptr->fs >= l) + (ptr->sn <= r);
                contrib -= H[i] * numIn; // removes bottom vertical section of perimeter of thing

                mina(tl, ptr->fs);
                maxa(tr, ptr->sn);
                if (ptr->fs < l) contrib -= H[i];
                if (ptr->sn > r) contrib -= H[i];

                rem.pb(*ptr);

                ptr++;
            }

            for (auto &x : rem) {
                segs.erase(x);
                contrib -= (x.sn - x.fs) * 2; // remove bottom section of perimeter of thing
            }
            segs.emplace(tl, tr);
            contrib += (tr - tl) * 2;
            // contrib -= (l - tl) + (tr - r);

            perim += contrib;
            dbperim.pb(perim);
            // if (N<=10){
            // cout<<"i="<<(i)<<", "; cout << "segs=["; for (auto x:segs)cout<<x<<", "; cout<<"], "; cout << endl; // db i,I:segs
            // }
            ans = mmul(ans, perim % MOD);
        }

        // cout << "dbperim=["; for (auto x:dbperim)cout<<x<<", "; cout<<"], "; cout << endl; // db I:dbperim

        cout << (ans) << '\n';

        // Reset
#ifndef LOCAL
        cerr << "Done case #" << caseno << endl;
#endif
    }

    return 0;
}

