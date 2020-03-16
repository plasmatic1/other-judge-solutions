#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
// #pragma GCC target "sse,sse2,sse3,sse4,abm,avx,mmx,popcnt,tune=native"

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
	const string PROBLEM_ID = "triangles";
	freopen((PROBLEM_ID + ".in").c_str(), "r", stdin);
	freopen((PROBLEM_ID + ".out").c_str(), "w", stdout);
}

struct pt {
	int x, y;
	void rot45() {
		x += y;
		y = x - 2 * y;
	}
	void fix() {
		x += 1;
		y += 301;
	}
	int manhat(pt &o) {
		return abs(x - o.x) + abs(y - o.y);
	}
	Cmplt(pt) {
		return x == o.x ? y < o.y : x < o.x;
	}
};
Outop(pt) {
	out << "(" << o.x << ", " << o.y << ")";
	return out;
}

const int MN = 301, MDIS = 600, MX = 605;
int N,
	psum[MX][MX];
bool has[MX][MX];
char grid[MN][MN];
vec<pt> pts;

finline int rsq(int r, int L, int R) {
	return psum[r][R] - psum[r][L - 1];
}

finline bool check(int x, int y) {
	if (x < 0 || x >= MX || y < 0 || y >= MX) return false;
	return has[x][y];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
#ifndef LOCAL
	init_file_io();
#endif

	// take input
	scan(N);
	repi(0, N)
		scan(grid[i]);
	repi(0, N) {
		repj(0, N) {
			if (grid[i][j] == '*') {
				pt p{i, j};
				// db(p);
				p.rot45(); p.fix();
				// dblb("trans"); db(p); dbln;
				pts.pb(p);
			}
		}
	}

	// make psum
	for (auto x : pts) {
		// println(x.x,x.y);
		psum[x.x][x.y]++;
		has[x.x][x.y] = true;
	}
	repi(0, MX)
		partial_sum(psum[i], psum[i] + MX, psum[i]);

	// count!!!
	ll tot = 0;
	rep(row, 1, MX) {
		repi(1, MX) {
			repj(i + 1, MX) {
				if (has[row][i] && has[row][j]) {
					int d = j - i, upRow = row - d, downRow = row + d;
					if (upRow > 0)
						tot += rsq(upRow, i, j);
					if (downRow < MX)
						tot += rsq(downRow, i, j);
				}
			}
		}
	}

	// make psum (again!!!) (but this time in other direction)
	memset(psum, 0, sizeof psum);
	memset(has, false, sizeof has);
	for (auto x : pts) {
		psum[x.y][x.x]++;
		has[x.y][x.x] = true;
	}
	repi(0, MX)
		partial_sum(psum[i], psum[i] + MX, psum[i]);

	// count!!!
	rep(col, 1, MX) {
		repi(1, MX) {
			repj(i + 1, MX) {
				if (has[col][i] && has[col][j]) {
					int d = j - i, upCol = col - d, downCol = col + d;
					if (upCol > 0)
						tot += rsq(upCol, i, j);
					if (downCol < MX)
						tot += rsq(downCol, i, j);
				}
			}
		}
	}

	// db(tot); dbln;

	// subtract duplicates
	memset(has, false, sizeof has);
	for (auto x : pts) {
		has[x.x][x.y] = true;
	}
	repi(1, MX) {
		repj(1, MX) {
			if (!check(i, j)) continue;
			repk(1, MX) {
				if (k == i) continue;
				if (!check(k, j)) continue;
				int d = abs(k - i);
				// db(i); db(j); db(k); db(d); db(j-d); db(j+d); dbln;
				tot -= check(i, j - d);
				tot -= check(i, j + d);
			}
		}
	}

	// db(tot); dbln;
	println(tot);
}
