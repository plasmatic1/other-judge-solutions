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
#define rep(i, a, b) for (auto i = a; i < b; i++)
#define reprev(i, a, b) for (auto i = a; i > b; i--)
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

/*
DP[i][j]
i -> Subtree of node #
j -> Taken nodes of subset at least J nodes away
*/

const int MN = 201;
int n, k,
    val[MN], dp[MN][MN];
vi g[MN];

void rec(int cur, int par) {
    // first do adj
    for (int adj : g[cur]) {
        if (adj ^ par)
            rec(adj, cur);
    }

    // calc dp
    repi(0, n) {
        if (i == 0) {
            dp[cur][0] = val[cur];
            for (int adj : g[cur]) {
                if (adj == par) continue;
                dp[cur][0] += dp[adj][k];
            }
        }
        else {
            for (int adj : g[cur]) {
                if (adj == par) continue;
                int cbest = dp[adj][i - 1];
                for (int adj2 : g[cur]) {
                    if (adj == adj2 || adj == par) continue;
                    // db(cbest); db(adj); db(adj2); db(i); db(max(i - 1, k - i)); dbln;
                    cbest += dp[adj2][max(i - 1, k - i)];
                }
                maxa(dp[cur][i], cbest);
            }
        }
    }

    // max
    reprev(i, n - 1, -1) {
        maxa(dp[cur][i], dp[cur][i + 1]);
        // db(cur); db(i); db(dp[cur][i]); dbln;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, k);

    repi(1, n + 1) {
        scan(val[i]);
    }

    repi(1, n) {
        int a, b;
        scan(a, b);
        g[a].pb(b);
        g[b].pb(a);
    }

    rec(1, -1);
    println(dp[1][0]);

    return 0;
}
