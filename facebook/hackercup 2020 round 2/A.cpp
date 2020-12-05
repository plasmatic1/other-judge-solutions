// A.yml
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

template <typename T> void read_fhc_array(vector<T> &v, int k, int inc = 1) {
    for (auto i = 0; i < k; i++)
        cin >> v[i];
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    for (auto i = k; i < (int)v.size(); i++)
        v[i] = (a * v[i - 2] + b * v[i - 1] + c) % d + inc;
}

#define DB N == 2 || N == 4

void solve() {
    int N, K;
    cin >> N >> K;

    vector<ll> S(N), X(N), Y(N);
    read_fhc_array(S, K, 0);
    read_fhc_array(X, K, 0);
    read_fhc_array(Y, K, 0);

    ll cusSum = 0, reqSum = 0, maxSum = 0, moveTo = 0, moveAway = 0;
    for (auto i = 0; i < N; i++) {
        ll l = X[i], r = X[i] + Y[i];
        if (S[i] < l) moveTo += l - S[i];
        if (S[i] > r) moveAway += S[i] - r;
        cusSum += S[i];
        reqSum += l;
        maxSum += r;
    }

    if (cusSum < reqSum || cusSum > maxSum) 
        cout << (-1) << '\n';
    else {
        ll ans = max(moveTo, moveAway);
        cout << (ans) << '\n';
    }
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
        solve();

        // Reset
#ifndef LOCAL
        cerr << "Done case #" << caseno << endl;
#endif
    }

    return 0;
}

