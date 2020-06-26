#pragma region
#include "bits/stdc++.h"
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
#define mtup make_tuple
#define pb push_back
#define popcount __builtin_popcount
#define clz __builtin_clz
#define ctz __builtin_ctz
#define popcountll __builtin_popcountll
#define clzll __builtin_clzll
#define ctzll __builtin_ctzll
#define finline __attribute__((always_inline))
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
#define db(x) cout << (#x) << ": " << (x) << ", "
#define dblb(s) cout << "[" << (s) << "] "
#define dba(alias, x) cout << (alias) << ": " << (x) << ", "
template<typename F> inline string __generic_tostring(F f) { stringstream ss; ss << f; return ss.str(); }
template<typename F> inline string __join_comma(F f) {return __generic_tostring(f);}
template<typename F, typename... R> string __join_comma(F f, R... r) { return __generic_tostring(f) + ", " + __join_comma(r...); }
#define dbp(alias, ...) cout << (alias) << ": (" << __join_comma(__VA_ARGS__) << "), "
#define dbbin(x, n) cout << (#x) << ": " << bitset<n>(x) << ", "
#define dbarr(x, n) cout << (#x) << ": " << arrayStr((x), (n)) << ", "
#define dbln cout << endl;
#pragma endregion

const int MAXB = 29;
struct Trie {
    int mx, val, ch[2];
};
int nodeCtr = 1;
Trie trie[4000000];
int make() {
    Trie &r = trie[nodeCtr];
    r.mx = r.ch[0] = r.ch[1] = 0;
    r.val = -1;
    return nodeCtr++;
}
void ins(Trie &r, int lev, int v, int dep) {
    maxa(r.mx, dep);
    if (lev < 0) {
        r.val = v;
        return;
    }
    bool bit = (v >> lev) & 1;
    int &nxt = r.ch[bit];
    if (!nxt) nxt = make();
    ins(trie[nxt], lev - 1, v, dep);
}
int search(Trie &r, int lev, int query, int req) {
    if (lev < 0)
        return r.val;
    bool bit = (query >> lev) & 1;
    if (r.ch[!bit] && trie[r.ch[!bit]].mx >= req)
        return search(trie[r.ch[!bit]], lev - 1, query, req);
    else if (r.ch[bit] && trie[r.ch[bit]].mx >= req)
        return search(trie[r.ch[bit]], lev - 1, query, req);
    return -1;
}

const int MN = 1e5 + 1;
int N, K,
    val[MN];
vi g[MN];

// centroid
int sz[MN];
bool block[MN];
int gsz(int c, int p) {
    sz[c] = 1;
    for (int to : g[c])
        if (to != p && !block[to])
            sz[c] += gsz(to, c);
    return sz[c];
}
int gcent(int c, int p, int H) {
    for (int to : g[c])
        if (to != p && !block[to] && sz[to] > H)
            return gcent(to, c, H);
    return c;
}
// dfs stuff
int root;
// qtype=0 -> query, qtype=1 -> update
ll dfs(int c, int p, int dep, ll v, int qtype) {
    ll res = -1;
    if (qtype == 0) {
        int oth = search(trie[root], MAXB, v, K - dep); // CHECK
        if (oth != -1)
            maxa(res, v ^ oth);
    }
    else if (qtype == 1) {
        ins(trie[root], MAXB, v, dep);
        if (dep >= K)
            maxa(res, v);
    }
    for (int to : g[c])
        if (to != p && !block[to])
            maxa(res, dfs(to, c, dep + 1, v ^ val[to], qtype));
    return res;
}
// using VIT = vi::iterator;
ll decomp(int c) {
    gsz(c, -1);
    if (sz[c] == 1) return -1;

    // ds bashing
    int cent = gcent(c, -1, sz[c] / 2);
    ll res = -1;

    nodeCtr = 1;
    root = make();
    for (int to : g[cent]) {
        if (!block[to]) {
            maxa(res, dfs(to, cent, 1, val[to], 0));
            maxa(res, dfs(to, cent, 1, val[cent] ^ val[to], 1));
        }
    }

    // propagate
    block[cent] = true;
    for (int to : g[cent])
        if (!block[to])
            maxa(res, decomp(to));
    return res;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(N, K);
    repi(1, N + 1) scan(val[i]);    
    repi(1, N) {
        scn(int, a, b);
        g[a].pb(b);
        g[b].pb(a);
    }

    ll ans = decomp(1);
    println(ans);

    return 0;
}
