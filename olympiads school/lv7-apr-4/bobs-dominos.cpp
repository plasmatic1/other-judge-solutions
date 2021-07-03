// ./bobs-dominos.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const ll MOD = 1e9 + 7;
const int MN = 17, MSUB = 1 << MN;
int N, M,
    A[MN+1][MN+1], dpF[MN+1][MN+1][MSUB], dpB[MN+1][MN+1][MSUB];

inline int kth(int v, int bit) { return (v >> bit) & 1; }
inline int mkth(int v, int bit) { return v ^ (1 << bit); }
inline int pushv(int msk, int v) { return ((msk << 1) | v) & ((1 << M) - 1); }
// #define kth(v, bit) (((v) >> (bit)) & 1)
// #define mkth(v, bit) ((v) ^ (1 << (bit)))
// #define pushv(msk, v) ((((msk) << 1) | (v)) & ((1 << (M)) - 1))

void run(int dp[MN+1][MN+1][MSUB]) {
    auto push = [&] (int i, int j, int k, int v) {
        dp[i][j][k] = (dp[i][j][k] + v) % MOD;
    };

    int msub = 1<<M;
    dp[0][0][msub-2] = 1;
    if (M >= 2 && !A[0][0] && !A[0][1]) dp[0][1][msub-1] = 1;

    for (auto i = 0; i < N; i++) {
        for (auto j = 0; j < M; j++) {
            int nxti = i + (j == M-1), nxtj = j == M-1 ? 0 : j+1;
            for (auto msk = 0; msk < msub; msk++) {
                int cur = dp[i][j][msk];
                // add vertical domino
                if (((j < M-1 && i > 0) || j == M-1) && kth(msk, M-1) == 0 && !A[nxti][nxtj] && !A[nxti-1][nxtj]) {
                    push(nxti, nxtj, pushv(msk, 1), cur);
                }
                // add horizontal domino
                if (j < M-2 && !A[i][j+1] && !A[i][j+2]) {
                    push(i, j+2, pushv(pushv(msk, 1), 1), cur);
                }
                else if (j == M-1 && M >= 2 && !A[i+1][0] && !A[i+1][1]) {
                    push(i+1, 1, pushv(pushv(msk, 1), 1), cur);
                }
                // do nothing
                push(nxti, nxtj, pushv(msk, 0), cur);
            }
        }
    }

    // for (auto i = 0; i < N; i++) {
    //     for (auto j = 0; j < M; j++) {
    //         for (auto k = 0; k < msub; k++) {
    //             printf("i=%d j=%d k=%d DP=%d\n", i,j,k,dp[i][j][k]);
    //         }
    //     }
    // }
}

// SOS utils
ll F[MSUB], B[MSUB];
inline void SOS(int f[MSUB], ll F[MSUB], int b[MSUB], ll B[MSUB]) { // also known as zeta transform but wHaTeVeR
    int msub = 1<<M;
    copy(f, f+msub, F);
    copy(b, b+msub, B);
    for (auto i = 0; i < M; i++) {
        int b = 1 << i;
        for (auto j = 1 << i; j < msub; j = (j + 1) | b) {
            F[j] += F[j ^ b];
            B[j] += B[j ^ b];
        }
    }
    for (auto j = 0; j < msub; j++) {
        F[j] %= MOD;
        B[j] %= MOD;
    }
}
int getall(int f[MSUB]) {
    int ans = 0;
    for (auto i = 0; i < 1<<M; i++) ans = (ans + f[i]) % MOD;
    return ans;
}

// precompute fmsk and bmsk for values
int fmskFor[MN][MSUB], bmskFor[MN][MSUB];
void FBMSK_init() {
    int msub = 1<<M;
    for (auto j = 0; j < M; j++) {
        for (auto msk = 0; msk < msub; msk++) {
            int fmsk = msub-1, bmsk = msub-1;
            for (auto k = 0; k < j; k++) {
                if (kth(msk, k)) {
                    fmsk = mkth(fmsk, j-1 - k);
                    bmsk = mkth(bmsk, M-j-1 + k);
                }
            }
            for (auto k = j+1; k < M; k++) {
                if (kth(msk, k)) {
                    fmsk = mkth(fmsk, j + M-k-1);
                    bmsk = mkth(bmsk, k-j-1);
                }
            }

            fmskFor[j][msk] = fmsk;
            bmskFor[j][msk] = bmsk;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (auto i = 0; i < N; i++)
        for (auto j = 0; j < M; j++)
            cin >> A[i][j];

    // edge case
    if (N == 1 && M == 1) {
        cout << !A[0][0] << '\n';
        return 0;
    }

    auto flipXY = [&] () {
        for (auto i = 0; i < N; i++)
            reverse(A[i], A[i]+M);
        for (auto i = 0; i < M; i++)
            for (auto j = 0; j < N/2; j++)
                swap(A[j][i], A[N-j-1][i]);
    };
    run(dpF);
    flipXY();
    run(dpB);
    flipXY(); // so we can check Aij correctly

    // for (auto i = 0; i < N; i++) {
    //     for (auto j = 0; j < M; j++) {
    //         printf("i=%d j=%d f=%d b=%d\n",i,j,getall(dpF,i,j),getall(dpB,i,j));
    //     }
    // }

    FBMSK_init();

    int msub = 1<<M;
    for (auto i = 0; i < N; i++) {
        for (auto j = 0; j < M; j++) {
            if (A[i][j]) cout << "0 ";
            else {
                // setup SOS DPs
                int i1 = i - (j == 0), j1 = (j - 1 + M) % M;
                int numSq = i * M + j + 1, sqRemIdx = N*M - numSq - 1, i2 = sqRemIdx / M, j2 = sqRemIdx % M;

                // edge cases
                if (i1 < 0) {
                    cout << getall(dpB[i2][j2]) << ' ';
                    continue;
                }
                else if (sqRemIdx < 0) {
                    cout << getall(dpF[i1][j1]) << ' ';
                    continue;
                }

                SOS(dpF[i1][j1], F, dpB[i2][j2], B);

                // printf("i=%d j=%d preI=%d preJ=%d numSq=%d sqRemIdx=%d i2=%d j2=%d\n", i,j,i-(j==0),(j-1+M)%M,numSq,sqRemIdx,i2,j2);

                // precompute allowed masks
                int allow = msub-1;
                allow = mkth(allow, j);
                for (auto k = 0; k < M; k++) {
                    if (A[i][k]) {
                        allow = mkth(allow, k);
                        continue;
                    }
                    if (k < j && A[i+1][k]) {
                        allow = mkth(allow, k);
                        continue;
                    }
                    if (k > j && i > 0 && A[i-1][k]) {
                        allow = mkth(allow, k);
                        continue;
                    }
                }
                
                // do the sos o la la
                ll ans = 0;
                for (auto msk = allow; ; msk = (msk - 1) & allow) {
                    // printf("msk=%d\n", msk);
                    ans = (ans + ll(F[fmskFor[j][msk]]) * B[bmskFor[j][msk]]) % MOD;
                    if (msk == 0) break;
                }
                cout << ans << ' ';
            }
        }
        cout << '\n';
    }

    return 0;
}

