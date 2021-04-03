// ./problem-1-no-time-to-dry.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 2e5 + 1;
int N, Q,
    A[MN*2], nxtUnder[MN], nxt[MN];
vector<int> ind[MN];

// count #(distinct) offline
struct query {
    int i, l;
};
vector<query> qs[MN];
int ans[MN], bit[MN], lst[MN*2];
void add(int x, int v) {
    for (; x < MN; x += x & -x)
        bit[x] += v;
}
int query(int x) {
    int sum = 0;
    for (; x; x -= x & -x)
        sum += bit[x];
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    for (auto i = 1; i <= N; i++)
        cin >> A[i];

    // add extra values
    A[N+1] = 0;
    for (auto i = N+2; i <= 2*N+1; i++)
        A[i] = N-(i-N-2);

    // set up "nxt" array
    {
        set<int> idx;
        map<int, vector<int>> iind;
        for (auto i = 1; i <= 2*N+1; i++) {
            iind[A[i]].push_back(i);
            ind[A[i]].push_back(i);
        }

        for (auto &p : iind) {
            if (p.first > 0) {
                for (auto k : p.second) {
                    if (k <= N)
                        nxtUnder[k] = *idx.upper_bound(k);
                }
            }
            for (auto k : p.second)
                idx.insert(k);
        }
    }
    // nxt array part 2
    for (auto i = 1; i <= N; i++) {
        nxt[i] = *upper_bound(ind[A[i]].begin(), ind[A[i]].end(), nxtUnder[i]);
        // printf("i=%d A=%d nxtUnder=%d nxt=%d\n", i,A[i],nxtUnder[i],nxt[i]);
    }

    // read queries
    for (auto i = 0; i < Q; i++) {
        int l, r; cin >> l >> r;
        qs[r].push_back({i, l});
    }

    // answer queries
    memset(lst, -1, sizeof lst);
    for (auto i = 1; i <= N; i++) {
        if (lst[nxt[i]] != -1) //{
            // printf("i=%d nxt=%d old at=%d\n", i, nxt[i], lst[nxt[i]]);
            add(lst[nxt[i]], -1);
        // }
        // printf("i=%d nxt=%d update\n", i, nxt[i]);
        add(lst[nxt[i]] = i, 1);

        for (auto &q : qs[i])
            ans[q.i] = query(i) - query(q.l-1);
    }

    // output
    for (auto i = 0; i < Q; i++)
        cout << ans[i] << '\n';

    return 0;
}

