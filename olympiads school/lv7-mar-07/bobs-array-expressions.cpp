// ./bobs-array-expressions.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const ll MOD = 1e9 + 7;

const int MN = 5e4 + 1, MM = 10;
int N, M, SN;
vector<int> A[MM];
string s;

int _op(int a, int b, int op) {
    switch (op) {
        case 0: return min(a, b);
        default: return max(a, b);
    }
    return -1;
}
void opto(vector<int> &a, vector<int> &b, bool op) {
    for (auto i = 0; i < (int)a.size(); i++)
        a[i] = _op(a[i], b[i], op);
}

pair<int, vector<int>> solve(int l) {
    vector<int> cur;
    int preop = -1;
    auto apply = [&] (vector<int> &v) {
        if (cur.empty()) cur = v;
        else opto(cur, v, preop);
    };
    while (s[l] != ')') {
        if (s[l] == '(') {
            auto sub = solve(l+1);
            apply(sub.second);
            l = sub.first+1;
        }
        else if (s[l] == '<') {
            preop = 0;
            l++;
        }
        else if (s[l] == '>') {
            preop = 1;
            l++;
        }
        else if ('0' <= s[l] && s[l] <= '9') {
            apply(A[s[l] - '0']);
            l++;
        }
        else if (s[l] == '?') assert(0);
        else assert(0);
    }
    return {l, cur};
}

string __(vector<ll> v) {
    string res = "[";
    for (auto x : v) res += to_string(x) + ", ";
    return res + "]";
}
string __(vector<int> v) {
    string res = "[";
    for (auto x : v) res += to_string(x) + ", ";
    return res + "]";
}
#define _(x) (__(x).c_str())

pair<int, vector<ll>> solve2(int ROW, int l, int SZ) {
    vector<ll> cur;
    int preop = -1, _st = l;
    auto apply = [&] (vector<ll> &v) {
        if (cur.empty()) return void(cur = v);

        vector<ll> alt(SZ);
        if (preop == 0 || preop == 2) {
            for (auto i = 0; i < SZ; i++) { // at most, preop = 0
                for (auto j = 0; j < SZ; j++) {
                    int to = min(i, j);
                    alt[to] = (alt[to] + cur[i] * v[j]) % MOD;
                }
            }
        }
        if (preop == 1 || preop == 2) {
            for (auto i = 0; i < SZ; i++) { // at least, preop = 1
                for (auto j = 0; j < SZ; j++) {
                    int to = max(i, j);
                    alt[to] = (alt[to] + cur[i] * v[j]) % MOD;
                }
            }
        }
        cur = alt;
    };
    while (s[l] != ')') {
        // printf("l=%d cur=%s\n", l,_(cur));
        if (s[l] == '(') {
            auto sub = solve2(ROW, l+1, SZ);
            apply(sub.second);
            l = sub.first+1;
        }
        else if (s[l] == '<') {
            preop = 0;
            l++;
        }
        else if (s[l] == '>') {
            preop = 1;
            l++;
        }
        else if ('0' <= s[l] && s[l] <= '9') {
            vector<ll> oth(SZ);
            oth[A[s[l] - '0'][ROW]] = 1;
            // printf("setoth=%s, arrNo=%c\n", _(oth), s[l]);
            apply(oth);
            l++;
        }
        else if (s[l] == '?') {
            preop = 2;
            l++;
        }
        else assert(0);
    }
    // printf("from=%d to=%d res=%s\n", _st,l,_(cur));
    return {l, cur};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (auto i = 0; i < M; i++) {
        A[i].resize(N);
        for (auto &x : A[i]) cin >> x;
    }
    cin >> s;
    s = "(" + s + ")";
    SN = s.length();
    bool hasq = false;
    for (auto &c : s) hasq |= c == '?';
    
    if (hasq) {
        ll ans = 0;
        for (auto i = 0; i < N; i++) {
            vector<int> rnk;
            for (auto j = 0; j < M; j++)
                rnk.push_back(A[j][i]);
            sort(rnk.begin(), rnk.end());
            rnk.resize(unique(rnk.begin(), rnk.end()) - rnk.begin());

            auto get = [&] (int a) {
                return 1 * (lower_bound(rnk.begin(), rnk.end(), a) - rnk.begin());
            };
            for (auto j = 0; j < M; j++)
                A[j][i] = get(A[j][i]);

            // printf("IDX=%d, compress=%s\n", i, _(rnk));
            auto res = solve2(i, 1, rnk.size()).second;
            for (auto j = 0; j < (int)rnk.size(); j++) {
                ans += res[j] * rnk[j] % MOD;
                ans %= MOD;
            }
        }

        cout << ans << '\n';
        return 0;
    }

    auto res = solve(1).second;
    ll ans = 0;
    for (auto x : res) ans = (ans + x) % MOD;
    cout << ans << '\n';

    return 0;
}
