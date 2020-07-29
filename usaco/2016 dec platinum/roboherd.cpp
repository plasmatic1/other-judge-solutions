// problem-3-robotic-cow-herd.yml
#include "bits/stdc++.h"
using namespace std;

// Defines
#define pb push_back
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
template <typename C> int SZ(C &v) { return v.size(); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

struct State {
    int cset, pos; ll sum;

    bool operator<(const State &o) const {
        return sum > o.sum;
    }
};

const int MN = 1e5 + 1;
int N, K;
vector<vector<ll>> vals;
priority_queue<State> pq;
ll ans = 0;

bool cmpVec(const vector<ll> &a, const vector<ll> &b) {
    return a[1] - a[0] < b[1] - b[0];
}

void init_file_io() {
#ifndef LOCAL
    const string PROBLEM_ID = "roboherd";
    freopen((PROBLEM_ID + ".in").c_str(), "r", stdin);
    freopen((PROBLEM_ID + ".out").c_str(), "w", stdout);
#endif
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_file_io();

    cin >> (N) >> (K);
    ll isum = 0;
    for (auto i = 0; i < N; i++) {
        int n;
        cin >> n;
        vector<ll> v;
        for (auto j = 0; j < n; j++) {
            ll x;
            cin >> x;
            v.pb(x);
        }
        sort(all(v));
        isum += v[0];
        if (SZ(v) > 1)
            vals.pb(v);
    }
    sort(all(vals), cmpVec);

    pq.push({0, 0, isum});

    for (auto i = 0; i < K; i++) {
        auto c = pq.top(); pq.pop();
        ans += c.sum;
        // cout<<"i="<<(i)<<", "; cout<<"c.sum="<<(c.sum)<<", "; cout << endl; // db i,c.sum

        if (c.pos + 1 < SZ(vals[c.cset]))
            pq.push({c.cset, c.pos + 1, c.sum + vals[c.cset][c.pos + 1] - vals[c.cset][c.pos]});
        if (c.cset + 1 < SZ(vals)) {
            if (c.pos == 1) pq.push({c.cset + 1, 1, c.sum - (vals[c.cset][1] - vals[c.cset][0]) + (vals[c.cset + 1][1] - vals[c.cset + 1][0])});
            if (c.pos > 0) pq.push({c.cset + 1, 1, c.sum + vals[c.cset + 1][1] - vals[c.cset + 1][0]});
        }
    }

    cout << (ans) << '\n';

    return 0;
}

