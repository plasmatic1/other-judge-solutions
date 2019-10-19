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

struct ed {
    int v; ll w;
};

struct ed2 {
    int v, i; ll w;
    Cmplt(ed2) {
        return w > o.w;
    }
};

struct p {
    int i; ll w;

    Cmplt(p) {
        return i == o.i ? w < o.w : i < o.i;
    }
};

const int MN = 301;
int n, m, l, Q;
p dis[MN][MN]; // A, B, # of times filled
vec<ed> g[MN];

priority_queue<ed2> nxt;
void dijk(int st, p dis[MN]) {
    dis[st] = {0, 0LL};
    nxt.push({st, 0, 0});

    while (!nxt.empty()) {
        ed2 cur = nxt.top(); nxt.pop();
        if (cur.i > dis[cur.v].i || cur.w > dis[cur.v].w) continue;

        for (ed adj : g[cur.v]) {
            p alt = {cur.i, cur.w + adj.w};

            if (alt.w > l) {
                alt = {cur.i + 1, adj.w};
                if (alt < dis[adj.v]) {
                    dis[adj.v] = alt;
                    nxt.push({adj.v, alt.i, alt.w});
                }
            }
            else {
                if (alt < dis[adj.v]) {
                    dis[adj.v] = alt;
                    nxt.push({adj.v, alt.i, alt.w});
                }
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, m, l);

    Fori(0, m) {
        int a, b, c;
        scan(a, b, c);

        if (c > l) continue; // cannot be used

        g[a].pb({b, c});
        g[b].pb({a, c});
    }

    memset(dis, 0x3f, sizeof dis);
    Forinci(1, n)
        dijk(i, dis[i]);

    scan(Q);
    while (Q--) {
        int s, t; scan(s, t);

        // if (dis[s][t] == LLINF)
        //     println(-1);
        // else {
        //     // ll d = dis[s][t];
        //     // println(d / l);
        // }

        if (dis[s][t].i == INF)
            println(-1);
        else
            println(dis[s][t].i);
    }

    return 0;
}
