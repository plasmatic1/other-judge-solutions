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
void tarjan(int c, int p) {
    ord[c] = low[c] = ++cord;

    int upc = 0;
    for (auto to : g[c]) {
        if (to != p) {
            if (!ord[to]) {
                tarjan(to, c);
                low[c] = min(low[c], low[to]);
            }
            else
                low[c] = min(low[c], ord[to]);

            upc += low[to] < ord[c];
        }
    }
    bad |= upc >= 2;
}

namespace CUSTOMS {
    vector<vector<pii>> cs;

    int cord = 0, ord[MN], low[MN];
    stack<pii> stk;
    void dfs(int c, int p) {
        ord[c] = low[c] = ++cord;
        for (auto to : g[c]) {
            if (to != p) {
                if (!ord[to]) {
                    stk.emplace(c, to);
                    dfs(to, c);
                    low[c] = min(low[c], low[to]);
                    
                    // we got an articulation point bois :sunglasses:
                    if (low[to] >= ord[c]) {
                        cs.push_back(vector<pii>());
                        int u, v;
                        do {
                            auto _e = stk.top(); stk.pop();
                            tie(u, v) = _e;
                            cs.back().emplace_back(u, v);
                        } while (u != c || v != to);
                    }
                }
                else if (ord[to] < ord[c]) {
                    stk.emplace(c, to);
                    low[c] = min(low[c], ord[to]);
                }
            }
        }
    }

    void reset() {
        cs.clear();
        while (!stk.empty()) stk.pop();
        cord = 0;
        memset(ord, 0, sizeof ord);
        memset(low, 0, sizeof low);
    }
};

void solve() {
    if (N > 1000) {
        while (true);
    }

    memset(clr, -1, sizeof clr);
    for (auto i = 1; i <= N; i++) {
        if (clr[i] == -1)
            dfs(i, 0);
    }
    if (bad) return void(cout << "NO\n");

    // tarj
    for (auto i = 1; i <= N; i++) {
        if (!ord[i]) {
            tarjan(i, -1);
        }
    }
    if (bad) return void(cout << "NO\n");

    // checking ;)
    for (auto i = 1; i <= N; i++) {
        if (!CUSTOMS::ord[i]) {
            CUSTOMS::dfs(i, -1);
        }
    }
    map<int, int> cycFre;
    for (auto &es : CUSTOMS::cs) {
        set<int> nodes;
        for (auto [a, b] : es) {
            nodes.insert(a);
            nodes.insert(b);
        }
        if (es.size() >= nodes.size()) {
            // printf("CYCCOMP\n");
            for (auto n : nodes)  {
                cycFre[n]++;
                // printf("n=%d\n", n);
            }
        }
    }
    for (auto [_, v] : cycFre)
        if (v >= 2)
            return void(cout << "NO\n");

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
        for (auto i = 0; i < M; i++) {
            int a, b; cin >> a >> b;
            g[a].push_back(b);
            g[b].push_back(a);
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
        CUSTOMS::reset();
    }
}
