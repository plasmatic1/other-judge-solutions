// ./cookie-jars.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 1001;
int N, C, Q,
    cnt[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> C >> Q;
    fill(cnt+1, cnt+N+1, C);
    while (Q--) {
        int x; cin >> x;
        for (auto i = x; i <= N; i += x)
            if (cnt[i] > 0) cnt[i]--;
    }
    int sum = 0;
    for (auto i = 1; i <= N; i++) sum += cnt[i];
    cout << sum << '\n';

    return 0;
}

