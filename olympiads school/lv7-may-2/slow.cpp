// ./bobs-spanning-tree.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

const ll MOD = 998244353;
ll fix(ll &&x) { x %= MOD; if (x < 0) x += MOD; return x; }
ll fix(ll &x) { x %= MOD; if (x < 0) x += MOD; return x; }
ll fpow(ll x, ll y, ll mod = MOD) {
    if (!y) return 1LL;
    return fpow(x * x % mod, y >> 1, mod) * ((y & 1) ? x : 1LL) % mod;
}
ll inv(ll x, ll mod = MOD) { return fpow(x, mod - 2, mod); }
// N choose R
vector<ll> fact, invf;
void init_nchooser(int MN) {
    fact.resize(MN + 1); invf.resize(MN + 1);
    fact[0] = 1LL;
    for (int i = 1; i <= MN; i++) fact[i] = fix(fact[i - 1] * i);
    invf[MN] = inv(fact[MN]);
    for (auto i = MN-1; i >= 0; i--) invf[i] = fix(invf[i + 1] * (i + 1));
}
ll choose(ll N, ll K) { return fix(fact[N] * fix(invf[K] * invf[N - K])); }
ll permute(ll N, ll K) { return fix(fact[N] * invf[N - K]); }

const int MN = 2e6+1;
int N;
vector<int> g[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    init_nchooser(N);
    for (auto i = 0; i < N-1; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
    }
    bool prop1 = true, prop2 = false;
    for (auto i = 1; i <= N; i++) {
        prop1 &= g[i].size() <= 2;
        prop2 |= g[i].size() == N-1;
    }

    if (prop2) {
        ll ans = 0, p2 = 1;
        for (auto i = 0; i < N; i++) {
            int left = N-i-1;
            ll comb = choose(N-1, i) * fpow(N, max(0, left-1));

            // ll comb = combNotLeaf + combLeaf;
            // if (comb >= MOD) comb -= MOD;
            ans += fix(p2 * i) * comb;
            fix(ans);
            p2 *= 2;
        }
        cout << ans << '\n';
    }
    else assert(0);

    return 0;
}

