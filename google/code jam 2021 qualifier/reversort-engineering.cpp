// ./reversort-engineering.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int N, C;
    cin >> N >> C;

    vector<int> cost(N+1, 1);
    C -= N-1;
    for (auto i = N-1; i >= 1; i--) {
        int gain = max(0, min(N-i, C));
        C -= gain;
        cost[i] += gain;
    }
    vector<int> ans(N+1); iota(ans.begin(), ans.end(), 0);
    if (C != 0) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    for (auto i = N-1; i >= 1; i--) {
        reverse(ans.begin()+i, ans.begin()+i+cost[i]);
    }
    for (auto i = 1; i <= N; i++) cout << ans[i] << ' ';
    cout << '\n';
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

