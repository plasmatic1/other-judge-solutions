/*
ID: moses1
LANG: C++14
TASK: wormhole
*/
#pragma GCC optimize("Ofast")
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

template <typename T, typename U> istream& operator>>(istream& in, pair<T, U> &p) {
    in >> p.first >> p.second;
    return in;
}

#define repl(a, b) rep(l, a, b)
#define repm(a, b) rep(m, a, b)

template <typename T> void rdvec(vec<T> &v) { int sz = v.size(); repi(0, sz) scan(v[i]); }
#define ri(a) scn(int, a)
#define ri2(a) scn(int, a, b)
#define ri3(a) scn(int, a, b, c)

void init_file_io() {
    const string wormhole = "wormhole";
    freopen((wormhole + ".in").c_str(), "r", stdin);
    freopen((wormhole + ".out").c_str(), "w", stdout);
}

int fact(int x) {
    if (x <= 1) return 1;
    return x * fact(x - 1);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef LOCAL
    init_file_io();
#endif

    ri(N);
    vpi p(N);
    rdvec(p);
    sort(all(p));
    
    vi nxt(N, -1);
    repi(0, N) {
        repj(i + 1, N) {
            if (p[i].second == p[j].second) {
                nxt[i] = j;
                break;
            }
        }
    }

    // int end = (1 << N) - 1, tot = 0;
    int tot = 0;
    vi use(N), jmp(N);
    function<bool(int)> noloop = [&] (int start) {
        repi(0, 25) {
            int to = nxt[start];
            if (to == -1) return true;
            start = jmp[to];
        }
        return false;
    };

    // uset<string> used;
    function<void(int, int)> rec = [&] (int t, int st) {
        if (t > N / 2) {
            bool wk = false;
            repi(0, N)
                wk |= !noloop(i);
            tot += wk;
        //     db(use), dbln;
            return;
        }
        repi(st, N) {
            if (use[i]) continue;
            repj(i + 1, N) {
                if (use[j]) continue;
                if (i == j) continue;
                // db(t); db(i); db(j); db(use); dbln;
                use[i] = t; use[j] = t;
                jmp[i] = j; jmp[j] = i;
                rec(t + 1, i + 1);
                use[i] = 0; use[j] = 0;
            }
        }
    };
    rec(1, 0);
    // tot /= fact(N / 2);
    println(tot);

    return 0;
}
