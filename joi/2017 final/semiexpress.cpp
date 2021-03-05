// ./joi-2017-final-p2----semiexpress.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MM = 3011;
int N, M, K,
    ptr[MM];
ll A, B, C, T,
   gain[MM][MM], S[MM];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> K >> A >> B >> C >> T;
    for (int i = 0; i < M; i++) cin >> S[i];
    S[M] = N+1;
    K -= M;

    // calculate "gain" amount
    for (int i = 0; i < M; i++) {
        ll cur = S[i]-1;
        for (int j = 0; j <= K; j++) {
            ll init = (S[i]-1)*B + (cur+1-S[i])*C;
            if (init > T) break;
            ll nxt = min(cur+1 + (T-init) / A, S[i+1]-1);
            gain[i][j] = nxt - cur;
            cur = nxt;
        }
    }

    // init
    priority_queue<pair<ll, int>> pq;
    ll ans = -1; // subtract station 1
    for (int i = 0; i < M; i++) {
        ans += gain[i][0];
        if (K > 0)
            pq.emplace(gain[i][++ptr[i]], i);
    }
    // greedy
    for (int i = 0; i < K; i++) {
        auto t = pq.top(); pq.pop();
        ans += t.first;
        if (ptr[t.second] < K)
            pq.emplace(gain[t.second][++ptr[t.second]], t.second);
    }
    cout << ans << '\n';

    return 0;
}

