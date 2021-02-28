// ./bobs-lights.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MM = 20, MSUB = 1<<MM;
const ll MOD = 998244353;
ll fpow(ll x, ll y) {
    if (!y) return 1;
    return fpow((x*x)%MOD, y/2) * (y&1 ? x : 1) % MOD;
}
ll inv(ll x) { return fpow(x, MOD-2); }
ll fact[MM], invf[MM];
ll C(int n, int k) { return fact[n]*(invf[k]*invf[n-k]%MOD)%MOD; }

int N, M,
    A[MM];

ll tcnt[MSUB];

bool subsets(int in, int out) {
    return (in & out) == in;
}

ll kcoeff[MSUB];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    fact[0] = 1;
    for (int i = 1; i < MM; i++) fact[i] = (fact[i-1]*i)%MOD;
    invf[MM-1] = inv(fact[MM-1]);
    for (int i = MM-2; i >= 0; i--) invf[i] = (invf[i+1]*(i+1))%MOD;

    cin >> N >> M;
    for (int i = 0; i < M; i++) cin >> A[i];

    int msub = 1<<M;

    // tcnt[i] = # of #s that divide all of subset
    for (auto i = 0; i < msub; i++) {
        ll lcm = 1;
        for (auto j = 0; j < M; j++) {
            if ((i>>j)&1) {
                lcm = (lcm * A[j]) / __gcd(lcm, (ll)A[j]);
                if (lcm > N) break;
            }
        }
        tcnt[i] = N/lcm;
    }

    // ll sum = 0; 
    // for (auto i = 0; i < msub; i++) {
    //     for (auto j = 0; j < msub; j++) {
    //         if (__builtin_popcount(j) % 4 == 0 && subsets(j, i)) {
    //             int pc = __builtin_popcount(j);
    //             for (auto k = 0; k < msub; k++) {
    //                 if (subsets(j, k) && subsets(k, i)) { // j supersets i
    //                     if ((__builtin_popcount(k) ^ pc) & 1) sum -= tcnt[k];
    //                     else sum += tcnt[k];
    //                 }
    //             }
    //         }
    //     }
    // }
    
    // observations:
    // we only care about j whose popcount(j)%4==0
    // - so coeff for all popcount(k)%2==1 is negative, and positive if it was even instead

    ll sum = 0;
    for (auto i = 0; i < msub; i++) {
        int pc = __builtin_popcount(i);
        for (int j = 0; j <= pc; j += 4)
            kcoeff[i] += C(pc, j);
        if (pc & 1) kcoeff[i] *= -1;
    }
    for (auto i = 0; i < msub; i++) {
        int pc = __builtin_popcount(i);
        ll single = kcoeff[i] * tcnt[i] % MOD;
        sum = (sum + single * fpow(2, M-pc)) % MOD;
    }

    if (sum<0) sum += MOD;
    cout << (sum * inv(fpow(2, M)) % MOD) << '\n';

    return 0;
}

