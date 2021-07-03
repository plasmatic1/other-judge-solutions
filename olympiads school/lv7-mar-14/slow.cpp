// ./bobs-graph.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const ll MOD = 998244353;
ll fpow(ll x, ll y, ll mod = MOD) {
    if (!y) return 1LL;
    return fpow(x * x % mod, y >> 1, mod) * ((y & 1) ? x : 1LL) % mod;
}
ll inv(ll x, ll mod = MOD) { return fpow(x, mod - 2, mod); }

const int MN = 10+1;
int N, M;
vector<int> g[MN];
bool sel[MN][MN], cpick[MN][MN];

bool cantake = true;
bool dfs(int c, int p, int en, bool mark) {
    if (c == en) return true;
    bool f = false;
    for (auto to : g[c]) {
        if (to != p) {
            bool ff = dfs(to, c, en, mark);
            if (ff) {
                if (cpick[c][to]) {
                    cantake = false;
                }
                if (mark) {
                    cpick[c][to] = cpick[to][c] = true;
                }
                f = true;
            }
        }
    }
    return f;
}

void solve() {
    cin >> N >> M;
    assert(M == N-1);
    for (auto i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
        sel[a][b] = sel[b][a] = true;
    }

    vector<pair<int, int>> es;
    for (auto i = 1; i <= N; i++)
        for (auto j = i+1; j <= N; j++)
            es.emplace_back(i, j);

    int sz = es.size(), msub = 1<<sz, ans = 0;
    for (auto i = 0; i < msub; i++) {
        memset(cpick, false, sizeof cpick);

        bool good = true;
        for (auto j = 0; j < sz; j++) {
            if ((i >> j) & 1) {
                auto [a, b] = es[j];
                if (sel[a][b]) {
                    good = false;
                    break;
                }
                cantake = true;
                dfs(a, -1, b, false);
                if (!cantake) {
                    good = false;
                    break;
                }
                cantake = true;
                dfs(a, -1, b, true);
            }
        }
        ans += good;
    }

    cout << ans << '\n';

    // reset stuff
    memset(sel, 0, sizeof sel);
    for (auto i = 1; i <= N; i++) {
        g[i].clear();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T; cin >> T;
    while (T--) {
        // printf("================tc\n");
        solve();
    }

    return 0;
}

