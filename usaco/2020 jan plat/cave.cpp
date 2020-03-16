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

void init_file_io() {
	const string PROBLEM_ID = "cave";
	freopen((PROBLEM_ID + ".in").c_str(), "r", stdin);
	freopen((PROBLEM_ID + ".out").c_str(), "w", stdout);
}

const ll MOD = 1e9 + 7;
const int MN = 1011, MNM = 1e6 + 1;
int n, m;
char grid[MN][MN];

void madd(ll &a, ll b) { a = (a + b) % MOD; }

// dsu
inline int conv(int x, int y) { return y + x * m; }
inline int getx(int v) { return v / m; }
inline int gety(int v) { return v % m; }
struct {
	int dsu[MNM];
	void init() { iota(dsu, dsu + MNM, 0); }
	int rt(int x) { return dsu[x] == x ? x : dsu[x] = rt(dsu[x]); }
	void merge(int x, int y) { 
		x = rt(x); y = rt(y);
		if (x > y) swap(x, y);
		dsu[y] = x;
	}
} uf;

// tree stuff
int par[MNM];
vi g[MNM];
ll dp[MNM];

void dfs(int c, int p) {
	dp[c] = 1LL;
	for (int to : g[c]) {
		if (to ^ p) {
			dfs(to, c);
			dp[c] = (dp[c] * dp[to]) % MOD;
		}
	}
	madd(dp[c], 1);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	// #ifndef LOCAL
	// init_file_io();
	// #endif

	scan(n, m);
	repi(0, n)
		scan(grid[i]); //, dbarr(grid[i], m + 2), dbln;
	
	// dsu stuff
	memset(par, -1, sizeof par);
	uf.init();
	reprev(i, n - 2, 0) {
		// first merge l-r
		repj(1, m - 1) {
			if (grid[i][j] != '#') {
				int cv = conv(i, j);
				if (grid[i][j - 1] != '#')
					uf.merge(cv, conv(i, j - 1));
				if (grid[i][j + 1] != '#')
					uf.merge(cv, conv(i, j + 1));
			}
		}

		// merge down
		repj(1, m - 1) {
			if (grid[i][j] != '#') {
				int cv = conv(i, j);
				
				if (grid[i + 1][j] != '#') {
					int cvAdj = conv(i + 1, j), adjRt = uf.rt(cvAdj);
					uf.merge(cvAdj, cv);
					int cRt = uf.rt(cv);
					// dblb("valid down merge"); db(i); db(j); db(cv); db(cRt); db(cvAdj); db(adjRt); dbln;

					if (adjRt != cRt) {
						par[adjRt] = cRt;
						g[cRt].pb(adjRt);
					}
				}
			}
		}

		// fix nodes that have changed root 
		repj(1, m - 1) {
			if (grid[i][j] != '#') {
				int cv = conv(i, j), cRt = uf.rt(cv);
				if (cv != cRt) {
					for (auto to : g[cv])
						g[cRt].pb(to);
					g[cv].clear();
				}
			}
		}
	}

	// debug
	// repi(0, n)
	// 	repj(0, m)
	// 		db(i), db(j), db(conv(i, j)), db(g[conv(i, j)]), dbln;

	// count subtree subsets
	ll tot = 1;
	int nm = n * m;
	repi(0, nm) {
		if (grid[getx(i)][gety(i)] != '#' && uf.rt(i) == i) {
			dfs(i, -1);
			tot = (tot * dp[i]) % MOD;
			// db(i); db(dp[i]); dbln;
		}
	}
	println(tot);

	return 0;
}
