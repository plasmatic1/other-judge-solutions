// ./moons-and-umbrellas.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int N, X, Y;
    string s;
    cin >> X >> Y >> s;
    N = s.length();

    vector<vector<int>> dp(N, vector<int>(2, INF));
    if (s[0] == 'C' || s[0] == '?') dp[0][0] = 0;
    if (s[0] == 'J' || s[0] == '?') dp[0][1] = 0;
    for (auto i = 1; i < N; i++) {
        if (s[i] == 'C' || s[i] == '?') {
            dp[i][0] = min(dp[i-1][0], dp[i-1][1] + Y);
        }
        if (s[i] == 'J' || s[i] == '?') {
            dp[i][1] = min(dp[i-1][1], dp[i-1][0] + X);
        }
    }

    cout << min(dp[N-1][0], dp[N-1][1]) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for (int caseno = 1; caseno <= T; caseno++) {
        // Input
       
        cout << "Case #" << caseno << ": ";
        solve();

        // Reset
    }
}

