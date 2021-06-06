// ./problem-3-balanced-subsets.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

const ll MOD = 1e9 + 7;
const int MN = 152;
int N,
    psum[MN][MN];
int dp[MN][MN][MN][2][2];
string grid[MN];

// helpers
inline bool ok(int r, int a, int b) {
    return psum[r][b] - psum[r][a-1] == b-a+1;
}
// check intersection
inline bool I(int a, int b, int c, int d) {
    return max(a, c) <= min(b, d);
}

ll dpsum[MN][MN][2][2];
inline void inc(int a, int c, int b, int d, bool a1, bool a2, int v) {
    if (a>c || b>d) return;
    dpsum[a][b][a1][a2] += v;
    dpsum[c+1][b][a1][a2] -= v;
    dpsum[a][d+1][a1][a2] -= v;
    dpsum[c+1][d+1][a1][a2] += v;
}
void apply(int idx) {
    for (auto i = 1; i <= N; i++) {
        for (auto j = 1; j <= N; j++) {
            for (auto k = 0; k <= 1; k++) {
                for (auto l = 0; l <= 1; l++) {
                    ll &c = dpsum[i][j][k][l];
                    c += dpsum[i-1][j][k][l] + dpsum[i][j-1][k][l] - dpsum[i-1][j-1][k][l];
                    c %= MOD;
                    if (c < 0) c += MOD;
                    dp[idx][i][j][k][l] = c;
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (auto i = 0; i < N; i++) {
        string s; cin >> s;
        for (auto j = 0; j < N; j++) {
            psum[i+1][j+1] = psum[i+1][j] + (s[j] == 'G');
        }
        grid[i+1] = ' ' + s;
    }

    ll ans = 0;
    for (auto i = 1; i <= N; i++) {
        memset(dpsum, 0, sizeof dpsum);

        for (auto j = 1; j <= N; j++) {
            for (auto k = j; k <= N; k++) {
                if (ok(i, j, k)) {
                    dp[i][j][k][0][0]++;

                    int gl = j, gr = k;
                    if (i < N) {
                        while (gl > 1 && grid[i+1][gl-1] == 'G') gl--;
                        while (gr < N && grid[i+1][gr+1] == 'G') gr++;
                    }

                    for (auto lB = 0; lB <= 1; lB++) {
                        for (auto rB = 0; rB <= 1; rB++) {
                            int &c = dp[i][j][k][lB][rB];
                            if (c >= MOD) c -= MOD;

                            if (i < N) {
                                // both strictly outside
                                if (!lB && !rB) {
                                    inc(gl, j-1, k+1, gr, 0, 0, c);
                                }
                                if (!lB) { // only left is strictly outside
                                    inc(gl, j-1, j, k-1, 0, 1, c); // right inside
                                    inc(gl, j-1, k, k, 0, rB, c); // right equal
                                }
                                if (!rB) { // only right is strictly outside
                                    inc(j+1, k, k+1, gr, 1, 0, c); // left inside
                                    inc(j, j, k+1, gr, lB, 0, c); // left equal
                                }
                                // both inside
                                inc(j, j, k, k, lB, rB, c); // on border
                                inc(j+1, k-1, j+1, k-1, 1, 1, c); // strictly inside
                                inc(j, j, j, k-1, lB, 1, c); // right strictly inside
                                inc(j+1, k, k, k, 1, rB, c); // left strictly inside
                            }

                            ans += c;
                        }
                    }
                }
            }
        }

        if (i < N)
            apply(i+1);
    }
    ans %= MOD;
    cout << ans << '\n';

    return 0;
}

