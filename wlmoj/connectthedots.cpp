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

#define BAD println("baf"); \
            return 0

const int MN = 1e5 + 1;
int N, M;
vi g[MN];
bool vis[MN], use[MN];
void dfsCheck(int c) {
    if (vis[c]) return;
    vis[c] = true;
    for (int to : g[c])
        dfsCheck(to);
}
bool moreIts() {
    repi(1, N + 1)
        if (sz(g[i]) > 2) return true;
    return false;
}
bool invalid() {
    repi(1, N + 1) {
        if (sz(g[i]) % 2) 
            return true;
    }
    return false;
}
int ctr = 0;
void dfs(int c) {
    if (vis[c] || sz(g[c]) != 2) return;
    vis[c] = true;
    ctr++;
    for (int to : g[c])
        dfs(to);
}
int step() { // return -1 if bad, cycle size otherwise
    // last step
    if (!moreIts()) {
        int cnt = 0;
        repi(1, N + 1) cnt += sz(g[i]) > 0; // remaining nodes
        return cnt;
    }

    fill(vis, vis + N + 1, false);
    int pre = -1;
    repi(1, N + 1) {
        if (use[i] && !vis[i] && sz(g[i]) == 2) {
            ctr = 0;
            dfs(i);
            if (pre == -1) pre = ctr;
            if (ctr != pre) return -1;
        }
    }
    return pre + 1;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(N, M);
    repi(0, M) {
        scn(int, a, b);
        g[a].pb(b);
        g[b].pb(a);
    }

    // multiple components
    dfsCheck(1);
    repi(1, N + 1) {
        if (!vis[i]) {
            BAD;
        }
    }

    // invalid degrees
    fill(use, use + N + 1, true);
    if (invalid()) {
        BAD;
    }

    // logn steps
    vi ans;
    do {
        // get next (step)
        ans.pb(step());
        if (ans.back() == -1) {
            BAD;
        }
        // prune
        uset<int> rem;
        repi(1, N + 1) {
            if (use[i]) {
                if (sz(g[i]) == 2) {
                    rem.insert(i);
                    g[i].clear();
                    g[i].shrink_to_fit();
                    use[i] = false;
                }
            }
        }
        repi(1, N + 1) {
            if (use[i]) {
                vi tmp;
                swap(tmp, g[i]);
                for (auto x : tmp) {
                    if (!rem.count(x))
                        g[i].pb(x);
                }
            }
        }
        // db(ans); dbln;
        // repi(1, N + 1) {
        //     if (use[i]) {
        //         db(i); db(g[i]); dbln;
        //     }
        // }
        // check if valid
        if (invalid()) {
            BAD;
        }
    } while (ans.back());
    ans.pop_back();
    reverse(all(ans));
    for (int x : ans) println(x);
    
    // lol
    int prod=1;
    for (auto x : ans) {
        assert(x>2);
        assert(N%x==0);
        prod*=x;
    }
    assert(prod==N);

    return 0;
}
