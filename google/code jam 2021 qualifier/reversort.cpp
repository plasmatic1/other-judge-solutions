// ./reversort.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 101;
int N,
    A[MN];

void solve() {
    cin >> N;
    for (auto i = 0; i < N; i++) cin >> A[i];
    int ans = 0;
    for (auto i = 0; i < N-1; i++) {
        int posOf = -1;
        for (auto j = i; j < N; j++) {
            if (A[j] == i+1) {
                posOf = j;
                break;
            }
        }
        ans += posOf-i+1;
        reverse(A+i, A+posOf+1);
    }
    cout << ans << '\n';
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

