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

struct p{
    ll a,b;
    Cmplt(p){return a<o.a;}
    Cmpgt(p){return a>o.a;}
};
int n,A[21],B[21];
ll h;

const int MN=5e5+10;
int bit[MN];
int qu(int x){
    int s=0;
    for(;x;x-=x&-x)s+=bit[x];
    return s;
}
void inc(int x){
    for(;x<MN;x+=x&-x)bit[x]++;
}

vl ranks;
int rk(ll x){
    return lower_bound(ranks.begin(), ranks.end(),x)-ranks.begin()+1;
}

vec<p> solve(int l, int r) {
    int sz = r-l+1;
    vec<p> ret;

    int sel[21];
    function<void(int)> rec = [&](int cur) {
        if (cur == sz) {
            ll ta=0,tb=0;
            Fori(0,sz){
                if (sel[i]&1)
                    ta+=A[l+i];
                if (sel[i]&2)
                    tb+=B[l+i];
            }
            ret.pb({ta,tb});
            return;
        }

        Forinci(1, 3) {
            sel[cur] = i;
            rec(cur+1);
        }
    };
    // ret.pb({0,0});

    rec(0);
    return ret;
}

ll solve(){
    int mid=n/2;
    auto aa=solve(0,mid),bb=solve(mid+1,n-1);
    // debug(mid);

    sort(aa.begin(), aa.end());
    // sort(bb.begin(), bb.end());
    // bb.resize(unique(bb.begin(), bb.end()) - bb.begin());
    sort(bb.begin(), bb.end(),greater<p>());
    ll tot=0;
    int ptr=0,bsz=bb.size();

    for(auto x:aa){ranks.pb(x.b);ranks.pb(h-x.b);}
    for(auto x:bb){ranks.pb(x.b);}
    sort(ranks.begin(), ranks.end());

    // for(auto x:aa)debug("aa",x.a,x.b);
    // for(auto x:bb)debug("bb",x.a,x.b);

    // vl bs;
    for (auto x : aa) {
        while(ptr<bsz&&x.a+bb[ptr].a>=h){
            // bs.pb(bb[ptr].b);
            // int rkk=rk(bb[ptr].b);debug('+',bb[ptr].b,rkk);
            inc(rk(bb[ptr].b));
            ptr++;
        }
        tot+=qu(MN-1)-qu(rk(h-x.b)-1);
    }

    return tot;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;scan(T);int cno=1;
    while (T--) {
        scan(n,h);
        Fori(0,n)scan(A[i]);
        Fori(0,n)scan(B[i]);
        ranks.clear();
        memset(bit,0,sizeof bit);
        cout<<"Case #"<<cno<<": "<<solve()<<"\n";cno++;
    }
    return 0;
}
