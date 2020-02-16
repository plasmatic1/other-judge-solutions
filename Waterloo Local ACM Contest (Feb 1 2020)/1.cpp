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

const int MN = 21;
int T, R, C;
char igrid[MN][MN], ogrid[MN][MN];
struct cell {
    int type; // 0 -> soil, 1 -> Soil+grass, 2 -> Soil+carcass
    int wait;
} grid[MN][MN];
map<pii, int> animals[2]; // 0 -> sheep, 1 -> wolf

void runTurn() {
    // move animals
    map<pii, int> mv;
    for (auto x : animals[0]) {
        auto pos = x.first;
        if (pos.first == R - 1) pos.first = 0;
        else pos.first++;
        mv[pos] = x.second - 1;
    }
    animals[0] = mv;
    mv.clear();
    for (auto x : animals[1]) {
        auto pos = x.first;
        if (pos.second == C - 1) pos.second = 0;
        else pos.second++;
        mv[pos] = x.second - 1;
    }
    animals[1] = mv;

    // eat
    for (auto &x : animals[1]) {
        auto pos = x.first;
        auto sp = animals[0].find(pos);
        if (sp != animals[0].end()) {
            x.second = 10;
            animals[0].erase(sp);
            grid[pos.first][pos.second] = cell{2, -1};
        }
    }
    for (auto &x : animals[0]) {
        auto pos = x.first;
        auto &c = grid[pos.first][pos.second];
        if (c.type == 1) {
            c = cell{0, 4};
            x.second = 5;
        }
    }

    // dying
    repi(0, 2) {
        vec<pii> rem;
        for (auto &x : animals[i]) {
            if (x.second == 0)
                rem.pb(x.first);
        }
        for (auto pos : rem) {
            animals[i].erase(animals[i].find(pos));
            grid[pos.first][pos.second] = cell{2, -1};
        }
    }
}

void updLand() {
    repi(0, R) {
        repj(0, C) {
            auto &c = grid[i][j];
            if (c.type == 0) {
                c.wait--;
                if (!c.wait) {
                    c.wait = -1;
                    c.type = 1;
                }
            }
        }
    }
}

void outputGrid() {
    memset(ogrid, 0, sizeof ogrid);
    for (auto p : animals[0])
        ogrid[p.first.first][p.first.second] = 'S';
    for (auto p : animals[1])
        ogrid[p.first.first][p.first.second] = 'W';
    repi(0, R) {
        repj(0, C) {
            if (!ogrid[i][j]) {
                switch (grid[i][j].type) {
                    case 0:
                    ogrid[i][j] = '.';
                    break;
                    case 1:
                    ogrid[i][j] = '#';
                    break;
                    case 2:
                    ogrid[i][j] = '*';
                    break;
                }
            }
        }
    }
    repi(0, R) {
        repj(0, C)
            print(ogrid[i][j]);
        print('\n');
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(T, R, C);
    repi(0, R)
        scan(igrid[i]);
    repi(0, R) {
        repj(0, C) {
            switch (igrid[i][j]) {
                case '.':
                grid[i][j] = {0, 3};
                break;

                case 'W':
                grid[i][j] = {0, 3};
                animals[1][mpr(i, j)] = 10;
                break;
                
                case 'S':
                grid[i][j] = {0, 3};
                animals[0][mpr(i, j)] = 5;
                break;
            }
        }
    }

    // do
    repi(0, T) {
        // outputGrid();
        runTurn();
        updLand();
        // println("---");
    }
    
    outputGrid();

    return 0;
}
