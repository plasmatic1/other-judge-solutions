// ./bobs-snowball.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 2e5 + 10;
int N, Q;
ll X[MN], pos[MN], dif[MN], change[MN], mxpos[MN], mnpos[MN], divide[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    for (auto i = 1; i <= N; i++)
        cin >> X[i];

    ll mn = 0, mx = 0;
    for (auto i = 1; i <= Q; i++) {
        cin >> pos[i];
        change[i] = pos[i];
        pos[i] += pos[i-1];

        mx = max(mx, pos[i]);
        mn = min(mn, pos[i]);
        dif[i] = mx - mn;
        mxpos[i] = mx;
        mnpos[i] = mn;
    }

    // on right
    // mx > k+mn
    // mx-mn > k
    //
    // on left
    // mn < -k+mx
    // mn-mx < -k
    // mx-mn > k
    for (auto i = 1; i < N; i++) {
        int idx = upper_bound(dif, dif+Q+1, X[i+1] - X[i]) - dif;
        if (idx <= Q) {
            if (change[idx] < 0)
                divide[i] = X[i] + mxpos[idx];
            else
                divide[i] = X[i+1] + mnpos[idx];
        }
        else divide[i] = LLINF;
    }
    for (auto i = 1; i <= N; i++) {
        ll l = X[i]+mn, r = X[i]+mx;
        if (i < N && divide[i] != LLINF) r = min(r, divide[i]);
        if (i > 1 && divide[i-1] != LLINF) l = max(l, divide[i-1]);
        cout << (r-l) << '\n';
    }


    return 0;
}
