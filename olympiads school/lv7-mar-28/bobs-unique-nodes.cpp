// ./bobs-unique-nodes.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 2e5 + 1;
int N, M,
    C[MN];
vector<int> g[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (auto i = 0; i < N-1; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (auto i = 1; i <= N; i++) {
        cin >> C[i];
    }

    if (M == 1) {
        vector<int> dis1(N+1), dis2(N+1);
        function<void(int, int, vector<int>&)> dfs = [&] (int c, int p, vector<int> &v) {
            for (auto to : g[c]) {
                if (to != p) {
                    v[to] = v[c] + 1;
                    dfs(to, c, v);
                }
            }
        };
        dis1.assign(N+1, 0);
        dfs(1, -1, dis1);
        int e1 = max_element(dis1.begin(), dis1.end()) - dis1.begin();
        dis1.assign(N+1, 0);
        dfs(e1, -1, dis1);
        int e2 = max_element(dis1.begin(), dis1.end()) - dis1.begin();
        dis2.assign(N+1, 0);
        dfs(e2, -1, dis2);
        // printf("e1=%d e2=%d\n",e1,e2);

        vector<bool> nope(N+1);
        int rad = INF;
        vector<int> rn;
        for (auto i = 1; i <= N; i++) {
            int cr = max(dis1[i], dis2[i]);
            // printf("i=%d cr=%d\n",i,cr);
            if (cr < rad) {
                rad = cr;
                rn = {i};
            }
            else if (cr == rad)
                rn.push_back(i);
        }
        // auto isleaf = [&] (int c) { return g[c].size() == 1; };
        // vector<bool> adjLeaf(N+1);
        // for (auto i = 1; i <= N; i++)
        //     if (isleaf(i))
        //         for (auto to : g[i])
        //             adjLeaf[to] = true;

        auto check = [&] (int c) {
            vector<int> fre(N+1);
            function<void(int, int, int)> cdfs = [&] (int c, int p, int cdep) {
                fre[cdep]++;
                for (auto to : g[c])
                    if (to != p)
                        cdfs(to, c, cdep+1);
            };
            cdfs(c, -1, 0);
            for (auto i = 1; i < int(fre.size()); i++)
                if (fre[i] == 1)
                    return false;
            return true;
        };

        for (auto x : rn) {
            // printf("x=%d rad=%d\n", x,rad);
            function<void(int, int)> dfs2 = [&] (int c, int p) {
                if (!check(c)) return;
                nope[c] = true;
                for (auto to : g[c]) {
                    if (to != p)
                        dfs2(to, c);
                }
            };
            dfs2(x, -1);
        }

        for (auto i = 1; i <= N; i++) cout << !nope[i] << '\n';
    }
    else if (N <= 2000) {
        for (auto i = 1; i <= N; i++) {
            vector<int> fre(N+1), clr(N+1);
            function<void(int, int, int)> dfs = [&] (int c, int p, int cdep) {
                fre[cdep]++;
                clr[cdep] = C[c];
                for (auto to : g[c])
                    if (to != p)
                        dfs(to, c, cdep+1);
            };
            dfs(i, -1, 0);
            set<int> haveClr;
            for (auto j = 1; j <= N; j++)
                if (fre[j] == 1)
                    haveClr.insert(clr[j]);
            cout << haveClr.size() << '\n';
        }
    }

    return 0;
}

