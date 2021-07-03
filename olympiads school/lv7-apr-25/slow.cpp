// ./bobs-permutation.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

// const int MN = 1001;
const int MN = 15;
int N,
    A[MN], W[MN];
vector<int> g[MN];
ll dp[1<<MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (auto i = 1; i <= N; i++) {
        cin >> A[i-1]; // i must come after A[i]
        if (A[i-1])
            g[A[i-1]-1].push_back(i-1);
    }
    for (auto i = 1; i <= N; i++) {
        cin >> W[i-1];
    }

    int msub = 1<<N;
    fill(dp, dp+msub, -LLINF); dp[0] = 0;
    for (auto i = 0; i < msub; i++) {
        if (dp[i] == -LLINF) continue;

        ll cur = __builtin_popcount(i)+1;
        for (auto j = 0; j < N; j++) {
            if (!((i >> j) & 1)) {
                int nmsk = i | (1 << j); bool ok = true;
                for (auto to : g[j])
                    ok &= !((nmsk >> to) & 1);
                if (ok)
                    dp[nmsk] = max(dp[nmsk], dp[i] + cur*W[j]);
            }
        }
    }

    cout << (dp[msub-1] == -LLINF ? -1 : dp[msub-1]) << '\n';

    return 0;
}

