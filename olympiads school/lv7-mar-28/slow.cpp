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
ld P[MN], dp[MN][2]; // dp course #, #(switch), node #

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
    int msub = 1<<N;
    ld ans = 1e9;
    for (auto i = 0; i < msub; i++) {
        if (__builtin_popcount(i) > M) continue;
        memset(dp, 0, sizeof dp);
        for (auto j = N-1; j >= 0; j--) {
            if ((i >> j) & 1) {
                dp[j][0] = P[j+1] * (dp[j+1][1] + dis[A[j]][B[j+1]]) + (1-P[j+1]) * (dp[j+1][0] + dis[A[j]][A[j+1]]);
                dp[j][1] = P[j+1] * (dp[j+1][1] + dis[B[j]][B[j+1]]) + (1-P[j+1]) * (dp[j+1][0] + dis[B[j]][A[j+1]]);
            }
            else {
                dp[j][0] = dp[j+1][0] + dis[A[j]][A[j+1]];
                dp[j][1] = dp[j+1][0] + dis[B[j]][A[j+1]];
            }
        }
        // if (dp[0][0]==0){
        //     printf("i=%d\n",i);
        // }
        // if (dp[0][0]<ans){
        //     printf("alt=%Lf sw=%d\n", dp[0][0],i);
        // }
        ans = min(ans, dp[0][0]);
    }

    // cout << fixed << setprecision(2) << ans << '\n';
    printf("%.2Lf\n", ans);

    return 0;
}

