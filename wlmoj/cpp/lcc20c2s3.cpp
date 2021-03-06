// ./lccmoose-20-contest-2-s3-alans-got-cake-😳.yml
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

const int MN = 1e5 + 1, LG = 17;
int N, K;
ll psum[MN*2];

int tb[LG][MN];
ll go[LG][MN];

bool check(ll want) {
    // cout<<"want="<<(want)<<", "; cout << endl; // db want
    for (auto i = 1; i <= N; i++) {
        int l = i - 1, r = i + N - 1;
        while (l + 1 < r) {
            int mid = (l + r) / 2;
            if (psum[mid] - psum[i-1] >= want)
                r = mid;
            else
                l = mid;
        }

        r++;
        go[0][i] = r - i;
        while (r > N) r -= N;
        tb[0][i] = r;
        // cout<<"i="<<(i)<<", "; cout<<"go[0][i]="<<(go[0][i])<<", "; cout<<"tb[0][i]="<<(tb[0][i])<<", "; cout << endl; // db i,go[0][i],tb[0][i]
    }
    for (auto i = 1; i < LG; i++) {
        for (auto j = 1; j <= N; j++) {
            tb[i][j] = tb[i-1][tb[i-1][j]];
            go[i][j] = go[i-1][j] + go[i-1][tb[i-1][j]];
        }
    }
    for (auto i = 1; i <= N; i++) {
        ll acc = 0; int c = i;
        for (auto j = 0; j < LG; j++) {
            if ((K >> j) & 1) {
                acc += go[j][c];
                c = tb[j][c];
            }
        }
        // cout<<"i="<<(i)<<", "; cout<<"acc="<<(acc)<<", "; cout << endl; // db i,acc
        if (acc <= N) return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (K);
    for (auto i = 1; i <= N; i++) {
        cin >> (psum[i]);
        psum[i+N] = psum[i];
    }
    partial_sum(psum, psum + 2*N + 1, psum);

    // check(9);
    // return 0;

    ll l = 0, r = 1e15;
    while (l + 1 < r) {
        ll mid = (l + r) / 2;
        if (check(mid))
            l = mid;
        else
            r = mid;
    }

    cout << (l) << '\n';

    return 0;
}