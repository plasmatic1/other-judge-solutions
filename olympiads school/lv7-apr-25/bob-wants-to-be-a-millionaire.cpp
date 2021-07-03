// ./bob-wants-to-be-a-millionaire.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

struct VEFlow {
    int N;
    vector<vector<int>> cap, g;
    VEFlow(int N0) : N(N0), cap(N, vector<int>(N)), g(N) {}
    void addEdge(int a, int b, int w) {
        g[a].push_back(b);
        g[b].push_back(a);
        cap[a][b] = w;
    }

    vector<int> par;
    void dfs(int c, int p) {
        if (par[c] != -1) return;
        par[c] = p;
        for (auto to : g[c])
            if (cap[c][to] > 0)
                dfs(to, c);
    }
    int getFlow(int s, int t) {
        int res = 0;
        bool ok = false;
        do {
            par.assign(N, -1);
            dfs(s, s); ok = par[t] != -1;
            if (ok) {
                for (auto c = t; c != s; c = par[c]) {
                    cap[par[c]][c]--;
                    cap[c][par[c]]++;
                }
                res++;
            }
        } while (ok);
        return res;
    }
};

const int MN = 1001;
int N, M,
    X[MN], Y[MN];

bool check(int k) {
    VEFlow flow(N+k+2);
    for (auto i = 1; i <= N; i++) flow.addEdge(0, i, 1);
    for (auto i = 1; i <= k; i++) flow.addEdge(N+i, N+k+1, 1);
    for (auto i = 1; i <= k; i++) {
        flow.addEdge(X[i], N+i, 1);
        flow.addEdge(Y[i], N+i, 1);
    }
    return flow.getFlow(0, N+k+1) == k;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (auto i = 1; i <= M; i++) {
        cin >> X[i] >> Y[i];
        X[i]++; Y[i]++;
    }

    int l = 0, r = M+1;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (check(mid)) l = mid;
        else r = mid;
    }
    cout << l << '\n';

    return 0;
}

