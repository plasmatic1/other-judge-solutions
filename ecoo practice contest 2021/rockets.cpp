// ./rockets.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 1e5 + 1;
int N, C, D;
vector<int> g[MN];

int dfs(int c, int p) {
    int sz = 1;
    for (auto to : g[c])
        if (to != p)
            sz += dfs(to, c);
    return sz;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (auto i = 1; i < N; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    cin >> C >> D;

    int sa = dfs(C, D), sb = dfs(D, C);
    if (sa % 2 == 0 || sb % 2 == 0) cout << "Let's play >:)\n";
    else cout << "NOU >:(\n";

    return 0;
}

