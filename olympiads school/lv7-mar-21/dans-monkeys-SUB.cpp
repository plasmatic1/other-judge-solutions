// ./dans-monkeys.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

// TREAP STARTS HERE
using TT = int;
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
    else if (lsz < k) return kth(rt->l, k);
    return rt;
}
string __(node *n) {
    string res = "[";
    function<void(node*)> trav = [&] (node* n) {
        if (!n) return;
        trav(n->l);
        res += to_string(n->val) + ", ";
        trav(n->r);
    };
    trav(n);
    return res + "]";
}
#define _(x) (__(x).c_str())
// TREAP ENDS HERE
// const int MN = 3e5 + 1;
const int MN = 1001, MM = 5e4+1;
int R, C, Q;

// st3
node *row;
// st1,2
ll grid[MN][MM], fcol[MM]; int rr[MN], cc[MN];
vector<ll> rowval;
int sub = -1;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> R >> C >> Q;
    if (R == 1) sub = 3;
    else if (R <= 1000 && C <= 1000 && Q <= 500) sub = 1;
    else if (Q <= 500) sub = 2;
    else assert(0);

    if (sub == 1 || sub == 2) {
        for (auto i = 0; i < Q; i++) {
            cin >> rr[i] >> cc[i];
            rr[i]--; cc[i]--;
            rowval.push_back(rr[i]);
        }
        sort(rowval.begin(), rowval.end());
        rowval.resize(unique(rowval.begin(), rowval.end()) - rowval.begin());

        int sz = rowval.size();
        for (auto i = 0; i < sz; i++)
            for (auto j = 0; j < C-1; j++)
                grid[i][j] = rowval[i]*C + j;
        for (auto i = 0; i < R; i++)
            fcol[i] = ll(i+1)*C-1;

        for (auto ctr = 0; ctr < Q; ctr++) {
            int r = rr[ctr], rc = lower_bound(rowval.begin(), rowval.end(), rr[ctr]) - rowval.begin(), c = cc[ctr];

            if (c == C-1) {
                cout << fcol[r]+1 << '\n';

                rotate(fcol+r, fcol+r+1, fcol+R);
            }
            else {
                ll rem = grid[rc][c];
                cout << rem+1 << '\n';

                for (auto i = c; i < C-2; i++)
                    grid[rc][i] = grid[rc][i+1];
                grid[rc][C-2] = fcol[r];

                fcol[r] = rem;
                rotate(fcol+r, fcol+r+1, fcol+R);
            }
        }
    }
    else if (sub == 3) {
        for (auto i = 0; i < C; i++)
            merge(row, row, new node(i));
        // printf("Itree=%s\n", _(row)); fflush(stdout);
        while (Q--) {
            int r, c; cin >> r >> c;
            r--; c--; assert(!r);

            node *curv, *rhs;
            split(row, c, row, curv);
            split(curv, 1, curv, rhs);
            // printf("r=%d c=%d row=%s curv=%s rhs=%s\n", r, c, _(row), _(curv), _(rhs)); fflush(stdout);
            assert(curv);
            // int res = curv->val;
            cout << curv->val+1 << '\n';
            merge(row, row, rhs);
            merge(row, row, curv);

            // printf("r=%d c=%d res=%d tree=%s\n", r,c,res,_(row)); fflush(stdout);
        }
    }

    return 0;
}
