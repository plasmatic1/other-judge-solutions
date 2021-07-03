// ./bobs-coloring-game.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

const int MN = 1e4 + 1, MM = 2e4 + 1;
int N, M,
    A[MM], B[MM];
vector<int> g[MN];

// clr
int clr[MN];
bool bad = false;
void dfs(int c, int cclr) {
    if (clr[c] != -1) {
        if (clr[c] != cclr) bad = true;
        return;
    }
    clr[c] = cclr;
    for (auto to : g[c])
        dfs(to, cclr^1);
}

// brute force
const int RES[3][2] = {{0, 1}, {0, 2}, {1, 2}};
int rest[MN][2];

bool foundOk = false;
void rec2(int c) {
    if (c == N+1) {
        bool ok = true;
        for (auto i = 1; i <= N; i++) {
            ok &= clr[i] == rest[i][0] || clr[i] == rest[i][1];
        }
        for (auto i = 0; i < M; i++) {
            ok &= clr[A[i]] != clr[B[i]];
        }

        foundOk |= ok;
        return;
    }
    for (auto i = 0; i < 3; i++) {
        clr[c] = i;
        rec2(c+1);
    }
}

void rec(int c) {
    if (c == N+1) {
        foundOk = false;
        rec2(1);
        if (!foundOk) bad = true;
        return;
    }
    for (auto i = 0; i < 3; i++) {
        copy(RES[i], RES[i]+2, rest[c]);
        rec(c+1);
    }
}

void solve() {
    // if (N > 6) {
    //     while (true);
    // }

    memset(clr, -1, sizeof clr);
    for (auto i = 1; i <= N; i++) {
        if (clr[i] == -1)
            dfs(i, 0);
    }
    memset(clr, 0, sizeof clr);
    if (bad) return void(cout << "NO\n");
    rec(1);
    if (bad) return void(cout << "NO\n");

    cout << "YES\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        // Input
        cin >> N >> M;
        // set<pii> use;
        for (auto i = 0; i < M; i++) {
            int a, b; cin >> a >> b;
            g[a].push_back(b);
            g[b].push_back(a);
            A[i] = a; B[i] = b;

            // if (a > b) swap(a, b);
            // assert(!use.count({a, b}));
            // use.emplace(a, b);
        }
        
        solve();

        bad = false;
        for (auto i = 1; i <= N; i++) {
            g[i].clear();
        }
    }
}
