#include <bits/stdc++.h>
#define db(x) cout << (#x) << ": " << x << ", ";
#define dbn cout << endl;
using namespace std;
using ll = long long;

struct trie {
    int cnt = 0;
    bool done = false;
    trie* ch[26];

    trie() {
        cnt = 0;
        done = false;
        memset(ch, 0, sizeof ch);
    }

    ~trie() {
        for (int i = 0; i < 26; i++)
            if (ch[i])
                delete ch[i];
    }
};

void insert(trie* &rt, int pos, int sz, string &s) {
    if (!rt) rt = new trie;
    rt->cnt++;
    if (pos == sz) {
        // do something
        return;
    }

    int id = s[pos] - 'A';
    insert(rt->ch[id], pos + 1, sz, s);
}

bool search(trie* &rt, int pos, int sz, string &s) {
    assert(rt); // searching for already found strings only
    if (pos == sz) {
        return false;
    }

    int id = s[pos] - 'A';
    bool wkNext = search(rt->ch[id], pos + 1, sz, s);
    // db(s) db(pos) db(sz) db(rt->cnt) db(wkNext) dbn;
    if (!wkNext) { // This is the best one
        if (rt->cnt >= 2 && pos > 0 && !rt->done) { // if pos == 1 then bad
            rt->done = true;
            rt->cnt -= 2;
            return true;
        }
        return false;
    }
    else {
        rt->cnt -= 2;
        return true;
    }
}

const int MN = 1001;
int n;
string words[MN];
trie *rt = nullptr;

int solve() {
    for (int i = 0; i < n; i++) {
        reverse(words[i].begin(), words[i].end());
        insert(rt, 0, words[i].size(), words[i]);
    }

    int tot = 0;
    for (int i = 0; i < n; i++) {
        if (search(rt, 0, words[i].size(), words[i])) {
            tot += 2;
        }
    }
    return tot;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tccount;
    cin >> tccount;

    for (int i = 1; i <= tccount; i++) {
        cin >> n;
        for (int j = 0; j < n; j++) {
            cin >> words[j];
        }

        // reset
        if (rt) {
            delete rt;
            rt = nullptr;
        }

        cout << "Case #" << i << ": " << solve() << "\n";
    }
}
