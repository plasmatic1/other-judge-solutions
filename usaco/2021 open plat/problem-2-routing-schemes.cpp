// ./problem-2-routing-schemes.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

const ll MOD = 1e9+7;
ll fpow(ll x, ll y) {
    if (!y) return 1LL;
    return fpow(x*x%MOD, y/2) * ((y & 1) ? x : 1LL) % MOD;
}
ll inv(ll x) { return fpow(x, MOD-2); }
const int MN = 101;

// precalc factorials and inverses
ll f[MN], Inv[MN];

int N, M, K;
bool S[MN], R[MN], adj[MN][MN]; // adj only includes down edges
vector<pii> down;
vector<int> Ss;

// for K=2
// Observation: there are only 2 ending points we ever try to get the DP sum of, so we can just run the DP "in reverse" and count contribution from each source instead
ll dpac[MN][MN][4], dpca[MN][MN][4]; // ending at (a,c) or (c,a) | 0->No special situation 1->first node has been used once by second pointer already 2->second node has been used once by first pointer already 3->Just started, allowed to overlap (otherwise is also a 0-state)
vector<tuple<int, int, int, ll>> rg[MN][MN][4];

void solve() {
    cin >> N >> K;
    string tmp; cin >> tmp;
    for (auto i = 0; i < N; i++) {
        if (tmp[i] == 'S') {
            Ss.push_back(i);
            S[i] = true;
        }
        else if (tmp[i] == 'R')
            R[i] = true;
    }
    M = 0;
    for (auto i = 0; i < N; i++) {
        cin >> tmp;
        for (auto j = 0; j < N; j++) {
            if (tmp[j] == '1') {
                if (i > j) down.emplace_back(i, j);
                else adj[i][j] = true;
            }
        }
    }

    // get ideg ("initial degree"), counting sinks as edges 'to the end' and only upwards edges
    // also get ians -> ans assuming K=0
    vector<int> ideg(N);
    ll ians = 1;
    for (auto i = 0; i < N; i++) {
        ideg[i] = R[i];
        for (auto j = 0; j < N; j++) ideg[i] += adj[i][j];
        ians = ians * f[ideg[i]] % MOD;
    }

    if (K == 0)
        cout << ians << '\n';
    else if (K == 1) {
        auto [a, b] = down[0];

        ll ans = 0;
        for (auto i = 0; i < (int)Ss.size(); i++) {
            int st = Ss[i];
            vector<ll> dp(N);

            dp[st] = 1;
            for (auto j = st; j < a; j++)
                for (auto to = 0; to < N; to++)
                    if (adj[j][to])
                        dp[to] = (dp[to] + dp[j] * inv(ideg[j])) % MOD;
            ans = (ans + ians * dp[a]) % MOD;
        }
        cout << ans << '\n';
    }
    else {
        auto [a, b] = down[0];
        auto [c, d] = down[1];

        // compute contribution reverse graph
        for (auto i = 0; i < N; i++) {
            for (auto j = 0; j < N; j++) {
                for (auto k = 0; k < N; k++) {
                    for (auto l = 0; l < 4; l++) {
                        if ((j >= i || k >= i) && l != 3) continue;

                        int degj = ideg[j] - (l == 1), degk = ideg[k] - (l == 2);
                        ll costj = Inv[degj], costk = Inv[degk];
                        // one to i
                        if (adj[j][i] && degj > 0 && i > j) {
                            int newl = j == k ? 2 : (l == 1 ? 0 : l);
                            if (newl == 3 && (min(i, k) == max(j, k) || max(i, k) > max(j, k))) newl = 0;
                            rg[i][k][newl].emplace_back(j, k, l, costj);
                        }
                        if (adj[k][i] && degk > 0 && i > k) {
                            int newl = j == k ? 1 : (l == 2 ? 0 : l);
                            if (newl == 3 && (min(j, i) == max(j, k) || max(j, i) > max(j, k))) newl = 0;
                            rg[j][i][newl].emplace_back(j, k, l, costk);
                        }
                        // both to i
                        if (j != k && adj[j][i] && adj[k][i] && degj > 0 && degk > 0 && i > j && i > k)
                            rg[i][i][0].emplace_back(j, k, l, costj * costk % MOD);
                    }
                }
            }
        }

        auto run = [&] (ll dp[MN][MN][4]) {
            for (auto i = N-1; i >= 0; i--)
                for (auto j = N-1; j >= 0; j--)
                    for (auto k = 0; k < 4; k++)
                        for (auto [ii, jj, kk, cost] : rg[i][j][k])
                            dp[ii][jj][kk] = (dp[ii][jj][kk] + dp[i][j][k] * cost) % MOD;
        };

        // get contribution using graph
        for (auto i = 0; i < 4; i++) {
            dpac[a][c][i] = 1;
            dpca[c][a][i] = 1;
        }
        run(dpac);
        run(dpca);

        // get ans
        ll ans = 0;
        for (auto i = 0; i < (int)Ss.size(); i++) {
            for (auto j = 0; j < (int)Ss.size(); j++) {
                if (i == j) {
                    // memset(dp, 0, sizeof dp); dp[Ss[i]][b][3] = 1; run(); (count from A,C)
                    ans = (ans + dpac[Ss[i]][b][3]) % MOD;

                    // memset(dp, 0, sizeof dp); dp[Ss[i]][d][3] = 1; run(); (count from C,A)
                    ans = (ans + dpca[Ss[i]][d][3]) % MOD;
                }
                else {
                    // memset(dp, 0, sizeof dp); dp[Ss[i]][Ss[j]][3] = 1; run(); (count from A,C)
                    ans = (ans + dpac[Ss[i]][Ss[j]][3]) % MOD;
                }
            }
        }
        ans = ans * ians % MOD;

        cout << ans << '\n';
    }

    // reset
    memset(dpac, 0, sizeof dpac);
    memset(dpca, 0, sizeof dpca);
    memset(adj, 0, sizeof adj);
    Ss.clear();
    down.clear();
    for (auto i = 0; i < N; i++) {
        S[i] = R[i] = false;
        for (auto j = 0; j < N; j++)
            for (auto k = 0; k < 4; k++)
                rg[i][j][k].clear();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    f[0] = 1;
    for (auto i = 1; i < MN; i++) {
        f[i] = f[i-1] * i % MOD;
        Inv[i] = inv(i);
    }

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}
