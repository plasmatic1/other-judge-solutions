// p5.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

int sign(int k) { return (k > 0) - (k < 0); }

// const int MN = 51, TH = MN*MN;
const int MN = 51, TH = 10000;
// const int MN = 51, TH = 3;
int N, M, Z,
    to[MN], rto[MN];

void _solve() {
    cin >> N >> M >> Z;
    for (auto i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        to[a] = b;
        rto[b] = a;
    }

    map<int, int> cnt;
    for (auto i = 0; i < Z; i++) {
        for (auto j = Z; j < N; j++) {
            if (to[i] == j) // lose instantly
                cnt[-1]++;
            else {
                auto check = [&] (int a, int b) {
                    int res = 0;
                    for (auto c = a; c != b; c = rto[c]) res++;
                    for (auto c = b; c != a; c = rto[c]) res--;
                    return sign(res);
                };

                int ans = check(i, j) + check(to[i], j);
                cnt[sign(ans)]++;
            }
        }
    }
    cout << cnt[1] << ' ' << cnt[-1] << ' ' << cnt[0] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    int tc = 1;
    while (t--) {
        cout << "Case #" << (tc++) << ": ";
        _solve();
    }

    return 0;
}
