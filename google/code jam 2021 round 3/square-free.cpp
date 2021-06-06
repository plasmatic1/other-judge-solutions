// ./square-free.yml
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

const int MN = 21;
int R, C, maxSquare,
    rc[MN], cc[MN];
bool grid[MN][MN];

bool inbound(int x, int y) {
    return 0 <= x && x < R && 0 <= y && y < C;
}
bool hasLine(int x, int y, int dx, int dy, int times, int val) {
    for (auto i = 0; i < times; i++) {
        if (!inbound(x, y) || grid[x][y] != val) return false;
        x += dx;
        y += dy;
    }

    return true;
}
void flipLine(int x, int y, int dx, int dy, int times) {
    for (auto i = 0; i < times; i++) {
        assert(inbound(x, y));
        grid[x][y] ^= 1;
        x += dx;
        y += dy;
    }
}

using T = tuple<int, int, int>;
const T BADT = {-1, -1, -1};
T getSquare() {
    for (auto i = 0; i < R; i++) {
        for (auto j = 0; j < C-1; j++) {
            for (auto k = 1; k <= maxSquare; k++) {
                if (hasLine(i, j+1, 1, 1, k, 0) && hasLine(i, j, 1, -1, k, 1) && // top lines
                        hasLine(i+2*k-1, j, -1, -1, k, 0) && hasLine(i+2*k-1, j+1, -1, 1, k, 1)) // bottom lines
                    return {i, j, k}; // got square'd
            }
        }
    }

    return BADT;
}

void solve() {
    cin >> R >> C;
    for (auto i = 0; i < R; i++)
        cin >> rc[i];
    for (auto i = 0; i < C; i++)
        cin >> cc[i];

    // get any grid satisfying properties
    vector<int> rem(cc, cc+C);
    for (auto i = 0; i < R; i++)
        fill(grid[i], grid[i]+C, 0);
    for (auto i = 0; i < R; i++) {
        vector<pii> vs;
        for (auto j = 0; j < C; j++)
            vs.eb(rem[j], j);
        sort(all(vs), greater<pii>());

        assert(rc[i] <= C);
        if (rc[i] > 0) {
            if (vs[rc[i]-1].first > 0) {
                for (auto j = 0; j < rc[i]; j++) {
                    auto [_, col] = vs[j];
                    rem[col]--;
                    grid[i][col] = 1;
                }
            }
            else {
                cout << ("IMPOSSIBLE") << '\n';
                return;
            }
        }
    }
    for (auto i = 0; i < C; i++) {
        if (rem[i] > 0) {
            cout << ("IMPOSSIBLE") << '\n';
            return;
        }
    }

    maxSquare = min(R, C) / 2;
    cout << ("POSSIBLE") << '\n';
    while (1) {
        auto res = getSquare();
        if (res == BADT) break;
        else {
            auto [i, j, k] = res;
            // top lines
            flipLine(i, j+1, 1, 1, k);
            flipLine(i, j, 1, -1, k); 
            // bottom lines
            flipLine(i+2*k-1, j, -1, -1, k);
            flipLine(i+2*k-1, j+1, -1, 1, k);
        }
    }

    for (auto i = 0; i < R; i++) {
        for (auto j = 0; j < C; j++)
            cout << "\\/"[grid[i][j]];
        cout << '\n';
    }
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

