// p5.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

int sign(int k) { return (k > 0) - (k < 0); }

// const int MN = 51, TH = MN*MN;
const int MN = 51, TH = 10000;
// const int MN = 51, TH = 3;
int N, M, Z,
    win[MN][MN]; // win - RBOY=i, ZER0=j
vector<int> g[MN], rg[MN];

void bfs(int s, int dis[MN]) {
    fill(dis, dis+N, INF);
    queue<int> q;
    q.push(s); dis[s] = 0;
    while (!q.empty()) {
        int c = q.front(); q.pop();
        for (auto to : rg[c]) {
            if (dis[to] == INF) {
                dis[to] = dis[c]+1;
                q.push(to);
            }
        }
    }
}

int dp[TH][MN][MN];
bool done[TH][MN][MN];
int solve(int left, int c, int d) { // dp[RBOY,ZERO]= 0->lose 1->win | INVERT=!x
    if (left == 0) return 0;
    int &ret = dp[left][c][d];
    if (done[left][c][d]) return ret;
    done[left][c][d] = true;
    ret = -INF;
    for (auto to : g[c]) {
        // if (c==3&&d==2) {
        //     printf("FOUNDTO=%d\n", to);
        // }
        if (to != d) {
            ret = max(ret, win[c][d] - solve(left-1, d, to)); // c=to, d=d
        }
    }
    return ret;
}

void _solve() {
    cin >> N >> M >> Z;
    for (auto i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        rg[b].push_back(a);
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

    memset(done, false, sizeof done);
    map<int, int> cnt;
    for (auto i = 0; i < Z; i++) {
        for (auto j = Z; j < N; j++) {
            int q = solve(TH-1, i, j);
            // printf("i=%d j=%d q=%d\n",i,j,q);
            if (abs(q)<=N) q=0;
            cnt[sign(q)]++;
        }
    }
    // for (auto i = 0; i < N; i++) {
    //     for (auto j = 0; j < N; j++) {
    //         if (i==j)continue;
    //         printf("i=%d j=%d W=%d\n",i,j,solve(i,j));
    //     }
    // }
    // cout << wc << ' ' << lc << ' ' << tc << '\n';
    cout << cnt[1] << ' ' << cnt[-1] << ' ' << cnt[0] << '\n';

    // clear
    for (auto i = 0; i < N; i++) {
        g[i].clear();
        rg[i].clear();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    int tc = 1;
    while (t--) {
        cout << "Case #" << (tc++) << ": ";
        _solve();
    }

    return 0;
}
