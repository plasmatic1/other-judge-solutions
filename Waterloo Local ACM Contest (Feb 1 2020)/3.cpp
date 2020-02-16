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
#define mtup make_tuple
#define pb push_back
#define popcount __builtin_popcount
#define clz __builtin_clz
#define ctz __builtin_ctz
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

const ll MOD = 1e9 + 7;
const int MN = 1e5 + 1, MK = 55, MK2 = 37, MK3 = 19;
int N, K, M,
    val[2][MN];
ll dp[MN][MK2][MK3];

void madd(ll &a, ll b) { a = (a + b) % MOD; }

int solCount(int x, int y, int target) { // how many x+y=target 
    if (x != -1 && y != -1) return x + y == target;
    if (y != -1) swap(x, y); // x is always the defined
    if (x != -1) return 0 <= target - x && target - x <= 9;
    int tot = 0;
    repi(0, 10) tot += 0 <= target - i && target - i <= 9;
    return tot;
}

void recInitial(int r, int c, int tot1, int tot2, int tot3) {
    if (r == 2) {
        if (tot1 == K)
            dp[2][tot2][tot3]++;
        return;
    }

    int nr = r, nc = c + 1;
    if (nc >= 3) nr++, nc = 0;
    if (val[r][c] == -1) {
        repi(0, 10)
            recInitial(nr, nc, tot1 + i, tot2 + (c > 0) * i, tot3 + (c > 1) * i);
    }
    else {
        int cval = val[r][c];
        recInitial(nr, nc, tot1 + cval, tot2 + (c > 0) * cval, tot3 + (c > 1) * cval);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    memset(val, -1, sizeof val);
    scan(N, K, M);
    repi(0, M) {
        int c, r, v;
        scan(c, r, v);
        val[r][c] = v;
    }
    
    if (K >= MK) { // impossible
        println(0);
        return 0;
    }

    // brute force first three
    recInitial(0, 0, 0, 0, 0);

    // dp
    repi(2, N - 1) {
        repj(0, MK2) {
            // precalc
            int req = K - j, solc = solCount(val[0][i + 1], val[1][i + 1], req);
            // db(i), db(j), db(req), dbln;

            // loop
            if (0 <= req && req <= 18) {
                int en = min(j + 1, MK3);
                repk(0, en) {
                    if (!dp[i][j][k]) continue;
                    // db(i); db(j); db(k); db(req); dba("v1", val[0][i + 1]); dba("v2", val[1][i + 1]); db(solc); db(k+req); db(req); db(dp[i][j][k]); dbln;
                    madd(dp[i + 1][k + req][req], (dp[i][j][k] * solc) % MOD);
                }
            }
        }
    }
    ll tot = 0;
    repi(0, MK2) {
        int en = min(i + 1, MK3);
        repj(0, en)
            madd(tot, dp[N - 1][i][j]); //, db(i), db(j), db(dp[N-1][i][j]), dbln;
    }
    println(tot);

    return 0;
}
