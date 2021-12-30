// ./longest-progression.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 3e5 + 1;
int N,
    A[MN], dp[MN][3];

void solve() {
    cin >> N;
    for (auto i = 0; i < N; i++) {
        cin >> A[i];
        dp[i][0] = dp[i][1] = dp[i][2] = 0;
    }

    int ans = 2;
    dp[0][0] = 1;
    dp[1][0] = 2;
    for (auto i = 2; i < N; i++) {
        for (auto j = 0; j < 3; j++) {
            if (j == 1) continue;
            dp[i][j] = 2;
            if (A[i]-A[i-1] == A[i-1]-A[i-2]) dp[i][j] = dp[i-1][j]+1;
        }

        if (i >= 3 && A[i]-A[i-2] == 2*(A[i-2]-A[i-3])) dp[i][1] = max(dp[i][1], dp[i-2][0]+2);
        if (i >= 3 && 2*(A[i]-A[i-1]) == A[i-1]-A[i-3]) dp[i][2] = max(dp[i][2], dp[i-1][1]+1);
        if ((A[i]-A[i-2]) % 2 == 0) dp[i][1] = max(dp[i][1], 3);

        ans = max({ans, dp[i][0]+1, dp[i][1], dp[i][2]});
    }
    cout << min(N, ans) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for (int caseno = 1; caseno <= T; caseno++) {
        // Input
       
        // printf("tc\n");
        cout << "Case #" << caseno << ": ";
        solve();

        // Reset
    }
}

