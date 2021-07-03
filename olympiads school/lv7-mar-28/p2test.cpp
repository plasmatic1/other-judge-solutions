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

    vector<int> u;
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
        printf("%lu\n", haveClr.size());
        if (haveClr.size()==0) {
            u.push_back(i);
        }
    }

#ifdef DBG
    printf("nouniq=%lu\n", u.size());
    for (auto x : u) printf("%d\n", x);
    printf("nouniq=%lu\n", u.size());
#endif

    return 0;
}

