// ./bobs-coloring-game.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

const int MN = 1e4 + 1;
int N, M;
vector<int> g[MN];

// clr
int clr[MN];
bool bad = false;
void dfs(int c, int cclr) {
    if (clr[c] != -1) {
        if (clr[c] != cclr) bad = true;
        return;
    }
    clr[c] = cclr;
    for (auto to : g[c])
        dfs(to, cclr^1);
}

// tarj
int ord[MN], low[MN], cord = 0;
set<pii> cycEdge;
void tarjan(int c, int p) {
    ord[c] = low[c] = ++cord;

    int upc = 0;
    for (auto to : g[c]) {
        if (to != p) {
            // printf("c=%d to=%d toVis=%d\n", c,to,ord[to]!=0);
            if (!ord[to]) {
                tarjan(to, c);
                low[c] = min(low[c], low[to]);
            }
            else {
                low[c] = min(low[c], ord[to]);
                cycEdge.emplace(min(c, to), max(c, to));
                // printf("back %d %d\n", c,to);
                // cycEdgeCnt++;
            }

            upc += low[to] < ord[c];
        }
    }
    bad |= upc >= 2;
}

void solve() {
    memset(clr, -1, sizeof clr);
    for (auto i = 1; i <= N; i++) {
        if (clr[i] == -1)
            dfs(i, 0);
    }
    if (bad) return void(cout << "NO\n");

    // tarj
    for (auto i = 1; i <= N; i++) {
        if (!ord[i]) {
            cycEdge.clear();
            tarjan(i, -1);
            bad |= (int)cycEdge.size() >= 2;
        }
    }
    if (bad) return void(cout << "NO\n");

    cout << "YES\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        // Input
        cin >> N >> M;
        // set<pii> use;
        for (auto i = 0; i < M; i++) {
            int a, b; cin >> a >> b;
            g[a].push_back(b);
            g[b].push_back(a);

            // if (a > b) swap(a, b);
            // assert(!use.count({a, b}));
            // use.emplace(a, b);
        }
        
        solve();

        // Reset
        cord = 0;
        bad = false;
        for (auto i = 1; i <= N; i++) {
            g[i].clear();
            ord[i] = 0;
            low[i] = 0;
        }
    }
}
