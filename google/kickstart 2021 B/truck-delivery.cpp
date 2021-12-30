// ./truck-delivery.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

ll gcd(ll a, ll b) { return b?gcd(b,a%b):a; }

// Template is 1-indexed
// RMQ + Set query
struct Comp {
    using Data = ll;
    using Update = ll;
    const Data vdef = 0;
    Data merge(Data l, Data r) { return gcd(l, r); }
    void applyUpdate(Data &l, Update &r) { l = r; }
};
#define MID int mid = (l + r) / 2, lhs = i + 1, rhs = i + (mid - l + 1) * 2;
template <class Comp> struct SegmentTree {
    using Data = typename Comp::Data; using Update = typename Comp::Update; Comp C;
    int N;
    vector<Data> seg;
    void init(int n0) {
        N = n0;
        seg.assign(2 * N + 2, C.vdef);
    }
    Data _query(int ql, int qr, int i, int l, int r) {
        if (ql > r || qr < l) return C.vdef;
        if (l >= ql && r <= qr) return seg[i];
        MID;
        return C.merge(_query(ql, qr, lhs, l, mid), _query(ql, qr, rhs, mid + 1, r));
    }
    Data _update(int q, Update v, int i, int l, int r) {
        if (q > r || q < l) return seg[i];
        if (l == q && r == q) {
            C.applyUpdate(seg[i], v);
            return seg[i];
        }
        MID;
        return seg[i] = C.merge(_update(q, v, lhs, l, mid), _update(q, v, rhs, mid + 1, r));
    }
    Data query(int ql, int qr) { return _query(ql, qr, 1, 1, N); }
    void update(int q, Update v) { _update(q, v, 1, 1, N); }
};

const int MN = 5e4+1;
int N, Q;

void solve() {
    cin >> N >> Q;

    vector<vector<tuple<int, int, ll>>> g(N);
    for (auto i = 0; i < N-1; i++) {
        int a, b, l; ll cost; cin >> a >> b >> l >> cost; a--; b--;
        g[a].emplace_back(b, l, cost);
        g[b].emplace_back(a, l, cost);
    }
    vector<vector<pii>> qs(N);
    vector<ll> ans(Q);
    for (auto i = 0; i < Q; i++) {
        int c, w; cin >> c >> w; c--;
        qs[c].emplace_back(i, w);
    }

    int LIM = 2e5;
    SegmentTree<Comp> seg; seg.init(LIM);
    function<void(int, int)> dfs = [&] (int c, int p) {
        // printf("c=%d\n", c);
        // for (auto i = 0; i < 11; i++) printf("i=%d QI=%lld QTO=%lld\n", i,seg.query(i,i),seg.query(1,i));
        for (auto [i, w] : qs[c]) {
            ans[i] = seg.query(1, w);
        }

        for (auto [to, L, C] : g[c]) {
            if (to != p) {
                seg.update(L, C);
                // printf("add L=%d C=%lld\n",L,C);
                dfs(to, c);
                seg.update(L, 0);
                // printf("remove L=%d C=%lld\n",L,C);

                // printf("c=%d to=%d ALL=%lld\n", c,to,seg.query(1,LIM));
            }
        }
    };
    dfs(0, -1);

    for (auto i = 0; i < Q; i++) cout << ans[i] << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for (int caseno = 1; caseno <= T; caseno++) {
        // Input
       
        cout << "Case #" << caseno << ": ";
        solve();

        // Reset
    }
}

