// ./bobs-fibonacci-sequence.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

/*
X'(b) + Y'(a-b*(a//b)) = gcdv
X'b + Y'a - Y'b*(a//b) = gcdv
Y'a + (X'-Y'*(a//b))b = gcdv
*/

ll extgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    ll tx, ty, res = extgcd(b, a%b, tx, ty);
    x = ty;
    y = (tx - ty * (a / b));

    return res;
}

const int MN = 1e5 + 1;
ll mod, F0, F1,
   F[MN];

ll fix(ll x, ll mod) { x %= mod; if (x < 0) x += mod; return x; }

ll fpow(ll x, ll y, ll mod) {
    if (!y) return 1LL;
    return fpow(x * x % mod, y >> 1, mod) * ((y & 1) ? x : 1LL) % mod;
}
// ll inv(ll x, ll mod) { return fpow(x, mod - 2, mod); }
ll inv(ll a, ll mod) {
    ll x, y; 
    if (extgcd(a, mod, x, y) != 1) return 0;
    return fix(x, mod);
}

vector<int> pf;

vector<int> getVector(ll a, ll b) {
    vector<int> cur;
    for (auto f : pf) {
        cur.push_back(fix(a * inv(b, f), f));
    }
    return cur;
}
ll single(ll a, ll b, ll f) {
    return fix(a * inv(b, f), f);
}

// map<vector<int>, int> ratios;
map<int, vector<int>> ratios[20];
int SZ;

ll getf(ll k, ll F0, ll F1) {
    return (F0 * F[k-2] + F1 * F[k-1]) % mod;
}

void solve() {
    cin >> F0 >> F1;

    // ll x, y, gv = extgcd(F0, F1, x, y);
    // if (mod % gv) {
    //     cout << "-1\n";
    //     return;
    // }
    // x *= mod/gv;
    // y *= mod/gv;
    // gv = mod;

    if (F0 % mod == 0) cout << "0\n";
    else if (F1 % mod == 0) cout << "1\n";
    else {
        int ans = INF;
        for (auto i = SZ-1; i >= 0; i--) {
            int x = pf[i];
            if (F0 % x != 0 && F1 % x != 0) {
                ll r = single(-F0, F1, x);
                for (auto candidate : ratios[i][r]) {
                    if (getf(candidate+1, F0, F1) == 0)
                        ans = min(ans, candidate+1);
                }
                break;
            }
        }

        cout << (ans == INF ? -1 : ans) << '\n';
    }
}

void solvesmall() {
    cin >> F0 >> F1;

    F[0] = F0;
    F[1] = F1;
    for (auto i = 2; i <= mod; i++) {
        F[i] = (F[i-1] + F[i-2]) % mod;
    }
    for (auto i = 0; i <= mod; i++) {
        if (F[i]%mod==0) {
            cout << i << '\n';
            return;
        }
    }
    cout << "-1\n";
}

void dopf(int k) {
    for (auto i = 2; i * i <= k; i++) {
        if (k % i == 0) {
            int c = 1;
            while (k % i == 0) {
                k /= i;
                c *= i;
            }
            pf.push_back(c);
        }
    }
    if (k > 1)
        pf.push_back(k);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T; cin >> T >> mod;
    dopf(mod);
    SZ = pf.size();

    F[0] = F[1] = 1;
    for (auto i = 2; i <= mod; i++) {
        F[i] = (F[i-1] + F[i-2]) % mod;
    }

    for (auto i = 1; i <= mod; i++) {
        vector<int> r = getVector(F[i], F[i-1]);
        // printf("i=%d Fi=%lld Fi-1=%lld\n", i,F[i],F[i-1]);
        // for (auto x : r) printf("%d ", x);
        // printf("\n");
        // if (!ratios.count(r)) ratios[r] = i;
        for (auto j = 0; j < SZ; j++)
            ratios[j][single(F[i], F[i-1], pf[j])].push_back(i);
    }

    // bool ip = isp(mod);
    while (T--) {
        // if (mod > 1000) solve();
        // else solvesmall();
        solve();
    }

    return 0;
}

