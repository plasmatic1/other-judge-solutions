// ./bobs-permutation.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

const int MN = 1001;
int N,
    A[MN], W[MN], indeg[MN];
vector<int> g[MN];

bool vis[MN], isrt[MN]; 
void check() {
    queue<int> q;
    for (auto i = 1; i <= N; i++) 
        for (auto to : g[i]) indeg[to]++;
    for (auto i = 1; i <= N; i++) {
        if (!indeg[i]) {
            q.push(i);
            isrt[i] = true;
        }
    }
    int rem = N;
    while (!q.empty()) {
        auto c = q.front(); q.pop(); rem--;
        for (auto to : g[c]) {
            if (--indeg[to] == 0) {
                vis[to] = true;
                q.push(to);
            }
        }
    }
    if (rem) {
        cout << "-1\n";
        exit(0);
    }
}

vector<int> dfs(int c) {
    vector<int> res;
    for (auto to : g[c]) {
        auto cvs = dfs(to);
        if (res.empty()) res.swap(cvs);
        else {
            int asz = res.size(), bsz = cvs.size();
            vector<vector<tuple<ll, int, int>>> dp(asz+1, vector<tuple<ll, int, int>>(bsz+1));
            for (auto i = 0; i <= asz; i++) {
                for (auto j = 0; j <= bsz; j++) {
                    auto [v, _, __] = dp[i][j];
                    ll nxt = i+j+1;
                    if (i < asz) dp[i+1][j] = max(dp[i+1][j], tuple<ll, int, int>{v + nxt*res[i], i, j});
                    if (j < bsz) dp[i][j+1] = max(dp[i][j+1], tuple<ll, int, int>{v + nxt*cvs[j], i, j});
                }
            }

            vector<int> newRes;
            for (int x = asz, y = bsz; x || y; ) {
                auto [_, px, py] = dp[x][y];
                if (x != px) newRes.push_back(res[px]);
                if (y != py) newRes.push_back(res[py]);
                
                x = px;
                y = py;
            }
            reverse(newRes.begin(), newRes.end());

            res.swap(newRes);
        }
    }
    if (c) res.insert(res.begin(), W[c]);

    printf("c=%d res=\n", c);
    for (auto x : res) printf("%d ", x);
    printf("\n");

    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    if (N >= 1001) while (1);
    for (auto i = 1; i <= N; i++) {
        cin >> A[i]; // i must come after A[i]
        if (A[i])
            g[A[i]].push_back(i);
    }

    // check and init ord
    for (auto i = 1; i <= N; i++) {
        cin >> W[i];
    }
    check();

    // thing??
    for (auto i = 1; i <= N; i++)
        if (isrt[i])
            g[0].push_back(i);

    auto seq = dfs(0);

    // printf("SEQ=");
    // for (auto i = 0; i < int(seq.size()); i++) printf("%d, ",seq[i]);
    // printf("\n");

    ll ans = 0;
    for (auto i = 0; i < N; i++) ans += ll(i+1) * seq[i];
    cout << ans << '\n';

    return 0;
}

