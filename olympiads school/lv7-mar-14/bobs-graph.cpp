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

const int MN = 5e5 + 1;
int N, M;
vector<int> g[MN], auxg[MN];
// ll dp[MN][3]; // 0->all the ways to select from n's subtree, 1->just total comb
// ll dpT[MN];

// toursC
using pii = pair<int, int>;
// tarjan
set<pii> bridge;
int cord = 0,
    ord[MN], low[MN];
void dfs1(int c, int p) {
    ord[c] = low[c] = ++cord;
    for (int to : g[c]) {
        if (to != p) {
            if (!ord[to]) {
                dfs1(to, c);
                low[c] = min(low[c], low[to]);
            }
            else
                low[c] = min(low[c], ord[to]);

            if (low[to] > ord[c]) {
                bridge.emplace(c, to);
                bridge.emplace(to, c);
            }
        }
    }
}
int comp[MN];
void dfs2(int c, int cno) {
    if (comp[c]) return;
    comp[c] = cno;
    for (int to : g[c]) {
        if (bridge.count({c, to})) continue;
        dfs2(to, cno);
    }
}

// tree DP
ll dp[MN][2];

ll c2(ll k) {
    static const ll D2 = inv(2);
    return (k*(k-1)%MOD)*D2%MOD;
}

void dfs(int c, int p, vector<int> g[MN]) {
    int ch = 0;
    ll prod = 1;
    for (auto to : g[c]) {
        if (to != p) {
            dfs(to, c, g);
            ch++;

            // subprod = subprod * (dpT[to] + dp[to][2]) % MOD;
            prod = prod * (dp[to][0] + dp[to][1]) % MOD;
        }
    }
    if (ch) {
        // single/no choice
        dp[c][0] = prod;
        // printf("tot after 1chain=%lld\n", prod);
        // double
        dp[c][0] += prod * c2(ch);
        dp[c][0] %= MOD;

        ll st1 = 1;
        for (auto to : g[c]) {
            if (to != p) {
                st1 = st1*dp[to][0]%MOD;
            }
        }
        for (auto to : g[c]) {
            if (to != p) {
                ll rem = st1 * inv(dp[to][0]) % MOD;
                dp[c][1] += ((dp[to][0]+dp[to][1])%MOD) * rem % MOD;
                dp[c][1] %= MOD;
            }
        }
    }
    else
        dp[c][0] = 1;

    // printf("c=%d p=%d TOT=%lld SEL=%lld\n", c,p,dp[c][0],dp[c][1]);
}

void solve() {
    cin >> N >> M;
    for (auto i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs1(1, -1);
    int cno = 1;
    for (auto i = 1; i <= N; i++) {
        if (!comp[i]) {
            dfs2(i, cno);
            cno++;
        }
    }
    for (auto i = 1; i <= N; i++) {
        for (auto to : g[i]) {
            int a = comp[i], b = comp[to];
            if (a != b)
                auxg[a].push_back(b);
        }
    }
    for (auto i = 1; i <= N; i++) {
        auxg[i].resize(unique(auxg[i].begin(), auxg[i].end()) - auxg[i].begin());
    }

    dfs(1, -1, auxg);
    cout << dp[1][0] << '\n';

    // reset stuff
    for (auto i = 1; i <= N; i++) {
        g[i].clear();
        auxg[i].clear();
        // dp[i][0] = dp[i][1] = dp[i][2] = dpT[i] = 0;
        dp[i][0] = dp[i][1] = 0;
        comp[i] = low[i] = ord[i] = 0;
    }
    cord = 0;
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

