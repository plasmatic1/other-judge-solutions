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

/*
connect A and B

4 4
1 2 3 4

1 - 2 - 3 - 4
1 + 2, 2 + 3, 3 + 4, 4 + 1 = 20
1 + 2, 1 + 3, 2 + 3, 


// 1 - 2
// 1 - 3
// 2 - 3
// 4 - 1
// 4 - 2

1 2
1 3
2 3

*/

struct p {
    int i, v;
    Cmplt(p) { return v < o.v; }
};

struct ed {
    int a, b, w;
    Cmplt(ed) { return w < o.w; }
};

const int MN = 1001;
int n, m,
    cnt[MN];
p fri[MN];
// vec<ed> alleds;
// bool used[500001];

void solve() {
    if (n == 2 || m < n) {
        println(-1);
        return;
    }

    // Forinci(1, n) {
    //     Forincj(i + 1, n) {
    //         alleds.pb({i, j, fri[i].v + fri[j].v});
    //     }
    // }
    // sort(alleds.begin(), alleds.end());

    // // assert(0);

    // vpi eds;
    // ll tot = 0;
    // int sz = alleds.size(), tused = 0;
    // Fori(0, sz) {
    //     auto ed = alleds[i];
    //     if (cnt[ed.a] < 2 && cnt[ed.b] < 2) {
    //         used[i] = true;
    //         cnt[ed.a]++;
    //         cnt[ed.b]++;
    //         eds.pb({ed.a, ed.b});
    //         tused++;
    //         tot += ed.w;
    //     }
    // }

    // Fori(0, sz) {
    //     if (used[i]) continue;
    //     auto ed = alleds[i];
    //     if (cnt[ed.a] < 2 || cnt[ed.b] < 2) {
    //         debug(i, tused, cnt[ed.a], cnt[ed.b], ed.a, ed.b, ed.w);
    //         used[i] = true;
    //         cnt[ed.a]++;
    //         cnt[ed.b]++;
    //         eds.pb({ed.a, ed.b});
    //         tused++;
    //         tot += ed.w;
    //     }
    // }

    // // assert(0);

    // while (tused < m) {
    //     eds.pb({alleds[0].a, alleds[0].b});
    //     tot += alleds[0].w;
    //     tused++;
    // }

    ll tot = 0;
    vpi eds;

    Fori(0, n) {
        int a = i, b = (i + 1) % n;
        a++; b++;
        eds.pb({a, b});
        tot += fri[a].v + fri[b].v;
    }

    sort(fri + 1, fri + n + 1);
    int ct = n;
    while (ct < m) {
        eds.pb({fri[1].i, fri[2].i});
        tot += fri[1].v + fri[2].v;
        ct++;
    }    

    println(tot);
    for (auto x : eds) {
        println(x.first, x.second);
    }

    // assert(0);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T; scan(T);
    while (T--) {
        // io
        scan(n, m);
        Forinci(1, n) {
            ll w;
            scan(w);
            fri[i] = {i, w};
        }
        // sort(fri + 1, fri + n + 1);

        // reset
        // alleds.clear();
        // fill(cnt, cnt + n + 1, 0);
        // fill(used, used + (n * (n - 1) / 2) + 1, 0);

        solve();
        // cout.flush();
    }

    return 0;
}
