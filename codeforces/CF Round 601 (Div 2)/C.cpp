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

struct trip {
    int a[3];
};

struct p {
    int i, v;
    Cmplt(p) { return v == o.v ? i < o.i : v < o.v; }
};

const int MN = 1e5 + 1;
int n,
    cnt[MN];
trip t[MN];
set<p> contains[MN];

void rem(int i) {
    auto a = t[i].a;
    // auto pa = contains[a[0]].lower_bound({i, a[1]}), pb = contains[a[0]].lower_bound({i, a[2]});
    // debug(a[0], a[1], a[2]);
    // debug(pa == contains[a[0]].end(), pb == contains[a[0]].end());
    contains[a[0]].erase(contains[a[0]].lower_bound({i, a[1]}));
    contains[a[0]].erase(contains[a[0]].lower_bound({i, a[2]}));
    contains[a[1]].erase(contains[a[1]].lower_bound({i, a[2]}));
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    scan(n);

    Fori(0, n - 2) {
        Forj(0, 3) {
            int x; scan(x);
            t[i].a[j] = x;
            cnt[x]++;
        }
        // sort(t[i].a, t[i].a + 3);

        auto a = t[i].a;
        contains[a[0]].insert({i, a[1]});
        contains[a[0]].insert({i, a[2]});
        contains[a[1]].insert({i, a[2]});
    }

    // get starts
    int st = -1;
    Forinci(1, n) {
        if (cnt[i] == 1) {
            st = i;
            break;
        }
    }

    // get first
    int stseq = -1;
    Fori(0, n - 2) {
        bool wk = false;
        Forj(0, 3)
            wk |= t[i].a[j] == st;
        if (wk) {
            stseq = i;
            break;
        }
    }

    // get 2nd and 3rd
    print(st, ' ');
    int tofinda, tofindb;
    Fori(0, 3) {
        int v = t[stseq].a[i];
        if (cnt[v] == 2) {
            tofinda = v;
            print(v, ' ');
        }
    }

    Fori(0, 3) {
        int v = t[stseq].a[i];
        if (cnt[v] == 3) {
            tofindb = v;
            print(v, ' ');
        }
    }

    // rem first
    rem(stseq);
    cout.flush();

    // loop rest
    int cur = -1;
    Fori(1, n - 2) {
        // debug(i, tofinda, tofindb);
        auto ptr = contains[tofinda].lower_bound({-1, tofindb});
        // debug(ptr == contains[tofinda].end());
        if (ptr == contains[tofinda].end() || ptr->v != tofindb) {
            ptr = contains[tofindb].lower_bound({-1, tofinda}); // find something
        }

        // debug(i, "enter", tofinda, tofindb, ptr->i, ptr->v);
        // Forj(1, n + 1) {
        //     debug(j);
        //     for (auto x : contains[j]) {
        //         debug(x.i, x.v);
        //     }
        // }

        int tmp = tofindb;
        cur = ptr->i;
        auto a = t[cur].a;
        Fori(0, 3) {
            // debug(a[i], tofinda, tofindb);
            if (a[i] != tofinda && a[i] != tofindb) {
                tofindb = a[i];
                break;
            }
        }

        // debug(cur, tmp, tofinda, tofindb);

        tofinda = tmp;
        print(tofindb, ' ');

        rem(cur);
        // debug("remmed");
    }
    print('\n');

    return 0;
}
