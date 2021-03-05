// ./bobs-group-photo.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 5001;
int N,
    H[MN], dp[MN], idxOf[MN], psum[MN][MN];

// valmin, valmax, l, r
int rq(int v, int w, int l, int r) {
    ll res = psum[w][r];
    if (v) res -= psum[v-1][r];
    if (l) res -= psum[w][l-1];
    if (v && l) res += psum[v-1][l-1];
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (auto i = 1; i <= N; i++) {
        cin >> H[i];
        idxOf[H[i]] = i;
        psum[H[i]][i]++;
    }
    for (auto i = 1; i <= N; i++)
        for (auto j = 1; j <= N; j++)
            psum[i][j] += psum[i-1][j] + psum[i][j-1] - psum[i-1][j-1];

    memset(dp, 0x3f, sizeof dp);
    dp[0] = 0;
    for (auto i = 0; i < N; i++) {
        int cost = 0;
        for (auto j = i+1; j <= N; j++) {
            cost += rq(1, i, idxOf[j], N) + rq(i+1, j-1, 1, idxOf[j]);
            dp[j] = min(dp[j], dp[i] + cost);
        }
    }

    cout << dp[N] << '\n';

    return 0;
}

