// ./problem-g-grid-magic.yml
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

const int MN = 9;
const int P[83] = {2, 3, 5, 7, 23, 29, 31, 37, 53, 59, 71, 73, 79, 233, 239, 293, 311, 313, 317, 373, 379, 593, 599, 719, 733, 739, 797, 2333, 2339, 2393, 2399, 2939, 3119, 3137, 3733, 3739, 3793, 3797, 5939, 7193, 7331, 7333, 7393, 23333, 23339, 23399, 23993, 29399, 31193, 31379, 37337, 37339, 37397, 59393, 59399, 71933, 73331, 73939, 233993, 239933, 293999, 373379, 373393, 593933, 593993, 719333, 739391, 739393, 739397, 739399, 2339933, 2399333, 2939999, 3733799, 5939333, 7393913, 7393931, 7393933, 23399339, 29399999, 37337999, 59393339, 73939133};
vector<int> nums[MN];

int digc(int x) {
    int res = 0;
    while (x) {
        res++;
        x /= 10;
    }
    return res;
}

bool OWO(int x) {
    int idx = lower_bound(P, P + 83, x) - P;
    return idx < 83 && P[idx] == x;
}
ll pick(ll n, ll k) {
    ll res = 1;
    for (auto i = 1; i <= n; i++) res *= i;
    for (auto i = 1; i <= n-k; i++) res /= i;
    return res;
}
ll bruh(ll n, ll m) {
    return pick(SZ(nums[m]), n);
}

int N, M;

ll ans = 0;
int digs[MN][MN];
bool use[MN];
void rec(int c) {
    if (c == N) {
        bool good = true;
        for (auto i = 0; i < M; i++) {
            int num = 0;
            for (auto j = 0; j < N; j++)
                num = (num * 10) + digs[j][i];
            if (!OWO(num)) {
                good = false;
                break;
            }
        }
        ans += good;
        // if (good) {
        //     for (auto i = 0; i < N; i++) {
        //         for (auto j = 0; j < M; j++)
        //             cout<<digs[i][j];
        //         cout<<'\n';
        //     }
        //     cout << ("---") << '\n';
        // }
        return;
    }

    for (auto i = 0; i < SZ(nums[M]); i++) {
        // if (!use[i]) {
        //     use[i] = true;
            for (int cnum = nums[M][i], ptr = M-1; ptr >= 0; cnum /= 10, ptr--) {
                // cout<<"c="<<(c)<<", "; cout<<"i="<<(i)<<", "; cout<<"cnum="<<(cnum)<<", "; cout<<"nums[M][i]="<<(nums[M][i])<<", "; cout<<"ptr="<<(ptr)<<", "; cout << endl; // db c,i,cnum,nums[M][i],ptr
                digs[c][ptr] = cnum % 10;
            }
            rec(c + 1);
            // use[i] = false;
        // }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M);
    if (bruh(N, M) > bruh(M, N))
        swap(N, M);
    for (auto x : P)
        nums[digc(x)].pb(x);

    rec(0);
    cout << (ans) << '\n';

    return 0;
}

