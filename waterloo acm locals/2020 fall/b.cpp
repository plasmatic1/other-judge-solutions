// b.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long; using ull = unsigned long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<long long, long long>;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

mt19937 mt(time(NULL));
ll N, K;
ld P;

ld P_somebody(int sz) {
    return 1 - pow(1 - P, sz);
}

ld E_block(int blocksize) {
    if (!blocksize) return 0;
    return 1 + blocksize * P_somebody(blocksize);
}

#define TEST

// tropical FUCK YOU
const int MK = 41;
const ld linf = numeric_limits<ld>::infinity();
ld tr[MK][MK], res[MK];

void M(ld a[MK][MK], ld b[MK][MK], ld to[MK][MK]) {
    static ld tmp[MK][MK];
    for (auto i = 0; i < K; i++) {
        for (auto j = 0; j < K; j++) {
            tmp[i][j] = linf;
            for (auto k = 0; k < K; k++)
                tmp[i][j] = min(tmp[i][j], a[i][k] + b[k][j]);
        }
    }
    for (auto i = 0; i < K; i++)
        for (auto j = 0; j < K; j++)
            to[i][j] = tmp[i][j];
}
void M2(ld a[MK][MK], ld b[MK], ld to[MK]) {
    static ld tmp[MK];
    for (auto i = 0; i < K; i++) {
        tmp[i] = linf;
        for (auto j = 0; j < K; j++)
            tmp[i] = min(tmp[i], a[i][j] + b[j]);
    }
    copy(tmp, tmp + K, to);
}

void solve() {
#ifdef TEST
    N = 1000;
    // K = uniform_int_distribution<int>(1, N)(mt);
    K = 100;
    // P = uniform_real_distribution<ld>(0.01, 0.99)(mt);
    P = 0.1;
#else
    cin >> (N) >> (K) >> (P);
#endif
    K = min(K, N);
    K = min(K, (ll)MK);

    cout << fixed << setprecision(9);
    ld ans;
    for (auto i = 0; i < K; i++)
        for (auto j = 0; j < K; j++)
            tr[i][j] = linf;
    for (auto i = 0; i < K; i++) {
        for (auto j = 0; j <= i; j++)
            tr[i][j] = E_block(i - j + 1);
        if (i < K)
            tr[i - 1][i] = 0;
    }

    fill(res, res + K, linf);
    res[0] = 0;
    // cout<<"res=["; for(int __i=0; __i<(K); __i++)cout<<res[__i]<<", "; cout<<"], ";cout << endl; // db A:K:res
    for (ll i = 0; i < 32; i++) {
        if ((N >> i) & 1) {
            M2(tr, res, res);
            // cout<<"res=["; for(int __i=0; __i<(K); __i++)cout<<res[__i]<<", "; cout<<"], ";cout << endl; // db A:K:res
        }
        M(tr, tr, tr);
    }

    ans = res[0];

#ifdef TEST
    vector<ld> dp(N + 1, numeric_limits<ld>::infinity());
    vector<int> par(N + 1);
    dp[0] = 0;
    for (auto i = 1; i <= N; i++) {
        for (auto j = i-1; j >= 0; j--) {
            if (i - j <= K) {
                ld alt = dp[j] + E_block(i - j);
                if (alt < dp[i]) {
                    dp[i] = alt;
                    par[i] = j;
                }
            }
            else
                break;
        }
    }
    vector<int> sz;
    for (int c = N; c; c = par[c])
        sz.push_back(c - par[c]);
    sort(sz.begin(), sz.end());

    if (dp[N] > ans) {
        cout << ("skip") << '\n';
        return;
    }
    cout<<"N="<<(N)<<", "; cout<<"K="<<(K)<<", "; cout<<"P="<<(P)<<", "; cout << endl; // db N,K,P
    cout<<"dp[N]="<<(dp[N])<<", "; cout<<"ans="<<(ans)<<", "; cout << endl; // db dp[N],ans
    cout << "sz=["; for (auto __x:sz)cout<<__x<<", "; cout<<"], "; cout << endl; // db I:sz
    cout << (N) << ' ' << (K) << ' ' << (P) << '\n';
    cout << (dp[N]) << '\n';
    cout.flush();
    assert(abs(dp[N] - ans) < 1e-4);
#else
    ans = min(ans, ld(N));
    cout << (ans) << '\n';
#endif
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifdef TEST
    int c = 5;
    while (c--) solve();
#else
    solve();
#endif
    return 0;
}

