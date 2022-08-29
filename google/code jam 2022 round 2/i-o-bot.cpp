// ./i-o-bot.yml
#include <bits/stdc++.h>
#define DEBUG 0
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

const int MN = 1e5 + 1;
int N, C;

ll rundp(vector<pii> balls) {
    if (balls.empty()) return 0LL;

    int sz = SZ(balls);
    sort(all(balls));

    ll ans = 0;
    set<int> unpaired[2];
    set<pii> pairedSame[2];
    for (auto i = sz-1; i >= 0; i--) {
        auto [p, s] = balls[i];

        vector<pair<ll, int>> costs;
        // 0 -> base cost
        // 1 -> takeDifferentPairedCost
        // 2 -> take different unpaired
        // 3 -> take same unpaired
        //
        // If we pair up opposite colours, we cannot improve on that further
        
        costs.eb(2LL * p, 0);
        if (!unpaired[s ^ 1].empty())
            costs.eb(0, 2);
        if (!unpaired[s].empty())
            costs.eb(C, 3);
        if (!pairedSame[s ^ 1].empty()) {
            ll ccost = 2LL * pairedSame[s ^ 1].begin()->fs - C;
            if (!unpaired[s].empty())
                ccost -= 2 * *prev(unpaired[s].end());
            costs.eb(ccost, 1);
        }

        sort(all(costs));
        auto [cost, action] = costs[0];

        if (DEBUG) { cout<<"i="<<(i)<<", "; cout<<"p="<<(p)<<", "; cout<<"s="<<(s)<<", "; cout<<"cost="<<(cost)<<", "; cout<<"action="<<(action)<<", "; cout << endl; } //__RAW_DEBUG_LINE__:db i,p,s,cost,action
        
        ans += cost;
        if (action == 0) {
            unpaired[s].insert(p);
        }
        else if (action == 1) {
            auto [tplo, tphi] = *pairedSame[s ^ 1].begin();
            pairedSame[s ^ 1].erase(pairedSame[s ^ 1].begin());

            if (!unpaired[s].empty()) {
                unpaired[s].erase(prev(unpaired[s].end()));
            }
            else {
                unpaired[s ^ 1].insert(tphi); // we pair up tplo and p, which are opposite colours
            }
        }
        else if (action == 2) {
            unpaired[s ^ 1].erase(prev(unpaired[s ^ 1].end()));
        }
        else {
            auto lst = prev(unpaired[s].end());
            pairedSame[s].insert(pii(p, *lst));
            unpaired[s].erase(lst);
        }
    }

    return ans;
}

void solve() {
    cin >> N >> C;

    vector<pii> ballsp, ballsn;
    for (auto i = 0; i < N; i++) {
        int p, s; cin >> p >> s;
        if (p < 0) ballsn.eb(-p, s);
        else if (p > 0) ballsp.eb(p, s);
    }

    ll ans = rundp(ballsn) + rundp(ballsp);
    cout << (ans) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for (int caseno = 1; caseno <= T; caseno++) {
        // Input
       
        cout << "Case #" << caseno << ": ";
        solve();

        // Reset
    }
}

