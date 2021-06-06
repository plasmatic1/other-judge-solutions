// ./coins.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, X; cin >> N >> X;
    int ans = 0;
    for (auto i = 0; i < N; i++) {
        int c, v; cin >> c >> v;
        ans = max(ans, min(X, c) * v);
    }
    cout << ans << '\n';

    return 0;
}

