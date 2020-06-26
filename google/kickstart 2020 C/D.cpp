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
template<typename T> inline int sz(const T &x) { return x.size(); }
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

template <typename T>
struct BIT {
    virtual T Default() = 0;
    virtual T Op(T &a, T &b) = 0;
    int N;
    vector<T> bit;
    void init(int n) { N = n; bit.assign(N + 1, 0LL); }
    void update(int x, T v) { for (; x <= N; x += x & - x) bit[x] = Op(bit[x], v); }
    T query(int x) { T sum = Default(); for (; x; x -= x & -x) sum = Op(sum, bit[x]); return sum; }
};
struct Bit : public BIT<ll> {
    ll Default() { return 0; }
    ll Op(ll &a, ll &b) { return a + b; }
};

const int MN = 2e5 + 1;
int N, Q;
ll val[MN];

Bit poly[2], sumb[2];
// int nxtEven(int x) { return x + x % 2; }
// int nxtOdd(int x) { return x + !(x % 2); }
// int preEven(int x) { return x - x % 2; }
// int preOdd(int x) { return x - !(x % 2); }

void upd(ll i, ll prevv, ll v) {
    bool p = i & 1;
    poly[p].update(i, i * (v - prevv));
    sumb[p].update(i, v - prevv);
}

void solve() {
    repi(0, 2) poly[i].init(N);
    repi(0, 2) sumb[i].init(N);

    repi(1, N + 1)
        upd(i, 0, val[i]);

    ll ans = 0;
    while (Q--) {
        scn(char, T);
        scn(ll, x, y);
        if (T == 'U') {
            upd(x, val[x], y);
            val[x] = y;
        }
        else {
            ll cans = 0;
            bool p = x & 1;
            cans += poly[p].query(y) - poly[p].query(x - 1);
            // db(poly[p].query(y) - poly[p].query(x - 1)); dbln;
            cans -= (x - 1) * (sumb[p].query(y) - sumb[p].query(x - 1));
            // db(sumb[p].query(y) - sumb[p].query(x - 1)); dbln;
            cans -= poly[!p].query(y) - poly[!p].query(x - 1);
            cans += (x - 1) * (sumb[!p].query(y) - sumb[!p].query(x - 1));
            // println(cans);
            ans += cans;
        }
    }
    println(ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T; cin >> T;
    int caseno = 1;
    while (T--) {
        // Input
        scan(N, Q);
        repi(1, N + 1) scan(val[i]);

        // Reset
        

        cout << "Case #" << (caseno++) << ": ";
        solve();
    }
}