#include <bits/stdc++.h>
#include <random>
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

using T = tuple<int, int, int>;

const int MN = 10, MM = 1001;
int N, M, R;
T vil[MN];
pii mon[MM];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> R;

    int mnx = INF, mny = INF, mxx = -INF, mxy = -INF;
    for (auto i = 0; i < N; i++) {
        auto &[x, y, r] = vil[i];
        cin >> x >> y >> r;
        // printf("x=%d y=%d r=%d\n", x,y,r); fflush(stdout);

        mnx = min(mnx, x);
        mny = min(mny, y);
        mxx = max(mxx, x);
        mxy = max(mxy, y);
    }
    for (auto i = 0; i < M; i++) {
        auto &[x, y] = mon[i];
        cin >> x >> y;

        mnx = min(mnx, x);
        mny = min(mny, y);
        mxx = max(mxx, x);
        mxy = max(mxy, y);
    }

    // printf("XR=%d-%d YR=%d-%d\n", mnx, mxx,mny,mxy);
    mt19937 mt(26022021);
    uniform_real_distribution<double> disx((double)mnx, (double)mxx), disy((double)mny, (double)mxy);

    int ts = 1e7/(N+M), ans = 0;
    // int ts = 1e2/(N+M), ans = 0;
    while (ts--) {
        if (ans == M) break;
        double xx = disx(mt), yy = disy(mt);
        bool ok = true;
        int cur = 0;

        for (auto i = 0; i < N; i++) {
            auto [x, y, r] = vil[i];
            double dx = x-xx, dy = y-yy, dissq = dx*dx+dy*dy;
            ok &= dissq >= (R+r)*(R+r);
        }
        for (auto i = 0; i < M; i++) {
            auto [x, y] = mon[i];
            double dx = x-xx, dy = y-yy, dissq = dx*dx+dy*dy;
            cur += dissq <= R*R;
        }

        // printf("xx=%lf yy=%lf ok=%d cur=%d\n", xx,yy,ok,cur);
        ans = max(ans, ok*cur);
    }

    cout << ans << '\n';

    return 0;
}
