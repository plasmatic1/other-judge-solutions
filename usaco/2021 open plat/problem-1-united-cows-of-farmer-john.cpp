// ./problem-1-united-cows-of-farmer-john.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds; 
template <typename T, class comp = less<T>> using os_tree = tree<T, null_type, comp, rb_tree_tag, tree_order_statistics_node_update>;

const int MN = 2e5 + 1;
int N,
    A[MN];
vector<int> ind[MN];

struct BIT {
    int bit[MN];
    void add(int x, int v) {
        if (x < 1 || x > N) return;
        for (; x < MN; x += x & -x)
            bit[x] += v;
    }
    int query(int x) {
        int sum = 0;
        for (; x; x -= x & -x)
            sum += bit[x];
        return sum;
    }
};
BIT nxtF;

#define MID int mid = (l + r) / 2, lhs = i+1, rhs = i+(mid-l+1)*2;
struct node {
    ll seg, cntF, lazy;
};
node seg[MN*2];
void push(int i, int l, int r) {
    auto &n = seg[i];
    if (n.lazy) {
        n.seg += n.lazy * n.cntF;
        if (l != r) {
            MID;
            seg[lhs].lazy += n.lazy;
            seg[rhs].lazy += n.lazy;
        }
        n.lazy = 0;
    }
}
void updateR(int ql, int qr, int v, int i=1, int l=1, int r=N) {
    push(i, l, r);
    if (ql > r || qr < l) return;
    if (ql <= l && r <= qr) {
        seg[i].lazy += v;
        push(i, l, r);
        return;
    }
    MID;
    updateR(ql, qr, v, lhs, l, mid); updateR(ql, qr, v, rhs, mid+1, r);
    seg[i].seg = seg[lhs].seg + seg[rhs].seg;
    seg[i].cntF = seg[lhs].cntF + seg[rhs].cntF;
}
void updateC(int q, int v, int ncnt, int i=1, int l=1, int r=N) {
    push(i, l, r);
    if (q > r || q < l) return;
    if (q == l && q == r) {
        seg[i].cntF += v;
        seg[i].seg += ncnt;
        return;
    }
    MID;
    updateC(q, v, ncnt, lhs, l, mid); updateC(q, v, ncnt, rhs, mid+1, r);
    seg[i].seg = seg[lhs].seg + seg[rhs].seg;
    seg[i].cntF = seg[lhs].cntF + seg[rhs].cntF;
}
ll query(int ql, int qr, int i=1, int l=1, int r=N) {
    if (ql > r || qr < l) return 0;
    push(i, l, r);
    if (ql <= l && r <= qr) return seg[i].seg;
    MID;
    return query(ql, qr, lhs, l, mid) + query(ql, qr, rhs, mid+1, r);
}

int nxt(int k) {
    return *upper_bound(ind[A[k]].begin(), ind[A[k]].end(), k);
}

void changeNxt(int idx, int delta) {
    updateR(idx, nxt(idx)-1, delta);
    nxtF.add(idx, delta);
    nxtF.add(nxt(idx), -delta);
    updateC(idx, delta, nxtF.query(idx-1));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (auto i = 1; i <= N; i++) ind[i].push_back(0);
    for (auto i = 1; i <= N; i++) {
        cin >> A[i];
        ind[A[i]].push_back(i);
    }
    for (auto i = 1; i <= N; i++)
        ind[i].push_back(N+1);

    ll ans = 0;
    {
        vector<bool> check(N+1);
        for (auto i = 1; i <= N; i++) {
            if (!check[A[i]]) {
                changeNxt(i, 1);
                check[A[i]] = true;
            }
        }
    }
    for (auto i = 1; i <= N; i++) {
        int nxti = nxt(i);

        // change cur
        changeNxt(i, -1);
        ll cont = query(i+1, nxti-1);
        ans += cont;
        if (nxti <= N)
            changeNxt(nxti, 1);
    }
    cout << ans << '\n';

    return 0;
}
