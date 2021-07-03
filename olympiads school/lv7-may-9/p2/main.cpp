#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

const int DIR[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
const int MN = 2001;
int R, C, K, Q, r0, c0,
    QR[MN], QC[MN], dis[MN][MN][4];
bool block[MN][MN];

bool in(int l, int r, int k) { return l <= k && k <= r; }

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> R >> C >> K >> Q;
    for (auto i = 0; i < K; i++) {
        int r, c; cin >> r >> c;
        block[r][c] = true;
    }
    cin >> r0 >> c0;

    memset(dis, 0x3f, sizeof dis);
    using T = tuple<int, int, int>;
    deque<T> q;
    for (auto i = 0; i < 4; i++) {
        dis[r0][c0][i] = 0;
        q.emplace_back(r0, c0, i);
    }
    while (!q.empty()) {
        auto [r, c, d] = q.front(); q.pop_front();
        // if (d==0)
        // printf("vis r=%d c=%d d=%d dis=%d\n", r,c,d,dis[r][c][d]);
        auto push = [&] (int r0, int c0, int d0, int w) {
            if (!in(1, R, r0) || !in(1, C, c0) || block[r0][c0]) return;
            int alt = dis[r][c][d]+w;
            // printf("push nxt r=%d c=%d d=%d alt=%d PREDIS=%d\n", r0,c0,d0,alt,dis[r0][c0][d0]);
            if (alt < dis[r0][c0][d0]) {
                // if (!d)
                dis[r0][c0][d0] = alt;
                if (w) q.emplace_back(r0, c0, d0);
                else q.emplace_front(r0, c0, d0);
            }
            // else
            //     assert(dis[r0][c0][d0]<=alt);
        };

        push(r+DIR[d][0], c+DIR[d][1], d, 0);
        push(r, c, (d+3)%4, 1);
        push(r, c, (d+1)%4, 1);
    }

    for (auto i = 0; i < Q; i++) {
        int r, c; cin >> r >> c;
        int ans = min({dis[r][c][0], dis[r][c][1], dis[r][c][2], dis[r][c][3]});
        cout << (ans == INF ? -1 : ans) << '\n';
    }

    return 0;
}
