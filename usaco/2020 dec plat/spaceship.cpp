// spaceship.yml
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
ll fix(ll &x) { x %= MOD; if (x < 0) x += MOD; return x; }
ll fix(ll &&x) { x %= MOD; if (x < 0) x += MOD; return x; }

int N;
const int MN = 60;
struct Vector {
    ll m[MN];
    Vector() { memset(m, 0, sizeof m); }
    Vector sum(Vector &o) {
        Vector res = *this;
        for (auto i = 0; i < N; i++)
            res.m[i] = (res.m[i] + o.m[i]) % MOD;
        return res;
    }
    Vector sum(Vector &&o) { return sum(o); }
};
struct Matrix {
    ll m[MN][MN];
    Matrix() { memset(m, 0, sizeof m); }
    Matrix sum(Matrix &o) {
        Matrix res = *this;
        for (auto i = 0; i < N; i++)
            for (auto j = 0; j < N; j++)
                res.m[i][j] = (res.m[i][j] + o.m[i][j]) % MOD;
        return res;
    }
    Matrix sum(Matrix &&o) { return sum(o); }
    Vector mul(Vector &o) {
        Vector res;
        for (auto i = 0; i < N; i++)
            for (auto j = 0; j < N; j++)
                res.m[i] = (res.m[i] + m[i][j] * o.m[j]) % MOD;
        return res;
    }
    Vector mul(Vector &&o) { return mul(o); }
    Matrix mul(Matrix &o) {
        Matrix res;
        for (auto i = 0; i < N; i++)
            for (auto j = 0; j < N; j++)
                for (auto k = 0; k < N; k++)
                    res.m[i][j] = (res.m[i][j] + m[i][k] * o.m[k][j]) % MOD;
        return res;
    }
    Matrix mul(Matrix &&o) { return mul(o); }
};

int K, Q;
Matrix adj, dp[MN+2];
Vector dp3[MN+1], dp2[MN+1];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (K) >> (Q);
    for (auto i = 0; i < N; i++) {
        string s;
        cin >> s;
        for (auto j = 0; j < N; j++)
            adj.m[j][i] = s[j] - '0';
    }

    for (auto i = 0; i < N; i++) dp[0].m[i][i] = 1;
    dp[1] = adj;
    for (auto i = 2; i <= K; i++)
        dp[i] = dp[i-1].sum(dp[i-1].mul(dp[i-1]));

    while (Q--) {
        int bs, s, bt, t;
        cin >> bs >> s >> bt >> t;
        s--; t--;

        fill(dp3 + 1, dp3 + K + 1, Vector());
        fill(dp2 + 1, dp2 + K + 1, Vector());
        dp2[bs].m[s] = 1;
        dp2[bs+1] = dp[bs].mul(dp2[bs]);
        for (auto i = bs+2; i <= K; i++)
            dp2[i] = dp2[i-1].sum(dp[i-1].mul(dp2[i-1]));

        for (auto i = K; i >= bt; i--) {
            for (auto j = i+1; j <= K; j++)
                dp3[i] = dp3[i].sum(dp3[j]);
            dp3[i] = dp[i].mul(dp3[i]);
            for (auto j = 0; j < N; j++)
                dp3[i].m[j] = fix(dp3[i].m[j] + dp2[i].m[j]);
        }
        cout << (dp3[bt].m[t]) << '\n';
    }

    return 0;
}

