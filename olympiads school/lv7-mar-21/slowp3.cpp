// ./game-of-palindrome.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

using pii = pair<int, int>;
using T = tuple<int, int, int>;

const int MN = 5001, MST=MN*MN+3;
int N, M, Q;
bool vis[MN][MN][3]; // 0->need another 0, 1->need another 1, 2->need nothin'
vector<int> g[MN][2];
string s;

int qptr = 0;
T q[MST];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> Q >> s;
    auto push = [&] (int u, int v, int t) {
        if (!vis[u][v][t]) {
            vis[u][v][t] = true;
            q[qptr++] = {u, v, t};
        }
    };
    for (auto i = 0; i < N; i++)
        push(i, i, 2);
    for (auto i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        g[a][s[b] - '0'].push_back(b);
        g[b][s[a] - '0'].push_back(a);
        if (s[a] == s[b])
            push(a, b, 2);
    }
    while (qptr > 0) {
        auto [a, b, want] = q[--qptr];
        if (want == 2) {
            for (auto i = 0; i < 2; i++)
                for (auto to : g[a][i])
                    push(to, b, i);
        }
        else {
            for (auto to : g[b][want])
                push(a, to, 2);
        }
    }
    while (Q--) {
        int x, y; cin >> x >> y;
        x--; y--;
        cout << (vis[x][y][2] || vis[y][x][2] ? "YES" : "NO") << '\n';
    }

    return 0;
}
