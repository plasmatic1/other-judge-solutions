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

const ll MOD = 1e9 + 7;
using Mat = vec<vec<ll>>;
using Vec = vec<ll>;

Mat make(int N) {
	Mat ret;
	repi(0, N)
		ret.pb(Vec(N));
	return ret;
}

Mat identity(int N) {
	Mat ret = make(N);
	repi(0, N)
		ret[i][i] = 1;
	return ret;
}

void mul(Mat &ret, Mat a, Mat b) {
	int N = a.size();
	repi(0, N)
		repj(0, N)
			ret[i][j] = 0;
	repi(0, N)
		repj(0, N)
			repk(0, N)
				ret[i][j] = (ret[i][j] + a[i][k] * b[k][j]) % MOD;
}

Mat mul(Mat a, Mat b) {
	int N = a.size();
	Mat ret = make(N);
	repi(0, N)
		repj(0, N)
			repk(0, N)
				ret[i][j] = (ret[i][j] + a[i][k] * b[k][j]) % MOD;
	return ret;
}

Vec mul(Mat a, Vec b) {
	int N = a.size();
	Vec ret(N);
	repi(0, N) 
		repj(0, N) 
			ret[i] = (ret[i] + a[i][j] * b[j]) % MOD;
	return ret;
}

const int MN = 1e5 + 1;
const Mat OP_A = {{1, 1}, {0, 1}}, OP_B = {{1, 0}, {1, 1}}, IDENTITY = identity(2);
int n, q;
string s;
struct {
	Mat seg[MN << 2][2];
	bool lazy[MN << 3];

	void push(int i) {
		if (lazy[i]) {
			swap(seg[i][0], seg[i][1]);
			lazy[i << 1] ^= 1;
			lazy[i << 1 | 1] ^= 1;
			lazy[i] = 0;
		}
	}
	void build(int i, int l, int r) {
		if (l == r) {
			bool cond = s[l - 1] == 'A';
			seg[i][0] = cond ? OP_A : OP_B;
			seg[i][1] = cond ? OP_B : OP_A;
			// dblb("build"); db(i); db(l); db(r); db(seg[i][0]); db(seg[i][1]); dbln;
			return;
		}
		int mid = (l + r) >> 1;
		build(i << 1, l, mid); build(i << 1 | 1, mid + 1, r);
		// seg[i][0] = mul(seg[i << 1][0], seg[i << 1 | 1][0]);
		// seg[i][1] = mul(seg[i << 1][1], seg[i << 1 | 1][1]);
		repj(0, 2) {
			seg[i][j] = make(2);
			mul(seg[i][j], seg[i << 1 | 1][j], seg[i << 1][j]);
		}
		// dblb("build"); db(i); db(l); db(r); db(seg[i][0]); db(seg[i][1]); dbln;
	}
	Mat qu(int i, int l, int r, int ql, int qr) {
		if (l > qr || r < ql) return IDENTITY;
		push(i);
		// db(i); db(l); db(r); db(ql); db(qr); db(seg[i][0]); dbln;
		if (l >= ql && r <= qr) return seg[i][0];
		int mid = (l + r) >> 1;
		// return mul(qu(i << 1, l, mid, ql, qr), qu(i << 1 | 1, mid + 1, r, ql, qr));
		return mul(qu(i << 1 | 1, mid + 1, r, ql, qr), qu(i << 1, l, mid, ql, qr));
	}
	void upd(int i, int l, int r, int ql, int qr) {
		push(i);
		if (l > qr || r < ql) return;
		if (l >= ql && r <= qr) {
			lazy[i] ^= 1;
			push(i);
			return;
		}
		int mid = (l + r) >> 1;
		upd(i << 1, l, mid, ql, qr); upd(i << 1 | 1, mid + 1, r, ql, qr);
		// seg[i][0] = mul(seg[i << 1][0], seg[i << 1 | 1][0]);
		// seg[i][1] = mul(seg[i << 1][1], seg[i << 1 | 1][1]);
		repj(0, 2)
			mul(seg[i][j], seg[i << 1 | 1][j], seg[i << 1][j]);
	}
} seg;

#define ALL 1, 1, n

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n, q, s);
	seg.build(ALL);
	// s = " " + s;

	// db(OP_A); db(OP_B); db(mul(OP_A, OP_A)); db(identity(2)); dbln;
	// repi(1, n + 1) {
		// auto qq = seg.qu(ALL, 1, i);
		// db(i); db(qq); db(mul(qq, {1,1})); dbln;
	// }

	repi(0, q) {
		int t, l, r;
		scan(t, l, r);

		if (t == 1) 
			seg.upd(ALL, l, r);
		else {
			ll a, b;
			scan(a, b);
			auto mat = seg.qu(ALL, l, r);
			auto ans = mul(mat, {a, b});
			// db(mat); db(ans); dbln;
			println(ans[0], ans[1]);
		}
	}

	return 0;
}