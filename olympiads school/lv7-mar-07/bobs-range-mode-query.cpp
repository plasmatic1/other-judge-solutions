// ./bobs-range-mode-query.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 5e5 + 1;
int N, Q,
    fre[MN], A[MN];
vector<vector<int>> cnt;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    cnt.assign(N+1, vector<int>(N+1));
    for (auto i = 1; i <= N; i++)
        cin >> A[i];
    for (auto i = 1; i <= N; i++) {
        fill(fre, fre+N+1, 0);
        int mf = 0;
        for (auto j = i; j <= N; j++) {
            mf = max(mf, ++fre[A[j]]);
            if ((i & 1) == (j & 1)) {
                cnt[i][j] = fre[(j+i)/2] == mf;
                // printf("%d-%d is\n", i,j);
            }
        }
    }
    for (auto i = 1; i <= N; i++)
        for (auto j = 1; j <= N; j++)
            cnt[i][j] += cnt[i-1][j] + cnt[i][j-1] - cnt[i-1][j-1];
    while (Q--) {
        int l, r; cin >> l >> r;
        int res = cnt[r][r] - cnt[l-1][r] - cnt[r][l-1] + cnt[l-1][l-1];
        cout << res << '\n';
    }

    return 0;
}

