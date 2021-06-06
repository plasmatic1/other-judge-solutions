// p5.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

int sign(int k) { return (k > 0) - (k < 0); }

const int MN = 51;
int N, M, Z,
    win[MN][MN]; // win - RBOY=i, ZER0=j
vector<int> g[MN];

void bfs(int s, int dis[MN]) {
    fill(dis, dis+N, INF);
    queue<int> q;
    q.push(s); dis[s] = 0;
    while (!q.empty()) {
        int c = q.front(); q.pop();
        for (auto to : g[c]) {
            if (dis[to] == INF) {
                dis[to] = dis[c]+1;
                q.push(to);
            }
        }
    }
}

int dp[MN][MN];
int solve(int c, int d) { // dp[RBOY,ZERO]= 0->lose 1->win | INVERT=!x
    int &ret = dp[c][d];
    if (ret != -1) return ret;
    ret = 0;
    for (auto to : g[c]) {
        // if (c==3&&d==2) {
        //     printf("FOUNDTO=%d\n", to);
        // }
        if (to != d) {
            ret = max(ret, 1-solve(d, to)); // c=to, d=d
        }
    }
    return ret;
}

void solve() {
    cin >> N >> M >> Z;
    for (auto i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
    }

    {
        int d1[MN], d2[MN];
        for (auto i = 0; i < N; i++) {
            for (auto j = 0; j < N; j++) {
                if (i != j) {
                    bfs(i, d1);
                    bfs(j, d2);
                    int cnt = 0;
                    for (auto k = 0; k < N; k++) {
                        if (d1[k]<d2[k]) cnt++;
                        if (d1[k]>d2[k]) cnt--;
                    }
                    win[i][j] = sign(cnt);
                }
            }
        }
    }

    memset(dp, -1, sizeof dp);
    int lc = 0, tc = 0, wc = 0;
    for (auto i = 0; i < Z; i++) {
        for (auto j = Z; j < N; j++) {
            int q = solve(i, j);
            if (q == 0) lc++;
            if (q == 1) wc++;
        }
    }
    // for (auto i = 0; i < N; i++) {
    //     for (auto j = 0; j < N; j++) {
    //         if (i==j)continue;
    //         printf("i=%d j=%d W=%d\n",i,j,solve(i,j));
    //     }
    // }
    cout << wc << ' ' << lc << ' ' << tc << '\n';

    // clear
    for (auto i = 0; i < N; i++) {
        g[i].clear();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    int tc = 1;
    while (t--) {
        cout << "Case #" << (tc++) << ": ";
        solve();
    }

    return 0;
}
