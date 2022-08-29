// ./pixelated-circle.yml
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

const int D = 100, MN = 2*D+1;
int N;
bool b[MN][MN];

inline bool& access(int x, int y) {
    return b[x+D][y+D];
}

ll clear(int R, bool type) {
    ll cnt = 0;
    for (auto x = -R; x <= R; x++) {
        for (auto y = -R; y <= R; y++) {
            if (round(sqrt(x * x + y * y)) <= R) {
                cnt += access(x, y) == type;
                access(x, y) = false;
            }
        }
    }

    return cnt;
}

void draw_circle_perimeter(int R) {
    for (auto x = -R; x <= R; x++) {
        if (R * R - x * x >= 0) {
            int y = round(sqrt(R * R - x * x));   // round to nearest integer, breaking ties towards zero
            if (DEBUG) { cout<<"x="<<(x)<<", "; cout<<"y="<<(y)<<", "; cout << endl; } //__RAW_DEBUG_LINE__:db x,y
            access(x, y) = true;
            access(x, -y) = true;
            access(y, x) = true;
            access(-y, x) = true;
        }
    }
}

void draw_circle_filled_wrong(int R) {
    for (auto i = 0; i <= R; i++) {
        draw_circle_perimeter(i);
    }
}

void solve() {
    cin >> N;

    clear(N, false);
    ll init = clear(N, false);
    draw_circle_filled_wrong(N);
    ll ans = init - clear(N, true);

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
