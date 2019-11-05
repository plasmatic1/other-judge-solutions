#pragma region
#include <bits/stdc++.h>
using namespace std;
// Common DS shorteners
using ll = long long; using ull = unsigned long long;
using pii = pair<int, int>; using pll = pair<ll, ll>;
template <typename T> using vec = vector<T>;
template <typename K, typename V> using um = unordered_map<K, V>; template<typename K, typename V> using om = map<K, V>;
template <typename K> using us = unordered_set<K>; template <typename K> using os = set<K>;
using vi = vec<int>; using vl = vec<ll>; using vpi = vec<pii>; using vpl = vec<pll>;
// Shorthand Macros
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define mpr make_pair
#define pb push_back
// Shorthand Function Macros
#define Fori(a, b) for (int i = a; i < b; i++)
#define Forj(a, b) for (int j = a; j < b; j++)
#define Fork(a, b) for (int k = a; k < b; k++)
#define Forinci(a, b) for (int i = a; i <= b; i++)
#define Forincj(a, b) for (int j = a; j <= b; j++)
#define Forinck(a, b) for (int k = a; k <= b; k++)
#define Cmplt(type) bool operator<(const type &o) const
#define Cmpgt(type) bool operator>(const type &o) const
#define Cmpfn(type) bool operator()(const type &a, const type &b)
// Shorthand Function Macros Part 2
#define Pow2(x) (1LL << (x))
// Shorthand Functions
template<typename T> inline void maxa(T& st, T v) { st = max(st, v); }
template<typename T> inline void mina(T& st, T v) { st = min(st, v); }
inline void setprec(ostream& out, int prec) { out << setprecision(prec) << fixed; }
// Out operators and printing for arrays and vectors
template <typename T> ostream& operator<<(ostream& out,vector<T> iter){out<<"[";for(auto t:iter){out<<t<<", ";}out<<"]";return out;}
template <typename T> void debugArray(T *arr,int sz){cout<<"[";for(int i=0;i<sz;i++){cout<<arr[i]<<", "; } cout<<"]\n";}
template <typename T> void printArray(T *arr,int sz){for(int i=0;i<sz;i++){cout<<arr[i]<<" "; } cout<<"\n";}
#define OUT_OPERATOR(type, propa, propb) ostream& operator<<(ostream& out,type obj){out<<"("<<#propa<<"="<<obj. propa<<", "<<#propb<<"="<<obj. propb<<")";return out;}
// I/O Operations
inline void scan(){}
template<typename F, typename... R> inline void scan(F &f,R&... r){cin>>f;scan(r...);}
template <typename F> inline void println(F t){cout<<t<<'\n';}
template<typename F, typename... R> inline void println(F f,R... r){cout<<f<<" ";println(r...);}
inline void print(){}
template<typename F, typename... R> inline void print(F f,R... r){cout<<f;print(r...);}
// Debugging
int di_; string dnms_, casttostr_ = ",";
void debug_(){cout<<endl;}
template<typename T> string debug_tostring_(T val) { ostringstream os; os << val; return os.str(); }
string debug_name_(string s, string str_val) {
    string ret = ""; if (s[0] == ' ') { ret += ' '; s = s.substr(1); } if (s[0] == '"' && s[s.length() - 1] == '"') { ret += string("[") + str_val + "]"; }
    else if (s.length() == (size_t)3 && s[0] == '\'' && s[2] == '\'') { ret += '(' + str_val + ')'; } else { ret += s + ": " + str_val; } return ret;
} template<typename F, typename... R> void debug_(F f, R... r) {
    int bc = 0; string pr = "";
    while (bc != 0 || dnms_[di_] != ',') { if (dnms_[di_] == '(') { bc++; } else if (dnms_[di_] == ')') { bc--; } pr += dnms_[di_++]; }
    di_++; cout << debug_name_(pr, debug_tostring_(f)) << ","; debug_(r...);
}
#define debug(...) do{dnms_=#__VA_ARGS__+casttostr_,di_=0,debug_(__VA_ARGS__);}while(0)
#pragma endregion

struct qu {
    int i, l, r;
    Cmplt(qu) { return r < o.r; }
};

const int MN = 2e5 + 1, MV = 1e6 + 1, CNT_D = 1e6;
int n, q,
    arr[MN], ans[MN];
qu queries[MN];

int query(int seg[MN << 2], int i, int l, int r, int ql, int qr) {
    if (l > qr || r < ql) return -INF;
    if (l >= ql && r <= qr) return seg[i];
    int mid = (l + r) >> 1;
    return max(query(seg, i << 1, l, mid, ql, qr), query(seg, i << 1 | 1, mid + 1, r, ql, qr));
}

int update(int seg[MN << 2], int i, int l, int r, int q, int v) {
    if (l > q || r < q) return seg[i];
    if (l == q && r == q) return seg[i] = v;
    int mid = (l + r) >> 1;
    return seg[i] = max(update(seg, i << 1, l, mid, q, v), update(seg, i << 1 | 1, mid + 1, r, q, v));
}

inline int SegQuery(int seg[MN << 2], int l, int r) { return query(seg, 1, 1, n, l, r); }
inline int SegUpdate(int seg[MN << 2], int q, int v) { return update(seg, 1, 1, n, q, v); }

// for solving
int segAbs[MN << 2], segRel[MN << 2], cnt[MV << 1];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // input
    scan(n, q);

    Forinci(1, n)
        scan(arr[i]);
    
    Fori(0, q) {
        int l, r;
        scan(l, r);
        queries[i] = {i, l, r};
    }
    sort(queries, queries + q);

    // solve
    int lptr = 1, rptr = 1, qptr = 0;
    for (; rptr <= n; rptr++) {
        // update seg
        cnt[arr[rptr] + CNT_D]++;
        if (cnt[arr[rptr] + CNT_D] > 1) {
            while (cnt[arr[rptr] + CNT_D] > 1) {
                assert(lptr <= rptr);
                SegUpdate(segAbs, lptr, rptr - 1);
                SegUpdate(segRel, lptr, rptr - lptr); // (rptr - 1) - lptr + 1;
                cnt[arr[lptr] + CNT_D]--;
                lptr++;
            }
        }

        // answer queries
        while (qptr < q && queries[qptr].r == rptr) {
            int &cans = ans[queries[qptr].i];
            maxa(cans, SegQuery(segRel, queries[qptr].l, queries[qptr].r)); // Answer is within subarray
            maxa(cans, rptr - max(lptr, queries[qptr].l) + 1); // Current 2-pointer result
            maxa(cans, SegQuery(segAbs, 1, queries[qptr].l) - queries[qptr].l + 1); // Answer is before subarray
            // debug(queries[qptr].i, queries[qptr].l, queries[qptr].r, cans, lptr, rptr);
            qptr++; // increment
        }
    }

    // output
    Fori(0, q)
        println(ans[i]);

    return 0;
}
