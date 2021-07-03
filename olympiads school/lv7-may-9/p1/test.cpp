#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

const int MN = 1e5 + 1, LG = 18;

int N,
    dp[161051];

void decode(int st, int A[5]) {
    for (auto i = 0; i < N; i++) {
        A[i] = st % 11;
        st /= 11;
    }
}
int encode(int A[5]) {
    int st = 0;
    for (auto i = N-1; i >= 0; i--)
        st = (st*11)+A[i];
    return st;
}

int A[5];
int solve(int st) {
    if (st == 0) return 0;
    if (dp[st] != -1) return dp[st];

    int res = INF;
    int cur[5], tmp[5]; decode(st, cur);

    // printf("solve st=%d STATE=",st);
    // for (auto i = 0; i < N; i++) printf("%d,", cur[i]);
    // printf("\n");
    // fflush(stdout);

    for (auto i = 0; i < N; i++) {
        for (auto j = i; j < N; j++) {
            bool ok;

            ok = true;
            copy(cur, cur+5, tmp);
            for (auto k = i; k <= j; k++) {
                ok &= tmp[k] > 0;
                tmp[k]--;
            }
            if (ok && encode(tmp) != st) {
                // printf("st=%d child=%d\n", st,encode(tmp));
                res = min(res, solve(encode(tmp)));
            }

            ok = true;
            copy(cur, cur+5, tmp);
            for (auto k = i; k <= j; k++) {
                if (k & 1) {
                    ok &= tmp[k] > 0;
                    tmp[k]--;
                }
            }
            if (ok && encode(tmp) != st) {
                // printf("st=%d child=%d\n", st,encode(tmp));
                res = min(res, solve(encode(tmp)));
            }

            ok = true;
            copy(cur, cur+5, tmp);
            for (auto k = i; k <= j; k++) {
                if (!(k & 1)) {
                    ok &= tmp[k] > 0;
                    tmp[k]--;
                }
            }
            if (ok && encode(tmp) != st) {
                // printf("st=%d child=%d\n", st,encode(tmp));
                res = min(res, solve(encode(tmp)));
            }
        }
    }
    return dp[st] = res+1;
}

void _case() {
    cin >> N;

    assert(N <= 5);
    for (auto i = 0; i < N; i++) {
        cin >> A[i];
    }

    memset(dp, -1, sizeof dp);
    cout << solve(encode(A)) << '\n';
    cout.flush();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int _t; cin >> _t;
    while (_t--) {
        // printf("case\n"); fflush(stdout);
        _case();
    }

    return 0;
}
