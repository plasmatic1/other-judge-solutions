// c.yml
#include <bits/stdc++.h>
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

using T = tuple<int, int, int, int>;

const int MN = 51, DIR[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
int N, M,
    sx1, sy1, sx2, sy2,
    ex1, ey1, ex2, ey2,
    dis[MN][MN][MN][MN];
char grid[2][MN][MN];
queue<T> q;

bool ok(int x, int y, int id) {
    return 0 <= x && x < N && 0 <= y && y < M && grid[id][x][y] == '.';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> sx1 >> sy1 >> sx2 >> sy2 >> ex1 >> ey1 >> ex2 >> ey2;
    sx1--; sx2--; sy1--; sy2--;
    ex1--; ex2--; ey1--; ey2--;
    for (auto j = 0; j < 2; j++)
        for (auto i = 0; i < N; i++)
            cin >> grid[j][i];

    memset(dis, 0x3f, sizeof dis);
    dis[sx1][sy1][sx2][sy2] = 0;
    q.emplace(sx1, sy1, sx2, sy2); 
    while (!q.empty()) {
        auto [x1, y1, x2, y2] = q.front(); q.pop();
        // if (dis[x1][y1][x2][y2] <= 5) {
        // cout<<"x1="<<(x1)<<", "; cout<<"y1="<<(y1)<<", "; cout<<"x2="<<(x2)<<", "; cout<<"y2="<<(y2)<<", "; cout<<"dis[x1][y1][x2][y2]="<<(dis[x1][y1][x2][y2])<<", "; cout << endl; // db x1,y1,x2,y2,dis[x1][y1][x2][y2]
        // }
        for (auto d : DIR) {
            int ax1 = x1+d[0], ax2 = x2+d[0], ay1 = y1+d[1], ay2 = y2+d[1];
            if (!ok(ax1, ay1, 0)) {
                ax1 -= d[0];
                ay1 -= d[1];
            }
            if (!ok(ax2, ay2, 1)) {
                ax2 -= d[0];
                ay2 -= d[1];
            }

            int alt = dis[x1][y1][x2][y2]+1;
            if (alt < dis[ax1][ay1][ax2][ay2]) {
                dis[ax1][ay1][ax2][ay2] = alt;
                q.emplace(ax1, ay1, ax2, ay2);
            }
        }
    }

    int ans = dis[ex1][ey1][ex2][ey2];
    cout << (ans == INF ? -1 : ans) << '\n';

    return 0;
}
