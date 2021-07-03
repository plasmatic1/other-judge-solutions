// ./bobs-substring-modification.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

int N, K;

const int MAXLEN = 3e5 + 10;
struct state {
    int len, link;
    map<char, int> next;
};
vector<int> g[MAXLEN * 2];
state st[MAXLEN * 2];
int cnt[MAXLEN*2][2];
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

    if (st[cur].len <= N) // part of A
        cnt[cur][1] += st[cur].len >= K;
    else if (st[cur].len > N+1) // part of B
        cnt[cur][0] += st[cur].len >= N+K+1;
}

// struct trie {
//     map<char, trie*> ch;
//     int cnt[2];
//     trie() { cnt[0] = cnt[1] = 0; }
// };
// void ins(trie* rt, int c, string &s, int type) {
//     if (c == (int)s.length()) return void(rt->cnt[type]++);
//     if (!rt->ch.count(s[c])) rt->ch[s[c]] = new trie;
//     ins(rt->ch[s[c]], c+1, s, type);
// }
// ll ans = 0;
// pii dfs(trie *rt, int dep) {
//     for (auto [c, to] : rt->ch) {
//         auto [to0, to1] = dfs(to, dep+1);
//         rt->cnt[0] += to0;
//         rt->cnt[1] += to1;
//     }
//     int left = min(rt->cnt[0], rt->cnt[1]);
//     rt->cnt[0] -= left;
//     rt->cnt[1] -= left;
//     ans -= ll(left) * dep;
//     return {rt->cnt[0], rt->cnt[1]};
// }

string A, B;

// void setup(int c, int K) {
//     for (auto to : g[c]) {
//         setup(to, K);
//     }
//     if (g[c].empty()) {
//         printf("SETUP LEAF c=%d dep=%d\n", c,st[c].len);
//         if (st[c].len <= N) // part of A
//             cnt[c][1] += st[c].len >= K;
//         else if (st[c].len > N+1) // part of B
//             cnt[c][0] += st[c].len >= N+K+1;
//     }
// }

ll ans = 0;
int totC[2];
pii dfs(int c) {
    totC[0] += cnt[c][0]; totC[1] += cnt[c][1];
    for (auto to : g[c]) {
        dfs(to);
        cnt[c][0] += cnt[to][0];
        cnt[c][1] += cnt[to][1];
    }
    int left = min(cnt[c][0], cnt[c][1]);
    // printf("c=%d dep=%d cnt=%d,%d left=%d\n", c,st[c].len,cnt[c][0],cnt[c][1],left);
    ans -= (ll)min(K, st[c].len) * left;
    cnt[c][0] -= left;
    cnt[c][1] -= left;

    return {cnt[c][0], cnt[c][1]};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K >> A >> B;

    sa_init();
    for (auto i = N-1; i >= 0; i--) sa_extend(B[i]);
    sa_extend('$');
    for (auto i = N-1; i >= 0; i--) sa_extend(A[i]);
    for (auto i = 1; i < sz; i++) g[st[i].link].push_back(i);
    // for (auto i = 0; i < sz; i++) {
    //     printf("i=%d dep=%d\n", i,st[i].len);
    // }
    // setup(0, K);

    ans = ll(N-K+1) * K;
    dfs(0);
    cout << ans << '\n';
    // printf("totc=%d,%d\n", totC[0],totC[1]);

    return 0;
}

