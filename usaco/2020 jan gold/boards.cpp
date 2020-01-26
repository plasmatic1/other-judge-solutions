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
	const string PROBLEM_ID = "boards";
	freopen((PROBLEM_ID + ".in").c_str(), "r", stdin);
	freopen((PROBLEM_ID + ".out").c_str(), "w", stdout);
}

struct Pos {
	int x, y;

	Cmplt(Pos) {
		return x == o.x ? y < o.y : x < o.x;
	}

	bool operator==(const Pos &o) const {
		return x == o.x && y == o.y;
	}
};

struct Spring {
	Pos st, en;
};

Inop(Pos) {
	in >> o.x >> o.y;
	return in;
}

// const int MN = 1e9 + 1;
const int MP = 1e5 + 5;
int n, p;
Spring sp[MP];

// seg and rank comp
vec<int> ycomp;
int ysz;
int rankof(int x) {
	return lower_bound(all(ycomp), x) - ycomp.begin() + 1;
}
const int BMAX = MP * 2; 
struct {
	ll bit[BMAX];
	ll query(int x) {
		ll mn = LLINF;
		for (; x; x -= x & -x)
			mina(mn, bit[x]);
		return mn;
	}
	void update(int x, ll v) {
		for (; x <= ysz; x += x & -x)
			mina(bit[x], v);
	}
	inline void init() { memset(bit, 0x3f, sizeof bit); }
} bdown;

// sweep
struct Qu {
	int type; // Query for point type (0), Update point type (1)
	int idx;
	Pos p;
	
	Cmplt(Qu) {
		// return p.x == o.p.x ? p.y > o.p.y : p.x > o.p.x;
		return p == o.p ? type > o.type : p < o.p; // if positions are same, update goes first only if different springs
	}
};

ll ans[MP];
vec<Qu> qus;

int main(){
#ifdef LOCAL
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
#else
	init_file_io();
#endif

	scan(n, p);
	repi(0, p) {
		scan(sp[i].st, sp[i].en);
		ycomp.pb(sp[i].st.y);
		ycomp.pb(sp[i].en.y);
	}

	// init
	ycomp.pb(0); ycomp.pb(n);
	sort(all(ycomp));
	ycomp.resize(unique(all(ycomp)) - ycomp.begin());
	ysz = ycomp.size();

	bdown.init();

	// init linesweep
	repi(0, p) { 
		qus.pb({0, i, sp[i].st});
		qus.pb({1, i, sp[i].en});
	}
	qus.pb({1, -1, {0, 0}});
	qus.pb({0, p, {n, n}});
	sort(all(qus));

	// do linesweep
	memset(ans, 0x3f, sizeof ans);
	for (auto q : qus) {
		auto &idx = q.idx;
		auto &pos = q.p;
		ll xadd = n - pos.x;
		int yidx = rankof(pos.y);

		if (q.type == 0) { // query
			ll ansdown = bdown.query(yidx) - xadd + pos.y;
			ans[idx] = ansdown;

			// db(q.type); db(idx); db(pos.x); db(pos.y); db(yidx); db(ansdown); db(ansup); db(xadd); dbln;
		}
		else { // update
			ll val = idx != -1 ? ans[idx] : 0; // if idx == -1 then it's starting pos
			bdown.update(yidx, val + xadd - pos.y);

			// db(q.type); db(idx); db(pos.x); db(pos.y); db(yidx); db(val); db(xadd); dbln;
		}
	}

	// output
	println(ans[p]);

	return 0;
}
