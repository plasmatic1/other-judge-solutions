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

const int MN = 1e5 + 1;
int N, M;
vec<vi> dis;
vec<vl> val;
vpi nxt;
set<int> leftH[MN], leftV[MN];

#define good(x) (abs(*(x)) < INF)

void run(int cdis) {
    // dblb("going for cdis"); db(cdis); dbln;
    vpi tmp, rem; swap(tmp, nxt);
    for (const auto &p : tmp) {
        int x = p.first, y = p.second;
        auto xptr = leftH[x].lower_bound(y), xptr2 = xptr, yptr = leftV[y].lower_bound(x), yptr2 = yptr;
        // db(cdis); db(x); db(y); db(*xptr); db(*yptr); dbln;
        if (*xptr != y || *yptr != x) 
            continue;
        yptr2++; xptr2++; xptr--; yptr--;
        // db(*xptr); db(*xptr2); db(*yptr); db(*yptr2); dbln;
        int osum = 0, ocnt = 0;

        if (good(xptr)) {
            osum += val[x][*xptr];
            ocnt++;
        }
        if (good(xptr2)) {
            osum += val[x][*xptr2];
            ocnt++;
        }
        if (good(yptr)) {
            osum += val[*yptr][y];
            ocnt++;
        }
        if (good(yptr2)) {
            osum += val[*yptr2][y];
            ocnt++;
        }

        if (val[x][y] * ocnt < osum) {
            // dblb("done"); db(x); db(y); dbln;
            dis[x][y] = cdis;
            rem.emplace_back(x, y);
            if (good(xptr)) nxt.emplace_back(x, *xptr);
            if (good(xptr2)) nxt.emplace_back(x, *xptr2);
            if (good(yptr)) nxt.emplace_back(*yptr, y);
            if (good(yptr2)) nxt.emplace_back(*yptr2, y);
        }
    }
    for (const auto &p : rem) {
        auto ptr = leftH[p.first].find(p.second);
        if (ptr != leftH[p.first].end())
            leftH[p.first].erase(ptr);
        auto ptr2 = leftV[p.second].find(p.first);
        if (ptr2 != leftV[p.second].end())
            leftV[p.second].erase(ptr2);
    }
}

void solve() {
    dis.assign(N, vi(M, INF));

    repi(0, N) {
        repj(0, M) {
            nxt.emplace_back(i, j);
            leftH[i].insert(j);
            leftV[j].insert(i);
        }
        leftH[i].insert(-INF);
        leftH[i].insert(INF);
    }
    repi(0, M) {
        leftV[i].insert(-INF);
        leftV[i].insert(INF);
    }

    int disCtr = 1;
    while (!nxt.empty())
        run(disCtr++);
    
    int rounds = 1;
    repi(0, N)
        repj(0, M)
            if (dis[i][j] != INF)
                maxa(rounds, dis[i][j] + 1);
    if (rounds == INF) rounds = 1;
    // db(rounds); dbln;
    ll tot = 0;
    repi(0, N) {
        repj(0, M) {
            tot += min(rounds, dis[i][j]) * ll(val[i][j]);
        }
    }
    println(tot);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T; cin >> T;
    int caseno = 1;
    while (T--) {
        // Input
        scan(N, M);
        val.resize(N);
        repi(0, N) {
            val[i].resize(M);
            repj(0, M) {
                scan(val[i][j]);
            }
        }

        // Reset
        

        cout << "Case #" << caseno << ": ";
        solve();
        caseno++;
        repi(0, N)
            leftH[i].clear();
        repi(0, M)
            leftV[i].clear();
    }
}