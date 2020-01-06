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

vl factor(ll x) {
    ld sqx = sqrt(x);
    vl ret;
    repi(1, sqx + 1) {
        if (x % i == 0) {
            ret.pb(i);
            ret.pb(x / i);
        }
    }

    sort(ret.begin(), ret.end());
    ret.resize(unique(ret.begin(), ret.end()) - ret.begin());
    return ret;
}

ll gcd(ll a, ll b) {
    return b ? a : gcd(b, a % b);
}

const int MN = 1001, MF = 7001; // Max factors
int n,
    dp[MN][MF];
ll k;
struct p {
    int i; ll v;
    Cmplt(p) { return v < o.v; }
} num[MN];
struct {
    int i, j;
} par[MN][MF];
vl kfactors, factors[MF]; // factors for k, factors for the nums

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // input and setup factors
    scan(n, k);
    kfactors = factor(k); // first factor is definitely 1
    int fsz = kfactors.size(); 
    assert(fsz < MF);

    // db(kfactors); dbln;

    factors[0] = {1};
    repi(1, fsz) {
        repj(0, fsz)
            if (kfactors[i] % kfactors[j] == 0)
                factors[i].pb(j);
        reverse(factors[i].begin(), factors[i].end());
    }

    // edge case
    if (k == 1) {
        print("1\n1\n");
        return 0;
    }

    // input nums
    repi(1, n + 1) {
        scan(num[i].v);
        // num[i].v = gcd(num[i].v, k);
        num[i].i = i;
    }
    sort(num + 1, num + n + 1);

    // dp
    memset(dp, 0x3f, sizeof dp);
    repi(1, n + 1) { 
        dp[0][0] = 0LL;
        repj(1, fsz) {
            mina(dp[i][j], dp[i - 1][j]);
            par[i][j] = {i - 1, j};
            for (auto from : factors[j]) {
                ll req = kfactors[j] / kfactors[from];
                if (req > num[i].v) break;

                if (num[i].v % req == 0) {
                    // dblb("tryjump"); db(i); db(j); db(l); db(factors[j]); db(factors[l]); dbln;
                    int alt = dp[i - 1][from] + 1;
                    if (alt < dp[i][j]) {
                        dp[i][j] = alt;
                        par[i][j] = {i - 1, from};
                    }
                }
            }
            
            // db(i); db(j); db(factors[j]); db(dp[i][j]); dbln;
        }
    }

    if (dp[n][fsz - 1] == INF) {
        println(-1);
        return 0;
    }

    // output and backtrack
    println(dp[n][fsz - 1]);

    vi seq;
    int ci = n, cj = fsz - 1;
    while (ci > 0 && cj > 0) {
        auto cpar = par[ci][cj];
        // db(ci); db(cj); dbln;

        if (cj > cpar.j)
            seq.pb(num[ci].i);

        ci = cpar.i;
        cj = cpar.j;
    }
    sort(seq.begin(), seq.end());
    for (auto x : seq)
        print(x, ' ');
    print('\n');

    return 0;
}
