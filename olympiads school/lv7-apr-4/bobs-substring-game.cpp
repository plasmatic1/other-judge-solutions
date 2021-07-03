// ./bobs-substring-game.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

struct state {
    int len, link;
    map<char, int> next;
};
const int MAXLEN = 1.5e6 + 10;
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
state EMPTY;
void sa_reset() {
    fill(st, st+sz, EMPTY);
    last = sz = 0;
}

ll cnt[MAXLEN * 2];
void dfs(int c) {
    if (cnt[c] != -1) return;
    cnt[c] = 1;
    for (auto [_, to] : st[c].next) {
        dfs(to);
        cnt[c] += cnt[to];
    }
}
ll runcnt() {
    fill(cnt, cnt+sz, -1);
    dfs(0);
    return cnt[0];
}

int N, Q;
string s;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> s >> Q;
    N = s.length();

    while (Q--) {
        string t; int l, r; cin >> t >> l >> r;

        sa_reset();
        sa_init();
        for (auto c : s) sa_extend(c);
        ll init = runcnt();

        if (l == 1 && r == N) {
            sa_extend('|');
            for (auto c : t) sa_extend(c);
            ll newc = runcnt() - init;
            cout << (newc - ll(N+1) * (t.length()+1)) << '\n';
        }
        else cout << "-1\n";
    }

    return 0;
}

