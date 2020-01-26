#pragma region
#include <bits/stdc++.h>
using namespace std;
// Common Type shorteners and int128
using ll = long long; using ull = unsigned long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<ll, ll>;
template <typename T> using vec = vector<T>;
template <typename K, typename V> using umap = unordered_map<K, V>; template <typename K> using uset = unordered_set<K>;
using vi = vec<int>; using vl = vec<ll>; using vpi = vec<pii>; using vpl = vec<pll>;
#ifdef __SIZEOF_INT128__
using int128 = __int128_t; using uint128 = __uint128_t;
#endif
template<typename I> string intStr(I x) { string ret; while (x > 0) { ret += (x % 10) + '0'; x /= 10; } reverse(ret.begin(), ret.end()); return ret; } // Int to string
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
#define Inop(type) istream& operator>>(istream& in, type &o)
#define Outop(type) ostream& operator<<(ostream& out, type o)
#define Pow2(x) (1LL << (x))
#define scn(type, ...) type __VA_ARGS__; scan(__VA_ARGS__) // scn -> Short for SCan New
// Shorthand Functions
template<typename T> inline void maxa(T& st, T v) { st = max(st, v); }
template<typename T> inline void mina(T& st, T v) { st = min(st, v); }
inline void setprec(ostream& out, int prec) { out << setprecision(prec) << fixed; }
// Out operators and printing for arrays and vectors
template <typename T> ostream& operator<<(ostream& out,vector<T> iter){out<<"[";for(auto t:iter){out<<t<<", ";}out<<"]";return out;}
template <typename T> string arrayStr(T *arr,int sz){string ret = "[";for(int i=0;i<sz;i++){ret+=to_string(arr[i])+", "; } return ret + "]";}
template <typename T> void printArray(T *arr,int sz){for(int i=0;i<sz;i++){cout<<arr[i]<<" "; } cout<<"\n";}
// I/O Operations
inline void scan(){}
template<typename F, typename... R> inline void scan(F &f,R&... r){cin>>f;scan(r...);}
template <typename F> inline void println(F t){cout<<t<<'\n';}
template<typename F, typename... R> inline void println(F f,R... r){cout<<f<<" ";println(r...);}
inline void print(){}
template<typename F, typename... R> inline void print(F f,R... r){cout<<f;print(r...);}
// Debugging
#define db(x) cout << (#x) << ": " << x << ", "
#define dblb(s) cout << "[" << s << "] "
#define dbbin(x, n) cout << (#x) << ": " << bitset<n>(x) << ", "
#define dbarr(x, n) cout << (#x) << ": " << arrayStr((x), (n)) << ", "
#define dbln cout << endl;
#pragma endregion

struct Qu {
    int i, a, b;
};

const int MN = 1e5 + 1, MN2 = MN * 2, LG = 17;
int n, q,
    ans[MN], val[MN];
vec<Qu> qus[MN];
vec<int> g[MN], vals[MN];

// lca 
int lv[MN], tb[LG][MN];
void dfslca(int c, int p) {
    lv[c] = p == -1 ? 0 : lv[p] + 1;
    tb[0][c] = p;
    for (int to : g[c])
        if (to ^ p)
            dfslca(to, c);
}
void makelca() {
    repi(1, LG) {
        repj(1, n + 1) {
            int pp = tb[i - 1][j];
            tb[i][j] = pp == -1 ? -1 : tb[i - 1][pp];
        }
    }
}
int lca(int a, int b) {
    if (a == b) return a;
    if (lv[a] > lv[b]) swap(a, b);
    int delta = lv[b] - lv[a];
    repi(0, LG)
        if ((delta >> i) & 1)
            b = tb[i][b];
    if (a == b) return a;
    reprev(i, LG - 1, -1) 
        if (tb[i][a] != tb[i][b])
            a = tb[i][a], b = tb[i][b];
    return tb[0][a];
}

// ETT
int tourIdx = 0,
    first[MN], last[MN], bit[MN2];
void dfsett(int c, int p) {
    first[c] = ++tourIdx;
    for (int to : g[c])
        if (to ^ p)
            dfsett(to, c);
    last[c] = ++tourIdx;
}
void add(int x, int v) {
    for (; x < MN2; x += x & -x)
        bit[x] += v;
}
int sum(int x) {
    int sum = 0;
    for (; x; x -= x & -x)
        sum += bit[x];
    return sum;
}
int qpath(int a, int b, int clr) {
    int lcav = lca(a, b);
    // db(a); db(b); db(lcav); dbln;
    return sum(first[a]) + sum(first[b]) - 2 * sum(first[lcav]) + (val[lcav] == clr);
}
int bottom(int a, int b) { // gets the bottom node out of two nodes (in a single edge)
    return lv[a] > lv[b] ? a : b;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // input
    scan(n, q);
    repi(1, n + 1) {
        scn(int, c);
        vals[c].pb(i);
        val[i] = c;
    }
    repi(0, n - 1) {
        scn(int, a, b);
        g[a].pb(b);
        g[b].pb(a);
    }
    repi(0, q) {
        scn(int, a, b, c);
        qus[c].pb({i, a, b});
    }

    // build data structure
    memset(tb, -1, sizeof tb);
    dfslca(1, -1);
    makelca();
    dfsett(1, -1);

    // offline
    repi(1, n + 1) {
        for (auto v : vals[i]) {
            add(first[v], 1);
            add(last[v], -1);
        }

        for (auto qu : qus[i])
            ans[qu.i] = qpath(qu.a, qu.b, i) > 0;
        
        for (auto v : vals[i]) {
            add(first[v], -1);
            add(last[v], 1);
        }
    }

    // print
    repi(0, q)
        print(ans[i]);
    print('\n');

    return 0;
}
