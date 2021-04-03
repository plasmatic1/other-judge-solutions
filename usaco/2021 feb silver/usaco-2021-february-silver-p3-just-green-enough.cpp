// ./usaco-2021-february-silver-p3-just-green-enough.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 501;
int N, 
    val[MN][MN], cmin[MN][MN][MN]; // (r1, r2, col)

int tri(int k) { return k*(k-1)/2; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (auto i = 0; i < N; i++)
        for (auto j = 0; j < N; j++)
            cin >> val[i][j];

    memset(cmin, 0x3f, sizeof cmin);
    for (auto i = 0; i < N; i++) { // col
        for (auto j = 0; j < N; j++) { // row
            int cur = INF;
            for (auto k = j; k < N; k++) {
                cur = min(cur, val[k][i]);
                cmin[j][k][i] = cur;
            }
        }
    }
    ll ans = 0;
    for (auto i = 0; i < N; i++) {
        for (auto j = i; j < N; j++) {
            int* ccmin = cmin[i][j];
            // count #>=100
            int pre = -1;
            for (auto k = 0; k < N; k++) {
                if (ccmin[k] < 100) {
                    ans += tri(k-pre);
                    pre = k;
                }
            }
            ans += tri(N-pre);
            // count #>100
            pre = -1;
            for (auto k = 0; k < N; k++) {
                if (ccmin[k] <= 100) {
                    ans -= tri(k-pre);
                    pre = k;
                }
            }
            ans -= tri(N-pre);
        }
    }
    cout << ans << '\n';

    return 0;
}

