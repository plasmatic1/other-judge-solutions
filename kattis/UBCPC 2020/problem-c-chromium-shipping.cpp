// ./problem-c-chromium-shipping.yml
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

struct Manager {
    using CF = function<ll(int)>;
    set<pair<ll, int>> s;
    CF cost;
    int m;
    Manager(CF cost0, bool max = false) : cost(cost0) {
        m = max ? -1 : 1;
    }
    void add(int k) { s.emplace(m * cost(k), k); }
    void rem(int k) { s.erase(mpr(m * cost(k), k)); }
    auto topI() { return s.begin()->sn; }
    auto top() { return s.begin(); }
    pair<ll, int> pop() {
        auto res = *s.begin();
        s.erase(s.begin());
        res.fs *= m;
        return res;
    }
    bool empty() { return s.empty(); }
};

const int MN = 1e5 + 10;
int N, M, S, T, A, B,
    X[MN], Y[MN];
vector<pii> g[MN];

vector<ll> dijk(int s) {
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    vector<ll> dis(N + 1, LLINF);
    dis[s] = 0; pq.push({0, s});
    while (!pq.empty()) {
        auto c = pq.top(); pq.pop();
        if (c.fs > dis[c.sn]) continue;
        for (auto to : g[c.sn]) {
            ll alt = c.fs + to.sn;
            if (alt < dis[to.fs]) {
                dis[to.fs] = alt;
                pq.emplace(alt, to.fs);
            }
        }
    }
    return dis;
}

ll Sa[MN], Sb[MN], Ta[MN], Tb[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M) >> (S) >> (T) >> (A) >> (B);
    for (auto i = 1; i <= S; i++)
        cin >> (X[i]);
    for (auto i = 1; i <= T; i++)
        cin >> (Y[i]);
    for (auto i = 0; i < M; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        g[a].eb(b, w);
        g[b].eb(a, w);
    }
    auto disA = dijk(A);
    auto disB = dijk(B);

    for (auto i = 1; i <= T; i++) {
        Ta[i] = disA[Y[i]];
        Tb[i] = disB[Y[i]];
    }
    for (auto i = 1; i <= S; i++) {
        Sa[i] = disA[X[i]];
        Sb[i] = disB[X[i]];
    }

    // get initial answer
    ll cans = 0;
    Manager tMan([&] (int k) { return Tb[k] - Ta[k]; });
    for (auto i = 1; i <= T; i++) {
        cans += Ta[i];
        tMan.add(i);
    }
    Manager sManA([&] (int k) { return Sa[k]; }, true),
            sManB([&] (int k) { return Sb[k]; }),
            sManDiff([&] (int k) { return Sb[k] - Sa[k]; });
    for (auto i = 1; i <= S; i++) {
        sManA.add(i);
        sManDiff.add(i);
        cans += Sa[i];
    }
    for (auto i = T+1; i <= S; i++) {
        int p = sManA.pop().sn;
        cans -= Sa[p];
        sManDiff.rem(p);
        sManB.add(p);
    }

    // compute
    ll ans = cans;
    for (auto i = 1; i <= T; i++) { // number of employers going to loc A
        // Change out the T
        cans += tMan.pop().fs;

#define BTOP() (sManB.empty() ? LLINF : sManB.top()->fs)
        // Change out the S
        // Case 1 - remove Max(sa[k]), add Min(sb[k])
        int p = sManA.topI();
        ll d1 = min(BTOP(), Sb[p]) - Sa[p];
        // Case 2 - remove Min(sb[k] - sa[k]), add Min(sb[k])
        p = sManDiff.topI();
        ll d2 = min(BTOP(), Sb[p]) - Sa[p];

        // Update DS
        if (d1 < d2) {
            p = sManA.pop().sn;
            sManDiff.rem(p);
        }
        else {
            p = sManDiff.pop().sn;
            sManA.rem(p);
        }
        sManB.add(p);
        int q = sManB.pop().sn;
        cans += Sb[q] - Sa[p];

        mina(ans, cans);
    }
    cout << (ans) << '\n';

    return 0;
}

