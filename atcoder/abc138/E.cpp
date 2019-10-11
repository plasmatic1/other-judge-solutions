#include <bits/stdc++.h>

using namespace std;

// Common DS shorteners
using ll = long long; using ull = unsigned long long;
using pii = pair<int, int>; using pll = pair<ll, ll>;
template <typename T> using vec = vector<T>;
template <typename K, typename V> using mp = unordered_map<K, V>;
template <typename K> using us = unordered_set<K>;
using vi = vec<int>; using vl = vec<ll>; using vpi = vec<pii>; using vpl = vec<pll>;
// Shorthand Macros
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define mpr make_pair
#define pb push_back
// Shorthand Functions
template<typename T> inline void maxa(T& st, T v) { st = max(st, v); }
template<typename T> inline void mina(T& st, T v) { st = min(st, v); }
// Out operators and printing for arrays and vectors
template <typename T> ostream& operator<<(ostream& out,vector<T> iter){out<<"[";for(auto t:iter){out<<t<<", ";}out<<"]";return out;}
template <typename T> void printDebug(T *arr,int sz){cout<<"[";for(int i=0;i<sz;i++){cout<<arr[i]<<", "; } cout<<"]\n";}
template <typename T> void printArray(T *arr,int sz){for(int i=0;i<sz;i++){cout<<arr[i]<<" "; } cout<<"\n";}
#define OUT_OPERATOR(type, propa, propb) ostream& operator<<(ostream& out,type obj){out<<"("<<#propa<<"="<<obj. propa<<", "<<#propb<<"="<<obj. propb<<")";return out;}
// I/O Operations
inline void scan(){}
template<typename F, typename... R> inline void scan(F &f,R&... r){cin>>f;scan(r...);}
inline void println(){cout<<"\n";}
template<typename F, typename... R> inline void println(F f,R... r){cout<<f<<" ";println(r...);}
inline void print(){}
template<typename F, typename... R> inline void print(F f,R... r){cout<<f;print(r...);}
// Debugging
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R>
void debug_(F f,R... r){int bc=0;while (bc != 0 || dnms_[di_] != ','){if (dnms_[di_] == '(') {bc++;}else if (dnms_[di_] == ')') {bc--;}cout << dnms_[di_++];}di_++;cout << ": " << f << ",";debug_(r...);}
#define debug(...) do{dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__);}while(0)

struct ed {
    int v, w = INF;

    bool operator<(const ed &o) const {
        return w < o.w;
    }
};

inline int let(char c) { return c - 'a'; }

const int MN = 2e5 + 1, LS = 26;
int n, m;
vi idxOf[LS];
ed g[MN][LS];
string s, t;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(s, t);
    n = s.length();
    m = t.length();

    for (int i = 0; i < n; i++)
        idxOf[let(s[i])].pb(i);
    
    set<pii> used;
    for (int i = 1; i < m; i++) {
        int a = let(t[i - 1]), b = let(t[i]);
        
        auto p = mpr(a, b);
        if (used.find(p) != used.end()) continue;
        used.insert(p);

        if (idxOf[b].empty()) {
            println(-1);
            return 0;
        }

        for (int id : idxOf[a]) {
            auto nxtPtr = upper_bound(idxOf[b].begin(), idxOf[b].end(), id);
            if (nxtPtr == idxOf[b].end())
                mina(g[id][b], {idxOf[b][0], n - id + idxOf[b][0]});
            else
                mina(g[id][b], {*nxtPtr, *nxtPtr - id});
        }
    }

    if (idxOf[let(t[0])].empty()) {
        println(-1);
        return 0;
    }

    ll ans = idxOf[let(t[0])][0], id = ans;
    for (int i = 1; i < m; i++) {
        int clet = let(t[i]);

        if (g[id][clet].w == INF) {
            println(-1);
            return 0;
        }

        auto edge = g[id][clet];
        id = edge.v;
        ans += edge.w;
    }

    println(ans + 1);

    return 0;
}
