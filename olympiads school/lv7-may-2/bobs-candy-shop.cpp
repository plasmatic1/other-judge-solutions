// ./bobs-candy-shop.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 1e5 + 1;
using T = tuple<int, int, int>;
using Qu = tuple<ll, ll, int>;

struct BIT {
    ll bit[MN];
    void add(int x, ll v) {
        for (; x < MN; x += x & -x)
            bit[x] += v;
    }
    ll query(int x) {
        ll res = 0;
        for (; x; x -= x & -x)
            res += bit[x];
        return res;
    }
    int search(ll sum) {
        int idx = 0;
        ll cur = 0;
        if (query(MN-1) < sum) return INF;
        for (int cbit = 1 << 17; cbit; cbit >>= 1) {
            int alt = idx | cbit;
            if (alt < MN && cur+bit[alt] < sum) {
                idx = alt;
                cur += bit[alt];
            }
        }
        return idx+1;
    }
};

int N, Q;
T its[MN];
ll ans[MN];
BIT sum, cnt;

void change(int cost, int amt) {
    sum.add(cost, ll(cost)*amt);
    cnt.add(cost, amt);
}
ll getMinCost(ll need) {
    int costTo = cnt.search(need);
    if (costTo == INF) return LLINF;
    ll queryCnt = cnt.query(costTo), cost = sum.query(costTo);
    return cost - (queryCnt - need) * costTo;
}

void CDQ(int l, int r, vector<Qu> qs) {
    if (qs.empty()) return;
    if (l == r) {
        auto [v, c, k] = its[l];
        change(c, k);
        for (auto [w, l, i] : qs) {
            if (getMinCost(l) <= w) ans[i] = v;
            else ans[i] = -1;
        }
        change(c, -k);
        return;
    }

    vector<Qu> lhs, rhs;
    int mid = (l + r) / 2;
    for (auto i = mid+1; i <= r; i++) {
        auto [v, c, k] = its[i];
        change(c, k);
    }
    // printf("START CDQ l=%d r=%d\n", l,r);
    for (auto [w, l, i] : qs) {
        // printf("CHECK query w=%lld l=%lld i=%d MINCOST=%lld\n", w,l,i,getMinCost(l));
        if (getMinCost(l) <= w)
            rhs.emplace_back(w, l, i);
        else
            lhs.emplace_back(w, l, i);
    }

    CDQ(l, mid, lhs);
    for (auto i = mid+1; i <= r; i++) {
        auto [v, c, k] = its[i];
        change(c, -k);
    }
    CDQ(mid+1, r, rhs);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    for (auto i = 0; i < N; i++) {
        int v, c, k; cin >> v >> c >> k;
        its[i] = {v, c, k};
    }
    sort(its, its+N);

    vector<Qu> qus;
    for (auto i = 0; i < Q; i++) {
        ll w, l; cin >> w >> l;
        qus.emplace_back(w, l, i);
    }

    CDQ(0, N-1, qus);

    for (auto i = 0; i < Q; i++) cout << ans[i] << '\n';

    return 0;
}

