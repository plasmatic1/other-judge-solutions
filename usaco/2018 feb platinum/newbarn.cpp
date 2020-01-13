// What the hell is this???
// ;)

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

const int MN = 1e5 + 1, LG = 17;
int Q, N = 0;

// lca stuff
int par[LG][MN], dis[MN];

int lca(int v, int w) {
	if (v == w) return v;
	if (dis[v] > dis[w]) swap(v, w);
	int delta = dis[w] - dis[v];
	repi(0, LG)
		if ((delta >> i) & 1)
			w = par[i][w];
	if (v == w) return v;
	reprev(i, LG - 1, -1) {
		if (par[i][v] != par[i][w]) {
			v = par[i][v];
			w = par[i][w];
		}
	}
	return par[0][v];
}

int qdis(int v, int w) {
	return dis[v] + dis[w] - 2 * dis[lca(v, w)];
}

// dsu and root stuff
int dsu[MN], rootIdx[MN];
struct Root {
	int rt, A, B;
};
vec<Root> roots;

void initDsu() { iota(dsu, dsu + MN, 0); }
int rt(int x) { return x == dsu[x] ? x : dsu[x] = rt(dsu[x]); }
void unite(int x, int y) {
	int rx = rt(x), ry = rt(y);
	dsu[max(rx, ry)] = min(rx, ry);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	// init
	memset(par, -1, sizeof par);
	initDsu();

	scan(Q);

	while (Q--) {
		char T; int V;
		scan(T, V);

		if (T == 'B') {
			N++;

			if (V == -1) {
				rootIdx[N] = roots.size();
				roots.pb({N, N, N});
			}
			else {
				// lca
				par[0][N] = V;
				dis[N] = dis[V] + 1;

				for (int i = 1; i < LG; i++) {
					int pp = par[i - 1][N];
					par[i][N] = pp == -1 ? -1 : par[i - 1][pp];
				}

				// dsu stuff
				unite(V, N);

				// update root stuff
				auto &root = roots[rootIdx[rt(V)]];
				int dia = qdis(root.A, root.B), da = qdis(N, root.A), db = qdis(N, root.B);
				// db(N); db(dia); db(root.A); db(root.B); db(da); db(db); dbln;
				if (da >= db && da > dia) {
					root.B = N;
					dia = da;
				}
				else if (db > da && db > dia) {
					root.A = N;
					dia = db;
				}
			}
		}
		else {
			auto root = roots[rootIdx[rt(V)]];
			int ans = max(qdis(root.A, V), qdis(root.B, V));
			println(ans);

			// db(V); db(root.rt); db(root.A); db(root.B); db(qdis(root.A, V)); db(qdis(root.B, V)); dbln;
		}
	}

	return 0;
}
