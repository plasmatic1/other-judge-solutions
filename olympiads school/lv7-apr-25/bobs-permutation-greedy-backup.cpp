// ./bobs-permutation.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

const int MN = 1001;
// const int MN = 5e5+1;
int N,
    A[MN], W[MN], indeg[MN];
vector<int> g[MN];

vector<pii> seq;
bool vis[MN]; 
void check() {
    queue<int> q;
    for (auto i = 1; i <= N; i++) if (A[i]) indeg[A[i]]++;
    for (auto i = 1; i <= N; i++)
        if (!indeg[i])
            q.push(i);
    while (!q.empty()) {
        auto c = q.front(); q.pop(); seq.emplace_back(c, W[c]);
        int to = A[c];
        if (to && --indeg[to] == 0) {
            vis[to] = true;
            q.push(to);
        }
    }
    if ((int)seq.size() != N) {
        cout << "-1\n";
        exit(0);
    }
}

bool adj[MN][MN];
void dfs(int c, bool vis[MN]) {
    if (vis[c]) return;
    vis[c] = true;
    for (auto to : g[c]) dfs(to, vis);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (auto i = 1; i <= N; i++) {
        cin >> A[i]; // i must come after A[i]
        if (A[i])
            g[A[i]].push_back(i);
    }

    for (auto i = 1; i <= N; i++) {
        cin >> W[i];
        dfs(i, adj[i]);
    }
    check();

    vector<pii> seq; // v, i
    for (auto [v, i] : vals) {
        auto ptr = seq.end();
        memset(vis, 0, sizeof vis);
        dfs(i);
        for (auto it = seq.begin(); it != seq.end(); it++)
            if (vis[it->second])
                ptr = min(ptr, it);

        printf("AFTER i=%d v=%d SEQIDX=%d\n", i,v,int(ptr-seq.begin()));
        seq.emplace(ptr, v, i);

        printf("SEQ=");
        for (auto i = 0; i < int(seq.size()); i++) printf("{i=%d v=%d}, ",seq[i].second,seq[i].first);
        printf("\n");
    }

    ll ans = 0;
    for (auto i = 0; i < N; i++) ans += ll(i+1) * seq[i].first;
    cout << ans << '\n';

    return 0;
}

