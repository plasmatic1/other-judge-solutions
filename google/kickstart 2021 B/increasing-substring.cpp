// ./increasing-substring1.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 2e5 + 1;

void solve() {
    int N; string s; cin >> N >> s;
    for (auto i = 0; i < N; i++) {
        char pre = s[i];
        int j = i-1;
        for (; j >= 0; j--) {
            if (s[j] >= pre) break;
            pre = s[j];
        }
        cout << (i-j) << ' ';
    }
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

