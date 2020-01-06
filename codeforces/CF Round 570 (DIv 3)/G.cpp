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

struct p {
    int cntall, cntgive; // u want max of cnt1
    Cmplt(p) { return cntall == o.cntall ? cntgive > o.cntgive : cntall > o.cntall; }
};

Outop(p) {
    out << "(all=" << o.cntall << ", " << "give=" << o.cntgive << ")";
    return out;
}

struct cmpgive {
    bool operator()(const p &a, const p &b) {
        return a.cntgive < b.cntgive;
    }
};

const int MN = 2e5 + 1;
int n, 
    arr[MN], give[MN];
umap<int, int> cntall, cntgive;
priority_queue<p, vector<p>, cmpgive> pqgive;
// priority_queue<p, vector<p>, cmpall> pqall;

void solve() {
    repi(0, n) {
        cntall[arr[i]]++;
        if (give[i])
            cntgive[arr[i]]++;
    }
    
    // get freqs
    vec<p> freqs;
    for (auto p : cntall)
        freqs.pb({p.second, cntgive[p.first]});
    sort(freqs.begin(), freqs.end());
    // db(freqs); dbln;

    // get curs
    vi curs;
    int cur = INF;
    for (auto p : freqs) {
        cur = min(cur - 1, p.cntall);
        curs.pb(cur);
    }

    // do stuff
    ll tot = 0, totgive = 0;
    int fptr = 0, fsz = freqs.size();
    for (auto cur : curs) {
        if (cur > 0) {
            while (fptr < fsz && freqs[fptr].cntall >= cur) {
                // dblb("push"); db(cur); db(freqs[fptr]); dbln;
                pqgive.push(freqs[fptr]);
                fptr++;
            }

            // try to use freqs
            // bool usefreqs = false;
            p use = {-1, -1};
            // if (fptr < fsz) {
            //     use = freqs[fptr];
            //     usefreqs = true;
            // }

            // try to use PQ
            // if (!pqgive.empty() && pqgive.top().cntgive > use.cntgive) {
                // dblb("using give"); db(pqgive.top()); dbln;
                // usefreqs = false;
                use = pqgive.top();
                pqgive.pop();
            // }

            // db(cur); db(use); db(usefreqs); db(fptr); db(fsz); db(pqgive.top()); dbln;

            // if freqs was used, increment pointer
            // if (usefreqs)
            //     fptr++;

            tot += cur;
            totgive += min(cur, use.cntgive);
        }
    }

    println(tot, totgive);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T; scan(T);
    while (T--) {
        // Input
        scan(n);
        repi(0, n)
            scan(arr[i], give[i]);

        // Reset
        cntall.clear();
        cntgive.clear();
        // pqall.clear();
        while (!pqgive.empty())
            pqgive.pop();

        solve();
    }

    return 0;
}
