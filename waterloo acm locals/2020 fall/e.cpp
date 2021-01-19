// e.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long; using ull = unsigned long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<long long, long long>;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

struct ed {
    int v, i; bool dir; // dir=0->fwd, dir=1->rev
};

template <typename T> void mina(T &a, T b) { a = min(a, b); }

const int MN = 2e5 + 1;
const string DIRS = "><";
int N, M;
vector<ed> g[MN];
char ans[MN];

int ord[MN], low[MN], cord = 0;
void dfs(int c, int p) {
    ord[c] = low[c] = ++cord;

    map<pii, pii> goidno;
    for (auto to : g[c]) {
        if (to.v != p) {
            if (!ord[to.v]) { // tree edge
                dfs(to.v, c);
                mina(low[c], low[to.v]);

                ans[to.i] = DIRS[to.dir];
            }
            else { // back edge
                mina(low[c], ord[to.v]);

                ans[to.i] = DIRS[!to.dir];
            }

            int a = to.v, b = c;
            if (a > b) swap(a, b);
            pii p{a, b};

            // assumes that this is a tree edge since non tree edges obviously cannot be bridges
            // make it go up lol
            if (low[to.v] > ord[c]) { // bridge!!
                if (goidno.count(p)) {
                    ans[to.i] = DIRS[!to.dir];
                    auto res = goidno[p];
                    ans[res.first] = DIRS[res.second];
                }
                else
                    ans[to.i] = '=';
            }
            goidno[p] = {to.i, to.dir};
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M);
    for (auto i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back({b, i, 0});
        g[b].push_back({a, i, 1});
    }

    dfs(1, -1);
    for (auto i = 0; i < M; i++)
        cout << (ans[i]) << '\n';

    return 0;
}

