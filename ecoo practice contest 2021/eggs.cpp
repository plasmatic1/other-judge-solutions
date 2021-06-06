// ./eggs.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const ll MOD = 1e9 + 7;
const int MN = 1001, DIR[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int N, M, K,
    freeTime[MN][MN]; // first time where the loc. is free from bullies
ll dp[MN][MN];
map<char, int> cmap;

bool inbound(int x, int y) {
    return 1 <= x && x <= N && 1 <= y && y <= M;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cmap['D'] = 0;
    cmap['U'] = 1;
    cmap['R'] = 2;
    cmap['L'] = 3;

    memset(freeTime, -0x3f, sizeof freeTime);
    cin >> N >> M >> K;
    for (auto i = 0; i < K; i++) {
        int x, y, s; char d; cin >> x >> y >> s >> d;

        int dx = DIR[cmap[d]][0], dy = DIR[cmap[d]][1], ctime = 0;
        while (inbound(x, y)) {
            int nx = x + dx * s, ny = y + dy * s;

            for (int cx = x, cy = y; (cx != nx || cy != ny) && inbound(cx, cy); cx += dx, cy += dy) {
                freeTime[cx][cy] = max(freeTime[cx][cy], ctime+1);
            }

            x = nx;
            y = ny;
            ctime++;
        }
    }

    // for (auto i = 1; i <= N; i++) {
    //     for (auto j = 1; j <= M; j++) {
    //         // printf("i=%d j=%d freeTime=%d\n", i,j,freeTime[i][j]);
    //         printf("%d ", freeTime[i][j]);
    //     }
    //     printf("\n");
    // }

    dp[0][1] = 1LL;
    for (auto i = 1; i <= N; i++) {
        for (auto j = 1; j <= M; j++) {
            if (i+j-2 > freeTime[i][j]) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
                dp[i][j] %= MOD;
            }
        }
    }
    cout << dp[N][M] << '\n';

    return 0;
}

