// ./bobs-shortest-non-common-substring.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

struct state {
    int len, link;
    map<char, int> next;
};
const int MAXLEN = 2010;
state st[MAXLEN * 2];
int sz, last;
void sa_init() {
    st[0].len = 0;
    st[0].link = -1;
    sz++;
    last = 0;
}
void sa_extend(char c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    int p = last;
    while (p != -1 && !st[p].next.count(c)) {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

const int MN = 2e3 + 69;
int N, M,
    nxt[MN][26], dp1[MN][MN], dp2[MN][MN*2];
string s, t;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> s >> t;
    N = s.length();
    M = t.length();

    fill(nxt[M], nxt[M]+26, M);
    for (auto i = M-1; i >= 0; i--) {
        copy(nxt[i+1], nxt[i+1]+26, nxt[i]);
        nxt[i][t[i] - 'a'] = i;
    }
    sa_init();
    for (auto i = 0; i < M; i++)
        sa_extend(t[i]);

    // L1,2
    int ans1 = INF, ans2 = INF;
    for (auto i = 0; i < N; i++) {
        int tidx = -1, saNode = 0, cans1 = INF, cans2 = INF;
        for (auto j = i; j < N; j++) {
            if (cans1 == INF) {
                auto ptr = st[saNode].next.find(s[j]);
                if (ptr == st[saNode].next.end()) cans1 = j-i+1;
                else saNode = ptr->second;
            }
            if (cans2 == INF) {
                tidx = nxt[tidx+1][s[j] - 'a'];
                if (tidx >= M) cans2 = j-i+1;
            }
        }
        ans1 = min(ans1, cans1);
        ans2 = min(ans2, cans2);
    }
    // L3,4
    memset(dp1, 0x3f, sizeof dp1);
    memset(dp2, 0x3f, sizeof dp2);
    dp1[0][0] = dp2[0][0] = 0;
    for (auto i = 0; i < N; i++) {
        // dp1
        for (auto j = 0; j <= M; j++) {
            // printf("i=%d j=%d dp=%d\n", i,j,dp1[i][j]);
            int &res = dp1[i+1][nxt[j][s[i] - 'a']+1];
            res = min(res, dp1[i][j]+1);
            dp1[i+1][j] = min(dp1[i+1][j], dp1[i][j]);
        }
        // dp2
        for (auto j = 0; j < sz; j++) {
            auto _ptr = st[j].next.find(s[i]);
            int takeNxt = _ptr == st[j].next.end() ? sz : _ptr->second, &res = dp2[i+1][takeNxt];
            res = min(res, dp2[i][j]+1);
            dp2[i+2][j] = min(dp2[i+2][j], dp2[i][j]);
        }
    }

    int ans3 = INF, ans4 = INF;
    for (auto i = 0; i <= N; i++) {
        ans3 = min(ans3, dp2[i][sz]);
        ans4 = min(ans4, dp1[i][M+1]);
    }

    if (ans1 == INF) ans1 = -1;
    if (ans2 == INF) ans2 = -1;
    if (ans3 == INF) ans3 = -1;
    if (ans4 == INF) ans4 = -1;
    cout << ans1 << '\n' << ans2 << '\n' << ans3 << '\n' << ans4 << '\n';

    return 0;
}
