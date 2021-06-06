// ./hacked-exam.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }

const int MN = 3, MQ = 41 + 10;
int N, Q,
    S[MN];
string A[MN];

ll dp1[MQ][MQ], dp2[MQ][MQ][MQ]; //, dp3[MQ][MQ][MQ][MQ];

ll solve(string A[MN], int S[MN]) {
    for (auto i = 0; i < N; i++)
        if (S[i] < 0)
            return 0LL;

    int Q = A[0].length();
    // printf("solve Q=%d\n", Q);

    if (N == 1) {
        memset(dp1, 0, sizeof dp1);
        dp1[0][0] = 1;
        for (auto i = 0; i < Q; i++) {
            for (auto j = 0; j <= S[0]; j++) {
                dp1[i+1][j+1] += dp1[i][j];
                dp1[i+1][j] += dp1[i][j];
            }
        }

        return dp1[Q][S[0]];
    }
    else if (N == 2) {
        memset(dp2, 0, sizeof dp2);
        dp2[0][0][0] = 1;
        for (auto i = 0; i < Q; i++) {
            for (auto j = 0; j <= S[0]; j++) {
                for (auto k = 0; k <= S[1]; k++) {
                    // if (dp2[i][j][k])
                    //     printf("i=%d j=%d k=%d dpv=%lld\n", i,j,k,dp2[i][j][k]);
                    int t1 = A[0][i] == 'T', t2 = A[1][i] == 'T';
                    dp2[i+1][j+t1][k+t2] += dp2[i][j][k];
                    dp2[i+1][j+1-t1][k+1-t2] += dp2[i][j][k];
                }
            }
        }

        // printf("res=%lld\n", dp2[Q][S[0]][S[1]]);
        return dp2[Q][S[0]][S[1]];
    }
    else
        assert(0);
}

void solve() {
    cin >> N >> Q;
    for (auto i = 0; i < N; i++) {
        cin >> A[i] >> S[i];
    }

    string ans;
    ll tot = solve(A, S), ev = 0;
    for (auto i = 0; i < Q; i++) {
        string tmpA[MN]; copy(A, A+N, tmpA);
        int tmpS[MN]; copy(S, S+N, tmpS);

        for (auto j = 0; j < N; j++) {
            if (A[j][i] == 'T')
                tmpS[j]--;
            tmpA[j].erase(tmpA[j].begin()+i);
        }
        ll tc = solve(tmpA, tmpS), fc = tot-tc;

        if (tc >= fc) {
            ev += tc;
            ans += 'T';
        }
        else {
            ev += fc;
            ans += 'F';
        }
    }

    ll _n = ev, _d = tot, _g = gcd(_n, _d);
    // printf("n=%lld d=%lld\n", _n,_d);fflush(stdout);
    _n /= _g;
    _d /= _g;
    cout << ans << ' ' << _n << '/' << _d << '\n';
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

