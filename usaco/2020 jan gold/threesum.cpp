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
	const string PROBLEM_ID = "threesum";
	freopen((PROBLEM_ID + ".in").c_str(), "r", stdin);
	freopen((PROBLEM_ID + ".out").c_str(), "w", stdout);
}

const int MN = 5001, MQ = 100001, MV = 4000001, D = 2000000;
int n, q;
ll val[MN];

// fca
struct {
	int cq = -1, qid[MV], val[MV];
	inline int get(int idx) {
		idx += D;
		if (qid[idx] != cq) val[idx] = 0, qid[idx] = cq;
		return val[idx];
	}
	inline void insert(int idx) {
		idx += D;
		if (qid[idx] != cq) val[idx] = 0, qid[idx] = cq;
		val[idx]++;
	}
	inline void reset() { cq++; }
} has;

// offline
struct Qu {
	int i, l, r;
	Cmplt(Qu) { return r < o.r; }
};
Qu qus[MQ];
ll ans[MQ];

ll bit[MN];
void add(int x, ll v) {
	for (; x < MN; x += x & -x)
		bit[x] += v;
}
ll sum(int x) {
	ll sum = 0;
	for (; x; x -= x & -x)
		sum += bit[x];
	return sum;
}
vec<pair<int, int>> segs[MN];

int main(){
#ifdef LOCAL
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
#else
	init_file_io();
#endif

	scan(n, q);
	repi(1, n + 1)
		scan(val[i]);
	repi(0, q) {
		scn(int, l, r);
		qus[i] = {i, l, r};
	}
	sort(qus, qus + q);

	// precalc
	repi(1, n + 1) {
		has.reset();
		repj(i + 2, n + 1) {
			// insert val
			has.insert(val[j - 1]);

			// count
			ll cc = has.get(-(val[i] + val[j]));
			// db(i); db(j); db(cc); dbln;
			if (cc != 0)
				segs[j].pb({i, cc});
		}
	}
	repi(1, n + 1)
		sort(all(segs[i]));

	// offline
	int sptr = 1;
	repi(0, q) {
		auto qu = qus[i];
		while (sptr <= qu.r) {
			for (auto p : segs[sptr])
				add(p.first, p.second);
			sptr++;
		}

		ans[qu.i] = sum(qu.r) - sum(qu.l - 1);
	}
	
	// ANSAR
	repi(0, q)
		println(ans[i]);

	return 0;
}
