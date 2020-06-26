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

struct PS {
    int i, j, k, ins;
};

const int MN = 1e5 + 1, B = 4;
int N, a, b, c;
PS dp[MN][B][B][B];
string ins[MN];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(N, a, b, c);

    // Init
    repi(0, N + 1)
        repj(0, B)
            repk(0, B)
                rep(l, 0, B)
                    dp[i][j][k][l] = {-1, -1, -1, -1};

    // Do DP
    memset(dp, -1, sizeof dp);
    dp[0][min(a, B - 1)][min(b, B - 1)][min(c, B - 1)] = {-2, -2, -2, -1};
    repi(0, N) {
        scan(ins[i + 1]);

        repj(0, B) {
            repk(0, B) {
                rep(l, 0, B) {
                    if (dp[i][j][k][l].i == -1) continue;
                    // db(i); db(j); db(k); db(l); db(dp[i][j][k][l]); db(ins[i + 1]); dbln;

                    #define INC(x) min(B - 1, x + 1)
                    #define DEC(x) x - 1

                    PS z0 = {j, k, l, 0}, z1 = {j, k, l, 1}, z2 = {j, k, l, 2};
                    if (ins[i + 1] == "AB") {
                        if (k > 0) dp[i + 1][INC(j)][DEC(k)][l] = z0;
                        if (j > 0) dp[i + 1][DEC(j)][INC(k)][l] = z1;
                    }
                    else if (ins[i + 1] == "BC") {
                        if (l > 0) dp[i + 1][j][INC(k)][DEC(l)] = z1;
                        if (k > 0) dp[i + 1][j][DEC(k)][INC(l)] = z2;
                    }
                    else {
                        if (l > 0) dp[i + 1][INC(j)][k][DEC(l)] = z0;
                        if (j > 0) dp[i + 1][DEC(j)][k][INC(l)] = z2;
                    }

                    #undef INC
                    #undef DEC
                }
            }
        }
    }

    // Output
    repi(0, B) {
        repj(0, B) {
            repk(0, B) {
                if (dp[N][i][j][k].i != -1) {
                    println("Yes");
                    vec<char> ans;
                    int cur = N, ci = i, cj = j, ck = k;
                    while (cur > 0) {
                        auto pre = dp[cur][ci][cj][ck];
                        ans.pb(char('A' + pre.ins));

                        // db(cur); db(ci); db(cj); db(ck); db(intIns); dbln;

                        ci = pre.i;
                        cj = pre.j;
                        ck = pre.k;
                        cur--;
                    }

                    for (auto it = ans.rbegin(); it != ans.rend(); it++)
                        println(*it);
                    return 0;
                }
            }
        }
    }
    println("No");

    return 0;
}
