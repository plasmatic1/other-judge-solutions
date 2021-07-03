// ./bobs-evil-plan.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

struct query {
    int i, l, r;
    bool operator<(const query &o) const {
        return r > o.r;
    }
};
struct change {
    char id; int x, y, oldr; char oldrnk; bool oldf;
};

const int MN = 2e5 + 10, DSUS = MN;
struct DSU {
    vector<change> chs;
    int dsu[DSUS]; char rnk[DSUS];
    bool F[DSUS];
    void init() {
        fill(rnk, rnk + DSUS, 1);
        iota(dsu, dsu + DSUS, 0);
        chs.reserve(3000000);
    }
    int rt(int x) { return dsu[x] == x ? x : rt(dsu[x]); }
    int clr(int x) { return dsu[x] == x ? 0 : F[x] ^ clr(dsu[x]); }
    bool sameClr(int x, int y) { return rt(x) == rt(y) && clr(x) == clr(y); }
    void unite(int x, int y, int chid) {
        bool sameclr = clr(x) == clr(y);
        x = rt(x); y = rt(y);
        if (x == y) return;
        if (rnk[x] < rnk[y]) swap(x, y); // y into x
        chs.push_back({(char)chid, x, y, dsu[y], (char)rnk[x], F[y]});
        if (rnk[x] == rnk[y])
            rnk[x]++;
        if (sameclr)
            F[y] = 1;
        dsu[y] = x;
    }
    void rollback(int to) {
        while (!chs.empty() && chs.back().id >= to) {
            auto &c = chs.back();
            dsu[c.y] = c.oldr;
            F[c.y] = c.oldf;

            chs.pop_back();
        }
    }
};

const int BS = 450*2, BCNT = MN/BS+10;
int N, M, Q,
    A[MN], B[MN];
vector<query> qs[BCNT];
bool ans[MN];

DSU dsu;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> Q;
    for (auto i = 1; i <= M; i++) {
        cin >> A[i] >> B[i];
    }
    for (auto i = 0; i < Q; i++) {
        int l, r; cin >> l >> r;
        qs[l/BS].push_back({i, l, r});
    }

    int maxb = M/BS;
    dsu.init();
    int fptr = 1;
    bool initTrue = false;
    for (auto i = 0; i <= maxb; i++) {
        sort(qs[i].begin(), qs[i].end());
        int fst = min(M, max(1, i*BS));

        auto addEdge = [&] (int a, int b, bool &ans, int id) {
            if (dsu.sameClr(a, b)) {
                ans = true;
                return;
            }
            dsu.unite(a, b, id);
        };

        int ctr = M;
        while (!initTrue && fptr < fst) {
            addEdge(A[fptr], B[fptr], initTrue, 0);
            fptr++;
        }
        bool blockInitTrue = initTrue;

        for (auto &q : qs[i]) {
            while (!blockInitTrue && ctr > q.r) {
                addEdge(A[ctr], B[ctr], blockInitTrue, 1);
                ctr--;
            }
            if (!blockInitTrue) {
                bool newTrue = false;
                for (auto j = fst; j < q.l; j++) {
                    addEdge(A[j], B[j], newTrue, 2);
                    if (newTrue) break;
                }
                ans[q.i] = newTrue;
                dsu.rollback(2);
            }
            else
                ans[q.i] = true;
        }
        dsu.rollback(1);
    }

    for (auto i = 0; i < Q; i++) {
        cout << (ans[i] ? "YES" : "NO") << '\n';
    }

    return 0;
}

