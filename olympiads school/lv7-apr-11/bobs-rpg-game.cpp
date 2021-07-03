// ./bobs-rpg-game.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

struct TwoSat {
    int N, cord, ccomp;
    vector<int> ord, low, instk, res, stk, comp;
    vector<vector<int>> g;
    void init(int N0) {
        N = N0; cord = ccomp = 0;
        g.assign(N*2+1, vector<int>());
        ord.assign(N*2+1, 0);
        low.assign(N*2+1, 0);
        instk.assign(N*2+1, 0);
        comp.assign(N*2+1, 0);
        res.assign(N+1, 0);
        stk.clear();
    }
    void addEdge(int a, int b) {
        if (a < 0) a = N-a;
        if (b < 0) b = N-b;
        g[a].push_back(b);
    }
    void addOr(int a, int b) {
        addEdge(-a, b);
        addEdge(-b, a);
    }
    void tarjan(int c) {
        ord[c] = low[c] = ++cord;
        instk[c] = true; stk.push_back(c);
        for (auto to : g[c]) {
            if (!ord[to]) {
                tarjan(to);
                low[c] = min(low[c], low[to]);
            }
            else if (instk[to])
                low[c] = min(low[c], ord[to]);
        }

        if (low[c] == ord[c]) {
            int u, cc = ++ccomp;
            do {
                u = stk.back(); stk.pop_back(); instk[u] = false;
                comp[u] = cc;
            } while (u != c);
        }
    }
    void solve() {
        for (auto i = 1; i <= 2*N; i++)
            if (!ord[i])
                tarjan(i);
        for (auto i = 1; i <= N; i++) {
            if (comp[i] == comp[i+N]) {
                res.assign(N+1, -1);
                return;
            }
        }
        for (auto i = 1; i <= N; i++)
            res[i] = comp[i] < comp[i+N]; // 1 > 0
    }
};

const int MN = 5e4 + 1, MM = 1e5 + 1;
int N, D, M,
    v1[MM], v2[MM];
string s;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> D >> s >> M;
    vector<int> xpos;
    for (auto &c : s) c += 'A' - 'a'; // to upper REEEEEEEEEEEE
    for (auto i = 0; i < N; i++)
        if (s[i] == 'X')
            xpos.push_back(i);
    for (auto i = 0; i < M; i++) {
        char t1, t2; int i1, i2; cin >> i1 >> t1 >> i2 >> t2;
        v1[i] = 3*(i1-1) + (t1-'A');
        v2[i] = 3*(i2-1) + (t2-'A');
    }

    int msub = 1<<D;
    for (auto i = 0; i < msub; i++) {
        for (auto j = 0; j < D; j++)
            s[xpos[j]] = 'A' + ((i >> j) & 1);
        // printf("i=%d CurS=%s\n", i,s.c_str());

        // do 2SAT
        TwoSat solver; solver.init(3*N);
        // make sure we don't pick multiple on a team
        for (auto j = 0; j < N; j++) {
            vector<int> allow;
            for (auto k = 'A'; k <= 'C'; k++)
                if (k != s[j])
                    allow.push_back(k - 'A');

            int v1 = 3*j+allow[0], v2 = 3*j+allow[1];
            solver.addEdge(v1+1, -(v2+1));
            solver.addEdge(v2+1, -(v1+1));
            solver.addOr(v1+1, v2+1);
            int v3 = 3*j+(s[j]-'A'); // the not allowed
            solver.addOr(-(v3+1), -(v3+1));
            // printf("j=%d allow=%d,%d oth=%d v1=%d v2=%d v3=%d\n", j,allow[0],allow[1],s[j]-'A',v1,v2,v3);
        }
        // given restrictions
        for (auto j = 0; j < M; j++) {
            solver.addEdge((v1[j]+1), (v2[j]+1));
            solver.addEdge(-(v2[j]+1), -(v1[j]+1));
        }
        solver.solve();

        // check res
        auto &res = solver.res;
        if (res[0] != -1) {
            string ans(N, '-');
            for (auto i = 0; i < N; i++) {
                int ok = -1;
                for (auto j = 0; j < 3; j++) {
                    if (res[3*i+j + 1]) { // 0->1 ind
                        ok = j;
                        break;
                    }
                }
                assert(ok != -1);
                ans[i] = 'A' + ok;
            }

            cout << ans << '\n';
            return 0;
        }
    }
    cout << "-1\n";

    return 0;
}

