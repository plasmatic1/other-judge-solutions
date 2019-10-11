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


const ll MOD = 1e9 + 7;

ll fastPow(ll x, ll y) {
    if (!y) return 1LL;
    return ((y & 1 ? x : 1) * fastPow((x * x) % MOD, y >> 1)) % MOD;
}
ll divMod(ll x, ll y) { return (x * fastPow(y, MOD - 2)) % MOD; }

ll facts[100];
void init() {
    facts[0] = facts[1] = 1;
    for (int i = 2; i < 100; i++) facts[i] = (facts[i - 1] * i) % MOD;
}
ll choose (int n, int k) { return divMod(facts[n], (facts[k] * facts[n - k]) % MOD); }

ll counts[65];
void countNumsWithSetBits(ll bound) {
    for (; bound; bound -= bound & -bound) {
        ll popbound = __builtin_popcountll(bound);
        if (__builtin_popcountll(bound + 1) == 1) {
            for (int i = 1; i <= popbound; i++)
                counts[i] = (counts[i] + choose(popbound, i)) % MOD;
            return;
        }

        ll sub = bound & -bound, next = bound - sub;
        int popnxt = __builtin_popcountll(next), popsub = __builtin_popcountll(sub - 1);

        debug(bound, sub, next, popbound, popnxt, popsub);
        
        counts[popbound]++;
        for (int i = 0; i <= popsub; i++)
            counts[i + popnxt] = (counts[i + popnxt] + choose(popsub, i)) % MOD;
    }
}

// a(0) = 0, a(x) = 2^(popcount(x) - 1) + a(x-1)
ll func(ll bound) {
    memset(counts, 0, sizeof counts);
    countNumsWithSetBits(bound);

    for (int i = 1; i <= 10; i++)
        debug(bound, i, counts[i]);

    ll tot = 0;
    for (int i = 1; i <= 60; i++) {
        ll mul = counts[i];
        tot = (tot + fastPow(2, i - 1) * mul) % MOD;
    }
    return tot;
}

ll l, r;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(l, r);

    init();

    ll ans = (func(r) - func(l - 1) + MOD) % MOD;
    println(ans);

    return 0;
}
