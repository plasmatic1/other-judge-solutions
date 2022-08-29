// ./matching-palindrome.yml
#include <bits/stdc++.h>
#define DEBUG 1
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
#if __cplusplus == 201703L // CPP17 only things
template <typename T> using opt_ref = optional<reference_wrapper<T>>; // for some templates
#endif
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

// Hashing stuff
const int FIXED_BASE = 0, RAND_BASE = 1 << 0;
const ll MOD = 999999999999999989;
ll BASE = 131;

vector<ll> _hash_pows;
template <int MODE> void init_hash(int MAX_N) {
    if (MODE & RAND_BASE) {
        mt19937 mt(RANDOM);
        BASE = uniform_int_distribution<ll>(MOD/2, MOD-2)(mt);
    }

    _hash_pows.resize(MAX_N + 1);
    _hash_pows[0] = 1LL;
    for (auto i = 1; i <= MAX_N; i++)
        _hash_pows[i] = __int128(_hash_pows[i - 1]) * BASE % MOD;
}
template <typename It> ll hget(It hs, int l, int r) {
    __int128 res = (hs[r] - __int128(hs[l - 1]) * _hash_pows[r - l + 1]) % MOD;
    if (res < 0) res += MOD;
    return res;
}
ll happend(ll hsh, int val) { return (__int128(hsh) * BASE + val) % MOD; }
ll hconcat(ll hshLeft, ll hshRight, int szRight) { return (__int128(hshLeft) * _hash_pows[szRight] + hshRight) % MOD; }

// stuff
const int MN = 1e5+1;
int N;
string s;
ll hs[MN], rhs[MN]; // hash, revhash

bool isPali(int l, int r) { // assume l <= r
    if (l > r) return true; // empty string

    ll hFw = hget(hs, l, r), hBw = hget(rhs, N-r+1, N-l+1);
    return hFw == hBw;
}

void solve() {
    cin >> N >> s;
    s = " " + s;

    for (auto i = 1; i <= N; i++) {
        hs[i] = happend(hs[i-1], s[i]);
        rhs[i] = happend(rhs[i-1], s[N-i+1]);
    }

    string ans;
    for (auto i = 1; i <= N; i++) {
        if (isPali(1, i) && isPali(i+1, N)) {
            ans = s.substr(1, i);
            break;
        }
    }

    cout << (ans) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_hash<FIXED_BASE>(MN);

    int T;
    cin >> T;
    for (int caseno = 1; caseno <= T; caseno++) {
        // Input
       
        cout << "Case #" << caseno << ": ";
        solve();

        // Reset
    }
}

