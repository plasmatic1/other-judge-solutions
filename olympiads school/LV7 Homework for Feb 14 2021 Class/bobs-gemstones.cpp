// ./bobs-gemstones.yml
// bruce is this pro-moses problem :-)

#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

struct vec {
    ll m[4];
    vec() { fill(m, m + 4, -LLINF); }
};
struct matrix {
    ll m[4][4];
    matrix(bool id) {
        for (auto i = 0; i < 4; i++) fill(m[i], m[i] + 4, -LLINF);
        if (id)
            for (auto i = 0; i < 4; i++)
                m[i][i] = 0;
    }
    matrix() : matrix(0) {}
    matrix operator*(const matrix o) const {
        matrix res(0); 
        for (auto i = 0; i < 4; i++)
            for (auto j = 0; j < 4; j++)
                for (auto k = 0; k < 4; k++)
                    res.m[i][j] = max(res.m[i][j], m[i][k] + o.m[k][j]);
        return res;
    }
    vec operator*(const vec o) const {
        vec res; 
        for (auto i = 0; i < 4; i++)
            for (auto j = 0; j < 4; j++)
                res.m[i] = max(res.m[i], m[i][j] + o.m[j]);
        return res;
    }
    void pr() {
        printf("M=[ ");
        for (auto i = 0; i < 4; i++) {
            for (auto j = 0; j < 4; j++) printf("%lld ", m[i][j]);
            if (i==3) printf("]\n");
            else printf("\n    ");
        }
    }
};

const int MN = 40001, S = 65536;
int N, Q,
    A[MN];

matrix seg[S*2];
matrix mat(int v) {
    matrix res;
    for (int i = 0; i <= 3; i++) {
        if (i < 3) res.m[i+1][i] = v;
        res.m[0][i] = 0;
    }
    return res;
}
void update(int q, int v) {
    q += S-1;
    seg[q] = mat(v);
    for (q >>= 1; q; q >>= 1) {
        seg[q] = seg[q * 2 + 1] * seg[q * 2];
    }
}

void solve() {
    ll ans = -LLINF;
    for (int i = 0; i <= 3; i++) { // num taken previously
        vec v; v.m[i] = 0;
        auto cans = seg[1] * v;
        for (int j = 0; j <= i; j++)
            ans = max(ans, cans.m[j]);
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 0; i < S*2; i++) seg[i] = matrix(1);
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
        update(i, A[i]);
    }
    solve();

    cin >> Q;
    while (Q--) {
        int i, x; cin >> i >> x;
        update(i, x);
        solve();
    }

    return 0;
}

