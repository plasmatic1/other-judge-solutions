#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

const int MN = 1e5 + 1, LG = 18;
struct spt {
    int N;
    pii tb[LG][MN];
    void init(int n0) {
        N = n0;
        for (auto i = 0; i < LG; i++)
            for (auto j = 0; j < N; j++)
                tb[i][j] = {INF, -1};
    }
    void set(int i, int v) {
        tb[0][i] = {v, i};
    }
    void build() {
        for (auto i = 1; i < LG; i++) {
            int jmp = 1 << (i-1), end = N-(1<<i)+1;
            for (auto j = 0; j < end; j++) {
                tb[i][j] = min(tb[i-1][j], tb[i-1][j+jmp]);
            }
        }
    }
    pii query(int l, int r) {
        int bit = __lg(r-l+1);
        return min(tb[bit][l], tb[bit][r-(1<<bit)+1]);
    }
};

int N;
// ll A[MN];

void _case() {
    cin >> N;

    vector<pii> v(N);
    for (auto i = 0; i < N; i++) {
        // cin >> A[i];
        cin >> v[i].second;
        v[i].first = i;
    }

    vector<pii> newv;
    for (auto [i, x] : v) if (x) newv.emplace_back(i, x);
    v.swap(newv);

    ll ans = 0;
    while (!v.empty()) {
        int sz = v.size();
        int groupCnt = 1;

        int pre = 0, prePos = v[0].first;
        for (auto i = 1; i < sz; i++) {
            auto [idx, val] = v[i];

            int dif = idx-prePos;
            // printf("i=%d dif=%d\n", i,dif);
            if (dif>2) {
                pre = i;
                groupCnt++;
            }
            else if (i-pre >= 2 && dif != prePos-v[i-2].first) {
                // printf("DIFFERENT prePos=%d prePosDif=%d\n", prePos,prePos-v[i-2].first);
                pre = i;
                groupCnt++;
            }

            prePos = idx;
        }

        ans += groupCnt;

        printf("doing rem process groupCnt=%d\n", groupCnt);
        printf("v=");
        for (auto [i, x] : v) printf("(i=%d x=%d), ", i,x);
        printf("\n");

        for (auto &[_, val] : v) val--;

        vector<pii> newv;
        for (auto [i, x] : v) if (x) newv.emplace_back(i, x);
        v.swap(newv);
    }
    // printf("ans=%lld\n", ans);

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int _t; cin >> _t;
    while (_t--) {
        printf("case\n");
        _case();
    }

    return 0;
}
