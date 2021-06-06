// ./prime-time.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 95, MV = 1e5+1;
int N;
ll P[MN], C[MN];

void solve() {
    cin >> N;
    ll tsum = 0;
    for (auto i = 0; i < N; i++) {
        cin >> P[i] >> C[i];
        tsum += P[i] * C[i];
    }

    ll maxRed = 0;
    for (auto i = 0; i < N; i++) {
        ll c = tsum;
        while (c > 0) {
            maxRed += P[i];
            c /= P[i];
        }
    }

    for (auto i = tsum; i >= max(1LL, tsum-maxRed-1); i--) {
        ll c = i, rsum = tsum;
        bool bad = false;
        for (auto j = 0; j < N; j++) {
            int cnt = 0;
            while (c % P[j] == 0) {
                c /= P[j];
                cnt++;
            }
            if (cnt > C[j]) {
                bad = true;
                break;
            }

            rsum -= cnt * P[j];
        }

        if (bad) continue;
        // printf("i=%lld c=%lld tsum=%lld rsum=%lld\n", i,c,tsum,rsum);
        // fflush(stdout);

        if (c == 1 && rsum == i) {
            cout << i << '\n';
            return;
        }
    }
    cout << "0\n";
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

