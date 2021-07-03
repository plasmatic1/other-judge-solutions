// ./bobs-combination-number.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using ld = long double;
using pii = pair<int, int>;

// can i cheese this?
const ll MOD = 1e9+7;
ll fpow(ll x, ll y) {
    if (!y) return 1LL;
    return fpow(x*x%MOD, y/2) * ((y & 1) ? x : 1LL) % MOD;
}
ll inv(ll x) { return fpow(x, MOD-2); }

const int MN = 1e6+1;
int N, K;
ld flog[MN];
ll f[MN], invf[MN];

ll C(int n, int k) { return f[n] * (invf[k] * invf[n-k] % MOD) % MOD; }
ld Cl(int n, int k) { return flog[n] - flog[k] - flog[n-k]; }
set<pii> use;
priority_queue<tuple<ld, int, int>> pq;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;
    f[0] = 1; flog[0] = 0;
    for (auto i = 1; i <= N; i++) {
        flog[i] = flog[i-1] + log(i);
        f[i] = f[i-1] * i % MOD;
    }
    invf[N] = inv(f[N]);
    for (auto i = N-1; i >= 0; i--)
        invf[i] = invf[i+1] * (i+1) % MOD;

    ll ans = 0;
    use.emplace(N, N/2);
    pq.emplace(Cl(N, N/2), N, N/2);
    while (!pq.empty()) {
        auto [lg, n, k] = pq.top(); pq.pop();
        ans = (ans + C(n, k)) % MOD;
        if (--K == 0) break;

        auto push = [&] (int n0, int k0) {
            if (!use.count({n0, k0})) {
                use.emplace(n0, k0);
                pq.emplace(Cl(n0, k0), n0, k0);
            }
        };
        if (k > 0) push(n, k-1);
        if (k < n) push(n, k+1);
        if (n > 0 && k <= n-1) push(n-1, k);
    }

    cout << ans << '\n';

    return 0;
}

