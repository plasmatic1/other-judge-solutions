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

const int MN = 2e5 + 1;
int n, m;
ll arr[MN], dp[MN][2]; // Idx, Flip [0], Flip [1]
// dp[i][j] -> Best value with subseq ending on IDX I

struct pa {
    int i, j;
} par[MN][2];

// segtree
struct pb {
    ll val; int idx;

    Cmplt(pb) {
        if (val == o.val) return idx > o.idx;
        return val < o.val;
    }
};

pb seg[MN << 2][2];

pb upd(int i, int l, int r, int q, pb v, bool flip) {
    if (l == q && r == q) return seg[i][flip] = v;
    if (l > q || r < q) return seg[i][flip];
    int mid = (l + r) >> 1;
    return seg[i][flip] = max(upd(i << 1, l, mid, q, v, flip), upd(i << 1 | 1, mid + 1, r, q, v, flip));
}

pb query(int i, int l, int r, int ql, int qr, bool flip) {
    if (l >= ql && r <= qr) return seg[i][flip];
    if (l > qr || r < ql) return {-LLINF, INF};
    int mid = (l + r) >> 1;
    return max(query(i << 1, l, mid, ql, qr, flip), query(i << 1 | 1, mid + 1, r, ql, qr, flip));
}

// rank compressor
vec<ll> ranks;
int rankOf(ll x) {
    return lower_bound(ranks.begin(), ranks.end(), x) - ranks.begin() + 1;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, m);

    Forinci(1, n) {
        int x; scan(x);
        ranks.pb(x);
        arr[i] = x;
    }

    // init rank compress
    sort(ranks.begin(), ranks.end());

    // init seg
    int n4 = n << 2;
    Fori(1, n4) 
        Forj(0, 2)
            seg[i][j] = {-LLINF, INF};

    // do DP
    dp[0][0] = -LLINF;
    dp[0][1] = 0;
    par[0][0] = par[0][1] = {-1, -1};
    Forinci(1, n) {
        int rankOfX = rankOf(arr[i]);

        Forj(0, 2) {
            par[i][j] = {-1, -1};
            dp[i][j] = -LLINF;
            ll trueX = arr[i] * (j ? -1 : 1);

            // Try 0
            if (dp[0][!j] + trueX > dp[i][j]) {
                dp[i][j] = dp[0][!j] + trueX;
                par[i][j] = {0, !j};
            }

            // Take value other than 0
            
            // Smallest number >= arr[i] - m
            int l = lower_bound(ranks.begin(), ranks.end(), arr[i] - m) - ranks.begin() + 1;
            // Largest number <= arr[i] + m
            int r = upper_bound(ranks.begin(), ranks.end(), arr[i] + m) - ranks.begin();

            pb other = query(1, 1, n, l, r, !j);

            if (other.val + trueX > dp[i][j]) {
                dp[i][j] = other.val + trueX;
                par[i][j] = {other.idx, !j};
            }
        }

        // upd segtree
        Forj(0, 2)
            upd(1, 1, n, rankOfX, {dp[i][j], i}, j);
    }

    // get BEST
    ll best = 0;
    int besti = -1, bestj = -1;
    Forinci(1, n) {
        Forj(0, 2) {
            if (dp[i][j] > best) {
                besti = i;
                bestj = j;
                best = dp[i][j];
            }
        }
    }

    if (besti == -1) {
        println(0);
    }
    else {
        println(best);

        // backtrack
        vi pos;
        while (besti != -1 && bestj != -1) {
            pos.pb(besti);
            int oi = besti, oj = bestj;
            besti = par[oi][oj].i;
            bestj = par[oi][oj].j;
        }

        sort(pos.begin(), pos.end());
        
        // print
        for (auto x : pos)
            if (x) // skip 0
                print(x, ' ');
        print('\n');
    }

    return 0;
}