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
    int l, r;
};

const int MM = 3e4 + 1, MN = 1e6 + 1;
int n, m,
    L[MM], R[MM], X[MM];
map<int, vec<qu>, greater<int>> qus;

// seg
int seg[MN << 2], lazy[MN << 3];

void push(int i) {
    if (lazy[i]) {
        seg[i] = lazy[i];
        lazy[i << 1] = lazy[i];
        lazy[i << 1 | 1] = lazy[i];
        lazy[i] = 0;
    }
}

int qu(int i, int l, int r, int ql, int qr) {
    push(i);
    if (l > qr || r < ql) return INF;
    if (l >= ql && r <= qr) return seg[i];
    int mid = (l + r) >> 1;
    return min(qu(i << 1, l, mid, ql, qr), qu(i << 1 | 1, mid + 1, r, ql, qr));
}

int upd(int i, int l, int r, int ql, int qr, int v) {
    push(i);
    if (l > qr || r < ql) return seg[i];
    if (l >= ql && r <= qr) {
        lazy[i] = v;
        push(i);
        return seg[i];
    }
    int mid = (l + r) >> 1;
    return seg[i] = min(upd(i << 1, l, mid, ql, qr, v), upd(i << 1 | 1, mid + 1, r, ql, qr, v));
}

bool work(int qcnt) {
    qus.clear();
    memset(seg, 0, sizeof seg);
    memset(lazy, 0, sizeof lazy);

    Fori(0, qcnt) {
        qus[X[i]].pb({L[i], R[i]});
    }

    // Check when a segment cannot be put on
    // Add all segs first
    for (auto &p : qus) {
        int l = p.second[0].l, r = p.second[0].r;
        for (auto q : p.second) {
            maxa(l, q.l);
            mina(r, q.r);
            if (l > r)
                return false;
        }

        if (qu(1, 1, n, l, r) > p.first)
            return false;

        for (auto q : p.second)
            upd(1, 1, n, q.l, q.r, p.first);
    }

    return true;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, m);

    Fori(0, m) {
        scan(L[i], R[i], X[i]);
    }

    int l = 0, r = m + 1;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        // debug(l, r, mid, work(mid));
        if (work(mid))
            l = mid;
        else
            r = mid;
    }

    // debug(l, r);

    if (l == m)
        println(0);
    else
        println(l + 1);

    return 0;
}
