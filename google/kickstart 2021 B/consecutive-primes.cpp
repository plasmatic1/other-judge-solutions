// ./consecutive-primes.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

bool isp(ll k) {
    for (ll i = 2; i * i <= k; i++) {
        if (k % i == 0)
            return false;
    }
    return true;
}

ll Z;

void solve() {
    cin >> Z;

    ll st = max(0LL, (ll)sqrt(Z)+1000);

    vector<ll> pr;
    while (st > 0) {
        if (isp(st)) {
            pr.push_back(st);
        }

        int sz = pr.size();
        if (sz >= 2 && pr[sz-1] * pr[sz-2] <= Z) {
            cout << (pr[sz-1]*pr[sz-2]) << '\n';
            return;
        }

        st--;
    }
    assert(0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T, tc = 1;
    cin >> T;
    while (T--) {
        // Input
        
        cout << "Case #" << tc << ": ";
        solve();
        tc++;

        // Reset
    }
}
