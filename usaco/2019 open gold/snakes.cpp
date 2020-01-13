#pragma region
#include <bits/stdc++.h>
using namespace std;
// Common Type shorteners and int128
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template <typename T>
using vec = vector<T>;
template <typename K, typename V>
using umap = unordered_map<K, V>;
template <typename K>
using uset = unordered_set<K>;
using vi = vec<int>;
using vl = vec<ll>;
using vpi = vec<pii>;
using vpl = vec<pll>;
#ifdef __SIZEOF_INT128__
using int128 = __int128_t;
using uint128 = __uint128_t;
#endif
template <typename I>
string intStr(I x) {
    string ret;
    while (x > 0) {
        ret += (x % 10) + '0';
        x /= 10;
    }
    reverse(ret.begin(), ret.end());
    return ret;
} // Int to string
// Shorthand Macros
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define mpr make_pair
#define pb push_back
#define popcount __builtin_popcount
#define clz __builtin_clz
#define ctz __builtin_ctz
// Shorthand Function Macros
#define sz(x) ((int)((x).size()))
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for (__typeof(a) i = a; i < b; i++)
#define reprev(i, a, b) for (__typeof(a) i = a; i > b; i--)
#define repi(a, b) rep(i, a, b)
#define repj(a, b) rep(j, a, b)
#define repk(a, b) rep(k, a, b)
#define Cmplt(type) bool operator<(const type &o) const
#define Cmpgt(type) bool operator>(const type &o) const
#define Cmpfn(name, type) bool name(const type &a, const type &b)
#define Inop(type) istream &operator>>(istream &in, type &o)
#define Outop(type) ostream &operator<<(ostream &out, type o)
#define Pow2(x) (1LL << (x))
#define scn(type, ...) \
    type __VA_ARGS__;  \
    scan(__VA_ARGS__) // scn -> Short for SCan New
// Shorthand Functions
template <typename T>
inline void maxa(T &st, T v) { st = max(st, v); }
template <typename T>
inline void mina(T &st, T v) { st = min(st, v); }
inline void setprec(ostream &out, int prec) { out << setprecision(prec) << fixed; }
// Out operators and printing for arrays and vectors
template <typename T>
ostream &operator<<(ostream &out, vector<T> iter) {
    out << "[";
    for (auto t : iter) {
        out << t << ", ";
    }
    out << "]";
    return out;
}
template <typename T>
string arrayStr(T *arr, int sz) {
    string ret = "[";
    for (int i = 0; i < sz; i++) {
        ret += to_string(arr[i]) + ", ";
    }
    return ret + "]";
}
template <typename T>
void printArray(T *arr, int sz) {
    for (int i = 0; i < sz; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}
// I/O Operations
inline void scan() {}
template <typename F, typename... R>
inline void scan(F &f, R &... r) {
    cin >> f;
    scan(r...);
}
template <typename F>
inline void println(F t) { cout << t << '\n'; }
template <typename F, typename... R>
inline void println(F f, R... r) {
    cout << f << " ";
    println(r...);
}
inline void print() {}
template <typename F, typename... R>
inline void print(F f, R... r) {
    cout << f;
    print(r...);
}
// Debugging
#define db(x) cout << (#x) << ": " << x << ", "
#define dblb(s) cout << "[" << s << "] "
#define dbbin(x, n) cout << (#x) << ": " << bitset<n>(x) << ", "
#define dbarr(x, n) cout << (#x) << ": " << arrayStr((x), (n)) << ", "
#define dbln cout << endl;
#pragma endregion

const int MN = 401;
ll val[MN], pmin[MN], dp[MN][MN][MN];
int N, K;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(N, K);
    repi(1, N + 1)
        scan(val[i]);
    memset(dp, 0x3f, sizeof dp);
#define RPM() memset(pmin, 0x3f, sizeof pmin)

    RPM();
    pmin[0] = 0;
    repi(1, N + 1)
        dp[0][i][0] = 0;

    repi(1, N + 1) {
        repj(1, N + 1) {
            if (val[j] < val[i])
                continue;
            repk(0, K + 1) {
                if (k > 0)
                    dp[i][j][k] = min(dp[i][j][k], pmin[k - 1]);
                dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k]);
                dp[i][j][k] += val[j] - val[i];
            }
        }
        RPM();
        repj(1, N + 1)
            repk(0, K + 1)
                pmin[k] = min(pmin[k], dp[i][j][k]);
    }

    ll mn = LLINF;
    repi(1, N + 1)
        repj(1, K + 1)
            mn = min(mn, dp[N][i][j]);
    println(mn);

    return 0;
}
