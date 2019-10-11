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

const ll MOD = 998244353;
const int MN = 3e5 + 1;
int n;
pii pp[MN];
ll dp[MN], bit[MN], facts[MN];
ll sortedA = 0, sortedB = 0;
ll tot = 0, sortedBoth = 0;

map<int, int> ctr, ctr2;
map<int, map<int, int>> ctrBoth;

// N! -Amount of ways to sort A, -amount of ways to sort B, +amount of ways to sort A and B 

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n);

    facts[0] = 1;
    for (int i = 1; i <= n; i++) {
        scan(pp[i].first, pp[i].second);
        facts[i] = (facts[i - 1] * i) % MOD;
    }

    // sort(pp + 1, pp + n + 1);

    for (int i = 1; i <= n; i++) {
        ctr[pp[i].first]++;
        ctr2[pp[i].second]++;
        ctrBoth[pp[i].first][pp[i].second]++;
    }

    sortedA = 1;
    sortedB = 1;
    for (auto p : ctr)
        sortedA = (sortedA * facts[p.second]) % MOD;
    for (auto p : ctr2)
        sortedB = (sortedB * facts[p.second]) % MOD;
    
    tot = facts[n];

    bool canSortBoth = true;
    for (auto it = ctrBoth.begin(); it != ctrBoth.end(); it++) {
        auto nxt = it; nxt++;
        if (nxt == ctrBoth.end())
            break;
        
        // Check max of cur <= min of next
        // debug(it->first, (--it->second.end())->first, nxt->second.begin()->first);
        canSortBoth &= (--it->second.end())->first <= nxt->second.begin()->first;
    }

    if (canSortBoth) {
        sortedBoth = 1;
        for (auto mp : ctrBoth) {
            // debug(mp.first);
            for (auto val : mp.second) {
                int cnt = val.second;
                // debug(val.first, cnt);
                sortedBoth = (sortedBoth * facts[cnt]) % MOD;
            }
        }
    }

    tot -= sortedA;
    tot = (tot + MOD) % MOD;
    tot -= sortedB;
    tot = (tot + MOD) % MOD;
    tot += sortedBoth;
    tot %= MOD;

    // debug(sortedA, sortedB, sortedBoth);

    println(tot);

    return 0;
}