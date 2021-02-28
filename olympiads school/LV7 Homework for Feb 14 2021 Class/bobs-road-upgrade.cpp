// ./bobs-road-upgrade.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
#define pb push_back

struct ed {
    int v; ll w;
    bool operator<(const ed &o) const { return w > o.w; }
};

const int MN = 1e5 + 1, MM = 2e5 + 1;
int N, M, C,
    A[MM], B[MM], W[MM];
vector<ed> g[MN];
ll dis[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> C;
    for (int i = 0; i < M; i++) {
        int a, b, c; cin >> a >> b >> c;
        g[a].pb({b, c});
        g[b].pb({a, c});
        A[i] = a;
        B[i] = b;
        W[i] = c;
    }

    memset(dis, 0x3f, sizeof dis);
    priority_queue<ed> pq;
    pq.push({1, 0}); dis[1] = 0;
    while (!pq.empty()) {
        auto c = pq.top(); pq.pop();
        if (c.w > dis[c.v]) continue;
        for (auto to : g[c.v]) {
            ll alt = c.w + to.w;
            if (alt < dis[to.v]) {
                dis[to.v] = alt;
                pq.push({to.v, alt});
            }
        }
    }
    vector<pair<ll, int>> es;
    set<ll, greater<ll>> diss;
    for (int i = 0; i < M; i++) es.pb({max(dis[A[i]], dis[B[i]]), W[i]});
    for (int i = 1; i <= N; i++) diss.insert(dis[i]);
    sort(es.begin(), es.end(), greater<>());

    int ptr = 0;
    ll ans = LLINF, cur = 0;
    for (auto w : diss) {
        while (ptr < M && es[ptr].first > w) {
            cur += es[ptr].second;
            ptr++;
        }
        ans = min(ans, ll(C) * w + cur);
    }

    cout << ans << '\n';

    return 0;
}

