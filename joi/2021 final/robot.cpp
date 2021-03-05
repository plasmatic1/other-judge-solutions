// ./bobs-robot.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
#define fs first
#define sn second
using pii = pair<int, int>;

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
template <typename K, typename V> using MP = hashmap<K, V, chash>;

struct ed {
    int v, c; ll w;
    bool operator<(const ed &o) const {
        return w > o.w;
    }
};

const int MN = 1e5 + 1, MM = 2e5 + 1;
int N, M,
    A[MM], B[MM], C[MM], W[MM];
vector<ll> dis[MN];
priority_queue<ed> pq;
vector<int> cols[MN];
MP<int, ll> sumc[MN];
MP<int, int> cmap[MN];
MP<int, vector<tuple<int, int, int>>> g[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (auto i = 0; i < M; i++) {
        int a, b, c, p; cin >> a >> b >> c >> p;
        g[a][c].emplace_back(i, b, p);
        g[b][c].emplace_back(i, a, p);
        sumc[a][c] += p;
        sumc[b][c] += p;
        A[i] = a; B[i] = b; C[i] = c; W[i] = p;
    }

    for (auto i = 1; i <= N; i++) {
        cols[i].push_back(0);
        int ctr = 0;
        for (auto &p : sumc[i]) {
            cmap[i][p.first] = ++ctr;
            cols[i].push_back(p.first);
        }
        dis[i].assign(cmap[i].size()+1, LLINF);

        // printf("i=%d cols=",i);
        // for (int j = 0; j < (int)cols[i].size(); j++) {
        //     printf("(col=%d, id=%d), ", cols[i][j],cmap[i][cols[i][j]]);
        // }
        // printf("\n");
    }

    dis[1][0] = 0; pq.push({1, 0, 0});
    while (!pq.empty()) {
        auto c = pq.top(); pq.pop();
        if (c.w > dis[c.v][c.c]) continue;
        // printf("c=%d colid/col=%d/%d w=%lld\n",c.v,c.c,cols[c.v][c.c],c.w); fflush(stdout);
        if (c.c == 0) {
            for (auto &_cat : g[c.v]) {
                int col = _cat.first;
                for (auto &_to : _cat.second) {
                    int i, to, w; tie(i, to, w) = _to;

                    // assume we're eating this edge uwu
                    ll alt = min(c.w + w, c.w + sumc[c.v][col] - w);
                    ll altSW = c.w;
                    assert(alt >= c.w);
                    assert(altSW >= c.w);

                    // printf("ADJ i=%d to=%d col=%d w=%d altNOSWITCH=%lld colid=%d\n", i,to,col,w,alt,cmap[to][col]); fflush(stdout);

                    // switch colour and regard it
                    int colid = cmap[to][col];
                    if (altSW < dis[to][colid]) {
                        dis[to][colid] = altSW;
                        pq.push({to, colid, altSW});
                    }
                    // disregard switch
                    if (alt < dis[to][0]) {
                        dis[to][0] = alt;
                        pq.push({to, 0, alt});
                    }
                }
            }
        }
        else {
            int col = cols[c.v][c.c];
            for (auto &_to : g[c.v][col]) {
                int i, to, w; tie(i, to, w) = _to;

                // keep same colour continue wee woo
                ll alt = c.w + sumc[c.v][col] - w;
                ll altSW = c.w + sumc[c.v][col];
                assert(alt >= c.w);
                assert(altSW >= c.w);

                // printf("ADJ i=%d to=%d col=%d w=%d altNOSWITCH=%lld colid=%d\n", i,to,col,w,alt,cmap[to][col]); fflush(stdout);

                // switch colour and regard it
                int colid = cmap[to][col];
                if (altSW < dis[to][colid]) {
                    dis[to][colid] = altSW;
                    pq.push({to, colid, altSW});
                }
                // disregard switch
                if (alt < dis[to][0]) {
                    dis[to][0] = alt;
                    pq.push({to, 0, alt});
                }
            }
        }
    }

    ll ans = dis[N][0];
    if (ans == LLINF) ans = -1;
    cout << ans << '\n';

    return 0;
}
