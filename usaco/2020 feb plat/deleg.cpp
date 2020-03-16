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

void init_file_io() {
    const string PROBLEM_ID = "deleg";
    freopen((PROBLEM_ID + ".in").c_str(), "r", stdin);
    freopen((PROBLEM_ID + ".out").c_str(), "w", stdout);
}

const int MN = 1e5 + 1;
int N;
vi g[MN];

// dp stuff
int dp[MN];
bool dfs(int c, int p, int K) {
    vi len;
    for (int to : g[c]) {
        if (to ^ p) {
            if (!dfs(to, c, K))
                return false;
            len.pb(dp[to] + 1);
        }
    }
    if (len.empty()) { // leaf
        dp[c] = 0;
        return true;
    }

    // dp stuff
    sort(all(len));
    multiset<int> lenSet(all(len));
    int badc = 0, sz = len.size();
    vpi pairs;
    repi(0, sz) {
        auto cptr = lenSet.find(len[i]);
        if (cptr == lenSet.end()) continue; // skip, this one has already been removed
        lenSet.erase(cptr);
        // db(i); dbln;
        
        if (len[i] < K) {
            auto ptr = lenSet.lower_bound(K - len[i]);
            if (ptr == lenSet.end()) {
                badc++;
                if (badc >= 2) return false; // impossible
                pairs.emplace_back(len[i], -1);
            }
            else {
                pairs.emplace_back(len[i], *ptr);
                lenSet.erase(ptr);
            }
        }
        else
            pairs.emplace_back(len[i], -1);
    }

    // set dp[c]
    dp[c] = 0;
    for (auto pp : pairs) {
        if (pp.second == -1) { // single.  If badc>0, then there can't be any things that are >=K as they would've been matched up already
            maxa(dp[c], pp.first);
        }
        else {
            assert(pp.first <= pp.second); // always should be the case
            if (badc == 0 && p != -1 && pp.second >= K) // can't do this if it's the root!.  Additionally, if badc>0, then that one must be taken, and this cannot be taken
                maxa(dp[c], pp.first);
        }
    }

    return true;
}

// check function
bool works(int K) {
    fill(dp, dp + N + 1, 0);
    bool work = dfs(1, -1, K);
    return work && (dp[1] == 0 || dp[1] >= K); // either everything is self contained or the one thing that's going up is >= K
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef LOCAL
    init_file_io();
#endif

    scan(N);
    repi(1, N) {
        int a, b;
        scan(a, b);
        g[a].pb(b);
        g[b].pb(a);
    }    

    int l = 1, r = N + 1;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        bool wk = works(mid);

        if (wk)
            l = mid;
        else
            r = mid;
    }
    println(l);

    // db(works(4)); dbln;
    // dbarr(dp, N + 1); dbln;
}