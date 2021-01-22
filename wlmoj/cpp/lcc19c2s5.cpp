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

const int MN = 3e5 + 10;
int n, q;
ll h[MN]; //, dp[MN];

struct node {
    int l, r;
    ll ansf[2], anss[2]; // ansf = {1st to 2last, 1st to last}, anss = {2nd to 2last, 2nd to last}
    // ll ans;

    int size() { return r - l + 1; }

    void size1(int i) {
        l = r = i;
        ansf[1] = 0;
        ansf[0] = anss[0] = anss[1] = LLINF;
    }

    void reset() {
        l = r = -1;
        ansf[0] = ansf[1] = anss[0] = anss[1] = LLINF;
    }
};

/*
XX...XXYY...YY
*/

ll dh(int x, int y) {
    return abs(h[x] - h[y]);
}

node mergeNode(node a, node b) {
    // dblb("merge"); db(a.l); db(a.r); db(b.l); db(b.r); dbln;
    // not full merge
    if (a.l == -1) return b;
    if (b.l == -1) return a;

    // actual merge now
    node ret{};
    ret.l = a.l;
    ret.r = b.r;

    if (a.size() == 1 && b.size() == 1) {
        ret.ansf[0] = 0LL;
        ret.ansf[1] = dh(b.l, a.l);
        ret.anss[0] = LLINF;
        ret.anss[1] = 0LL;

        // dblb("1node"); db(a.l); db(b.l); dbln;
        // db(ret.ansf[0]); db(ret.ansf[1]); db(ret.anss[0]); db(ret.anss[1]); dbln;
    }
    else if (a.size() == 1) {
        ret.ansf[0] = min(dh(a.l, b.l) + b.ansf[0], dh(a.l, b.l + 1) + b.anss[0]);
        ret.ansf[1] = min(dh(a.l, b.l) + b.ansf[1], dh(a.l, b.l + 1) + b.anss[1]);
        ret.anss[0] = b.ansf[0];
        ret.anss[1] = b.ansf[1];
    }
    else if (b.size() == 1) {
        ret.ansf[0] = a.ansf[1];
        ret.ansf[1] = min(a.ansf[0] + dh(a.r - 1, b.l), a.ansf[1] + dh(a.r, b.l));
        ret.anss[0] = a.anss[1];
        ret.anss[1] = min(a.anss[0] + dh(a.r - 1, b.l), a.anss[1] + dh(a.r, b.l));
    }
    else {
        ret.ansf[0] = min(a.ansf[0] + dh(a.r - 1, b.l) + b.ansf[0], a.ansf[1] + min(dh(a.r, b.l) + b.ansf[0], dh(a.r, b.l + 1) + b.anss[0]));
        ret.ansf[1] = min(a.ansf[0] + dh(a.r - 1, b.l) + b.ansf[1], a.ansf[1] + min(dh(a.r, b.l) + b.ansf[1], dh(a.r, b.l + 1) + b.anss[1]));
        ret.anss[0] = min(a.anss[0] + dh(a.r - 1, b.l) + b.ansf[0], a.anss[1] + min(dh(a.r, b.l) + b.ansf[0], dh(a.r, b.l + 1) + b.anss[0]));
        ret.anss[1] = min(a.anss[0] + dh(a.r - 1, b.l) + b.ansf[1], a.anss[1] + min(dh(a.r, b.l) + b.ansf[1], dh(a.r, b.l + 1) + b.anss[1]));
    }

    mina(ret.ansf[0], dh(ret.l, ret.l + 1) + ret.anss[0]);
    mina(ret.ansf[1], dh(ret.l, ret.l + 1) + ret.anss[1]);
    mina(ret.ansf[1], ret.ansf[0] + dh(ret.r, ret.r - 1));
    mina(ret.anss[1], ret.anss[0] + dh(ret.r, ret.r - 1));

    return ret;
}

const node DEFNODE = {-1, -1};
node seg[MN << 2];

node build(int i, int l, int r) {
    node &n = seg[i];
    if (l == r) {
        n.size1(l);
        return n;
    }
    int mid = (l + r) >> 1;
    return seg[i] = mergeNode(build(i << 1, l, mid), build(i << 1 | 1, mid + 1, r));
}

node qu(int i, int ql, int qr) {
    node &n = seg[i];
    if (ql > n.r || qr < n.l) {
        node ret;
        ret.reset();
        return ret;
    }
    if (n.l >= ql && n.r <= qr) { 
        // db(n.ansf[0]); db(n.ansf[1]); db(n.anss[0]); db(n.anss[1]); dbln; 
        return n; 
    }

    auto qa = qu(i << 1, ql, qr), qb = qu(i << 1 | 1, ql, qr), ret = mergeNode(qa, qb);
    // dblb("seg ret"); db(i); db(n.l); db(n.r); db(ql); db(qr); dbln;
    // db(qa.l); db(qa.r); db(qa.ansf[0]); db(qa.ansf[1]); db(qa.anss[0]); db(qa.anss[1]); dbln;
    // db(qb.l); db(qb.r); db(qb.ansf[0]); db(qb.ansf[1]); db(qb.anss[0]); db(qb.anss[1]); dbln;
    // db(ret.ansf[0]); db(ret.ansf[1]); db(ret.anss[0]); db(ret.anss[1]); dbln;
    return ret;
    // return mergeNode(qu(i << 1, ql, qr), qu(i << 1 | 1, ql, qr));
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, q);

    repi(1, n + 1) {
        scan(h[i]);
    }
    build(1, 1, n);

    repi(0, q) {
        int a, b;
        scan(a, b);
        if (a > b) swap(a, b);

        auto ans = qu(1, a, b);
        // db(ans.ansf[0]); db(ans.ansf[1]); db(ans.anss[0]); db(ans.anss[1]); dbln;

        println(ans.ansf[1]);
    }

    return 0;
}