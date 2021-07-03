// ./dans-monkeys.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

// TREAP STARTS HERE
using TT = ll;
mt19937 mt(26022021);
uniform_int_distribution<int> dis(INT_MIN, INT_MAX);

struct node {
    int pri, sz; TT val; 
    node *l, *r;
    node(TT val0) : pri(dis(mt)), sz(1), val(val0), l(nullptr), r(nullptr) { }
};
int SZ(node *n) { return n ? n->sz : 0; }
void upd(node *n) {
    if (n) {
        n->sz = SZ(n->l) + SZ(n->r) + 1;
    }
}
void split(node *t, int key, node *&l, node *&r) { // l->first (KEY) nodes
    if (!t) return void(l = r = nullptr);
    if (SZ(t->l)+1 <= key) { l = t; split(t->r, key-SZ(t->l)-1, t->r, r); }
    else { r = t; split(t->l, key, l, t->l); }
    upd(l); upd(r);
}
void merge(node *&t, node *l, node *r) {
    if (!l || !r) return void(t = l ? l : r); 
    if (l->pri > r->pri) { t = l; merge(t->r, t->r, r); } // l on top
    else { t = r; merge(t->l, l, t->l); }
    upd(t);
}
node* kth(node *rt, int k) {
    int lsz = SZ(rt->l) + 1;
    if (lsz < k) return kth(rt->r, k-lsz);
    else if (lsz > k) return kth(rt->l, k);
    return rt;
}
// TREAP ENDS HERE

struct snode {
    snode *l, *r;
    int sum;
    snode() : l(nullptr), r(nullptr), sum(0) {}
};
int SUM(snode *n, int l, int r) { return r - l + 1 - (n ? n->sum : 0); }
snode* lc(snode *n) { return n ? n->l : nullptr; }
snode* rc(snode *n) { return n ? n->r : nullptr; }
int update(snode *&n, int q, int v, int l, int r) {
    if (q > r || q < l) return n ? n->sum : 0;
    if (!n) n = new snode;
    if (l == r) return n->sum = v;
    int mid = (l + r) / 2;
    return n->sum = update(n->l, q, v, l, mid) + update(n->r, q, v, mid+1, r);
}
int query(snode *n, int k, int l, int r) {
    if (l == r) return SUM(n, l, r) <= k ? l : -INF;
    int mid = (l + r) / 2;
    if (SUM(lc(n), l, mid) >= k) return query(lc(n), k, l, mid);
    return max(query(rc(n), k-SUM(lc(n), l, mid), mid+1, r), mid);
}

const int MN = 3e5 + 1;
int R, C, Q;
node *fcol = nullptr, *rows[MN];
snode *pre[MN];

void shiftkth(node *&n, int k) {
    node *tv, *rhs;
    split(n, k-1, n, tv);
    split(tv, 1, tv, rhs);
    merge(n, n, rhs);
    merge(n, n, tv);
}

ll popkth(int r, int c, bool shift) { // shift=1 -> actually do the MOOOVE
    if (c == C-1) {
        ll res = kth(fcol, r+1)->val;
        if (shift)
            shiftkth(fcol, r+1);

        return res;
    }

    int origLeft = C-1 - SZ(rows[r]), foundIdx = -1; ll vkey = -1;
    if (c < origLeft) {
        foundIdx = query(pre[r], c+1, 1, C);
        vkey = ll(r)*C + foundIdx - 1;
    }
    else {
        vkey = kth(rows[r], c-origLeft+1)->val;
    }

    if (shift) {
        if (c < origLeft) {
            update(pre[r], foundIdx, 1, 1, C);
            auto fp = kth(fcol, r+1);
            merge(rows[r], rows[r], new node(fp->val));
            fp->val = vkey;
        }
        else {
            int idx = c-origLeft+1;
            node *tv, *rhs;
            split(rows[r], idx-1, rows[r], tv);
            split(tv, 1, tv, rhs);
            auto fp = kth(fcol, r+1);
            swap(tv->val, fp->val);
            merge(rows[r], rows[r], rhs);
            merge(rows[r], rows[r], tv);
        }

        shiftkth(fcol, r+1);
    }

    return vkey;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> R >> C >> Q;

    for (auto i = 0; i < R; i++)
        merge(fcol, fcol, new node(ll(i+1)*C-1));

    while (Q--) {
        int r, c; cin >> r >> c;
        r--; c--;
        ll res = popkth(r, c, true);
        cout << res+1 << '\n';
    }

    return 0;
}

