// ./spiraling-into-control.yml
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

const int MN = 9999 + 1;
int N, K;

inline int disttoend(int x, int y) {
    return abs(x - N / 2) + abs(y - N / 2);
}

inline int dist(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

const pii DIRS[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
vector<int> remAmt;
int curdir = 0;

inline void init() {
    remAmt.pb(N-1);
    for (auto i = N-1; i >= 1; i--) {
        remAmt.pb(i);
        remAmt.pb(i);
    }
    reverse(all(remAmt));
    curdir = 0;
}

inline pii step() {
    auto ret = DIRS[curdir];
    int &lst = remAmt[SZ(remAmt) - 1];
    lst--;
    if (lst == 0) {
        remAmt.pop_back();
        curdir = (curdir + 1) % 4;
    }

    // if (DEBUG) { cout<<"ret.fs="<<(ret.fs)<<", "; cout<<"ret.sn="<<(ret.sn)<<", "; cout << endl; } //__RAW_DEBUG_LINE__:db ret.fs,ret.sn
    // cout.flush();

    return ret;
}

void solve() {
    cin >> N >> K;
    
    if (K % 2 == 1 || K < N - 1) { // impossible cases
        cout << ("IMPOSSIBLE") << '\n';
        return;
    }

    init();

    vector<pii> shortcut;
    int x = 0, y = 0, cur = 1, pre = 1;
    int prex = 0, prey = 0;
    int remdist = -1;
    while (cur < N*N) {
        if (remdist == -1 && disttoend(x, y) == K) {
            remdist = disttoend(x, y);
        }

        auto [dx, dy] = step();
        int nx = x+dx, ny = y+dy;

        x = nx;
        y = ny;
        cur++;

        if (remdist == -1) {
            K--;
            pre = cur;
            prex = x;
            prey = y;
        }
        else if (disttoend(nx, ny) == remdist - 1) {
            if (cur > pre && dist(x, y, prex, prey) == 1) {
                remdist--;
                if (cur - pre > 1) {
                    shortcut.eb(pre, cur);
                }

                K--;
                pre = cur;
                prex = x;
                prey = y;
            }
        }
    }

    cout << (SZ(shortcut)) << '\n';
    for (auto [x, y] : shortcut)
        cout << (x) << ' ' << (y) << '\n';
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

