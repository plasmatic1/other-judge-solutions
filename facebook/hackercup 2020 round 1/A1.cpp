// A1.yml
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

const ll MOD = 1e9 + 7;
ll madd(ll a, ll b, ll mod = MOD) { return (a + b) % mod; }
ll msub(ll a, ll b, ll mod = MOD) { return (a - b + mod) % mod; }
ll mmul(ll a, ll b, ll mod = MOD) { return (a * b) % mod; }
ll fpow(ll x, ll y, ll mod = MOD) {
    if (!y) return 1LL;
    return mmul(fpow(mmul(x, x, mod), y >> 1, mod), (y & 1) ? x : 1LL, mod);
}
ll mdiv(ll x, ll y, ll mod = MOD) { return mmul(x, fpow(y, mod - 2, mod), mod); }

struct Rect {
    ll l, r, h, contrib;
};
ostream& operator<<(ostream& out, const Rect o) {
    out << "(l=" << o.l << ", r=" << o.r << ", h=" << o.h << ", contrib=" << o.contrib << ")";
    return out;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    init_file_io();

    int T;
    cin >> T;
    for (int caseno = 1; caseno <= T; caseno++) {
        // Input
       
        cout << "Case #" << caseno << ": ";

        int N, K, W;
        cin >> N >> K >> W;

        // Input
        vector<ll> L(N), H(N);
        for (auto i = 0; i < K; i++)
            cin >> (L[i]);
        ll _a, _b, _c, _d;
        cin >> _a >> _b >> _c >> _d;
        for (auto i = K; i < N; i++)
            L[i] = (_a * L[i - 2] + _b * L[i - 1] + _c) % _d + 1;
        for (auto i = 0; i < K; i++)
            cin >> (H[i]);
        cin >> _a >> _b >> _c >> _d;
        for (auto i = K; i < N; i++)
            H[i] = (_a * H[i - 2] + _b * H[i - 1] + _c) % _d + 1;

        // Process
        vector<ll> dbPerim;
        deque<Rect> dq;
        ll ans = 1, perim = 0, lastR = -INF;
        for (auto i = 0; i < N; i++) {
            ll l = L[i], r = L[i] + W, contrib = 0;

            perim += r - max(l, lastR);
            if (l > lastR) {
                contrib += H[i];
                contrib += r - l;
                contrib += H[i];
                dq.pb({l, r, H[i], contrib});
            }
            else {
                while (!dq.empty() && dq.back().h <= H[i] && dq.back().l >= l) {
                    perim -= dq.back().contrib;
                    dq.pop_back();
                }

                auto p = dq.back();
                contrib -= p.h;
                contrib += abs(H[i] - p.h) + H[i] + (r - p.r);
                // if (N==2||N==10){
                //     cout<<"i="<<(i)<<", "; cout<<"l="<<(l)<<", "; cout<<"r="<<(r)<<", "; cout<<"H[i]="<<(H[i])<<", "; cout<<"p="<<(p)<<", "; // db i,l,r,H[i],p
                //     cout<<"contrib="<<(contrib)<<", "; cout << endl; // db contrib
                // }
                dq.pb({p.r, r, H[i], contrib});
            }
            perim += contrib;
            dbPerim.pb(perim);
            ans = mmul(ans, perim % MOD);
            lastR = r;
        }
        // cout << "dbPerim=["; for (auto x:dbPerim)cout<<x<<", "; cout<<"], "; cout << endl; // db I:dbPerim
        cout << (ans) << '\n';
    }
}

