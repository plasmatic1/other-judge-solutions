// ./usaco-2021-february-bronze-p3-clockwise-fence.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

void solve() {
    int x = 0, y = 0;
    string s; cin >> s;
    int N = s.length();

    pair<pii, int> mx{{0, 0}, -1};
    for (auto i = 0; i < N; i++) {
        char c = s[i];
        if (c == 'N') y += 1;
        else if (c == 'E') x += 1;
        else if (c == 'S') y -= 1;
        else if (c == 'W') x -= 1;
        mx = max(mx, pair<pii, int>{{x, y}, i});
    }

    // printf("BP=%d %d INS=%d\n", mx.first.first,mx.first.second,mx.second);
    int preIns = mx.second, nxtIns = mx.second+1;
    auto fix = [&] (int &k) {
        k %= N;
        if (k < 0) k += N;
    };
    fix(preIns); fix(nxtIns);
    // printf("preIns=%d nxtIns=%d %c %c\n", preIns,nxtIns,s[preIns],s[nxtIns]);

    if (s[nxtIns] == 'W') cout << "CCW\n";
    else cout << "CW\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T; cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}

