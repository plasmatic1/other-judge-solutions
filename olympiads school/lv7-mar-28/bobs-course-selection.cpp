// ./bobs-course-selection.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
using ld = long double;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const ld LINF = 1e9;
const int MN = 2001, MV = 301;
int N, M, V, E,
    dis[MV][MV], A[MN], B[MN];
ld P[MN], dp[MN][MN][2]; // dp course #, #(switch), whether an application was filed

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // read input
    cin >> N >> M >> V >> E;
    for (auto i = 1; i <= N; i++) cin >> A[i];
    for (auto i = 1; i <= N; i++) cin >> B[i];
    for (auto i = 1; i <= N; i++) cin >> P[i];
    memset(dis, 0x3f, sizeof dis);
    for (auto i = 1; i <= V; i++) dis[i][i] = 0, dis[0][i] = 0;
    for (auto i = 0; i < E; i++) {
        int u, v, w; cin >> u >> v >> w;
        dis[u][v] = min(dis[u][v], w);
        dis[v][u] = min(dis[v][u], w);
    }
    for (auto k = 1; k <= V; k++)
        for (auto i = 1; i <= V; i++)
            for (auto j = 1; j <= V; j++)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);

    // run DP
    for (auto i = 0; i <= M; i++) dp[N][i][0] = dp[N][i][1] = LINF;
    dp[N][0][0] = dp[N][1][1] = 0;
    for (auto i = N-1; i >= 1; i--) {
        for (auto j = 0; j <= M; j++) {
            dp[i][j][0] = dp[i][j][1] = LINF;

            auto push = [&] (int k, ld v) {
                dp[i][j][k] = min(dp[i][j][k], v);
            };

            // no switch
            push(0, dp[i+1][j][0] + dis[A[i]][A[i+1]]);
            push(0, dp[i+1][j][1] + P[i+1] * dis[A[i]][B[i+1]] + (1-P[i+1]) * dis[A[i]][A[i+1]]);
            // switch
            if (j > 0) {
                push(1, dp[i+1][j-1][0] + P[i] * dis[B[i]][A[i+1]] + (1-P[i]) * dis[A[i]][A[i+1]]);
                push(1, dp[i+1][j-1][1] + 
                        P[i] * P[i+1] * dis[B[i]][B[i+1]] + 
                        P[i] * (1-P[i+1]) * dis[B[i]][A[i+1]] +
                        (1-P[i]) * P[i+1] * dis[A[i]][B[i+1]] +
                        (1-P[i]) * (1-P[i+1]) * dis[A[i]][A[i+1]]);
            }
        }
    }

    // get ans
    ld ans = LINF;
    for (auto i = 0; i <= M; i++)
        ans = min({ans, dp[1][i][0], dp[1][i][1]});
    cout << fixed << setprecision(2) << ans << '\n';

    return 0;
}

