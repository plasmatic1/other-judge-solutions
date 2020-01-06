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

const int MN = 1e5 + 1;
int n, m,
    cnt[MN];
umap<int, ll> g[MN];
deque<pair<int, int>> dq;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, m);

    repi(0, m) {
        scn(int, a, b, w);
        g[a][b] += w;

        dq.pb(mpr(a, b));
    }

    while (!dq.empty()) {
        auto cur = dq.front(); dq.pop_front();
        int a = cur.first, b = cur.second; // a to b

        auto ptr = g[a].find(b);
        if (ptr == g[a].end() || a == b || ptr->second == 0LL) {
            if (ptr != g[a].end()) g[a].erase(ptr);
            continue;
        }

        ll w1 = g[a][b];

        // anything that ends in b
        vi rem;
        for (auto ed : g[b]) {
            int c = ed.first;
            ll z = min(w1, ed.second);

            if (b == c) {
                rem.pb(c);
                continue;
            }

            // db(a); db(b); db(c); dbln;

            w1 -= z;
            if (ed.second == z)
                rem.pb(c);
            else
                g[b][c] -= z;
            
            g[a][c] += z;
            dq.pb(mpr(a, c));

            if (w1 == 0)
                break;
        }
        
        for (auto x : rem)
            g[b].erase(g[b].find(x));

        g[a][b] = w1;
        if (w1 == 0)
            g[a].erase(g[a].find(b));
    }

    vec<tuple<int, int, ll>> ans;
    repi(1, n + 1) {
        for (auto ed : g[i]) {
            if (ed.second == 0LL || i == ed.first)
                continue;
            ans.pb(make_tuple(i, ed.first, ed.second));
        }
    }

    println(ans.size());
    for (auto tup : ans) {
        int a, b; ll w;
        tie(a, b, w) = tup;

        println(a, b, w);
    }

    return 0;
}
