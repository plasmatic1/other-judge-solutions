// ./bobs-homework.yml
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

const ll MOD = 1e9 + 7;
ll fix(ll &&x) { x %= MOD; if (x < 0) x += MOD; return x; }
ll fix(ll &x) { x %= MOD; if (x < 0) x += MOD; return x; }
ll fpow(ll x, ll y, ll mod = MOD) {
    if (!y) return 1LL;
    return fpow(x * x % mod, y >> 1, mod) * ((y & 1) ? x : 1LL) % mod;
}
ll inv(ll x, ll mod = MOD) { return fpow(x, mod - 2, mod); }

const int MM = 1e5 + 1;
int N, K, L, R;
vector<int> p;
ll pN[MM];

int trl(int k) { return (L / k) + (L % k > 0); }
int ilen(int k) { return R / k - trl(k) + 1; }

ll ans = 0;
void rec(int idx, int cnt, ll cval) {
    if (cval > 1) {
        ll comb = fix(pN[ilen(cval)]);
        if (cnt & 1) ans = (ans + comb) % MOD;
        else ans = fix(ans - comb);
    }
    if (idx == SZ(p)) return;
    for (auto i = idx; i < SZ(p); i++) {
        if (cval * p[i] > 1e9) continue;
        if (ilen(cval * p[i]) > 0)
            rec(i + 1, cnt + 1, cval * p[i]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (K) >> (L) >> (R);

    // gcd(seq) = 1 instead of K
    L = trl(K);
    R /= K;

    for (auto i = 1; i < MM; i++) pN[i] = fpow(i, N);
    for (auto i = L; i <= R; i++) {
        int c = i;
        for (int j = 2; j * j <= i; j++) {
            if (c % j == 0) {
                p.pb(j);
                while (c % j == 0) c /= j;
            }
        }
        if (c > 1) p.pb(c);
    }
    UNIQUE(p);

    rec(0, 0, 1);
    ans = fix(pN[R - L + 1] - ans);
    cout << (ans) << '\n';

    return 0;
}

