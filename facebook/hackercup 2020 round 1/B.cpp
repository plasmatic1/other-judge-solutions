// B.yml
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init_file_io();

    int T;
    cin >> T;
    for (int caseno = 1; caseno <= T; caseno++) {
        // Input
       
        cout << "Case #" << caseno << ": ";

        // Input
        int N, M, K, S;
        cin >> N >> M >> K >> S;
        vector<ll> P(N), Q(M);
        for (auto i = 0; i < K; i++)
            cin >> (P[i]);
        ll _a, _b, _c, _d;
        cin >> _a >> _b >> _c >> _d;
        for (auto i = K; i < N; i++)
            P[i] = (_a * P[i - 2] + _b * P[i - 1] + _c) % _d + 1;
        for (auto i = 0; i < K; i++) 
            cin >> (Q[i]);
        cin >> _a >> _b >> _c >> _d;
        for (auto i = K; i < M; i++)
            Q[i] = (_a * Q[i - 2] + _b * Q[i - 1] + _c) % _d + 1;

        sort(all(P));
        sort(all(Q));

        auto cost = [&] (deque<ll> &dq, ll pos) -> ll {
            if (dq.empty()) return 0LL;
            ll lp = dq.front(), rp = dq.back(), cnt = SZ(dq);
            mina(lp, pos); maxa(rp, pos);
            if (lp > rp) swap(lp, rp);

            ll llen = pos - lp, rlen = rp - pos;
            if (llen > rlen) swap(llen, rlen);
            return llen * 2 + rlen + (ll)S * cnt;
        };
        auto check = [&] (ll lim) -> bool {
            int ptr = 0;
            for (auto i = 0; i < N; i++) {
                deque<ll> dq;
                while (ptr < M && cost(dq, P[i]) <= lim) {
                    dq.pb(Q[ptr]);
                    ptr++;
                }
                while (cost(dq, P[i]) > lim) {
                    dq.pop_back();
                    ptr--;
                }
            }

            return ptr == M;
        };

        ll l = -1, r = 1e17;
        while (l + 1 < r) {
            ll mid = (l + r) / 2;
            if (check(mid))
                r = mid;
            else
                l = mid;
        }
        cout << (r) << '\n';
        cout.flush();

        // Reset
#ifndef LOCAL
        cerr << "Done case #" << caseno << endl;
#endif
    }
}
