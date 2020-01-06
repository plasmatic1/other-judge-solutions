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

const int MN = 51;

int qu(int a, int b, int c, int d) {
    cout << a << " " << b << " " << c << " " << d << "\n";
    cout.flush();

    int ret;
    cin >> ret;
    assert(ret != -1);

    return ret;
}

int n,
    grid[MN][MN];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    grid[1][1] = 1;
    grid[n][n] = 0;

    // Set first checkerboard
    for (int i = 3; i <= n; i += 2) {
        int pali = qu(i - 2, 1, i, 1);
        grid[i][1] = grid[i - 2][1] ^ pali ^ 1;
    }

    for (int i = 1; i <= n; i += 2) {
        for (int j = 3; j <= n; j += 2) {
            int pali = qu(i, j - 2, i, j);
            grid[i][j] = grid[i][j - 2] ^ pali ^ 1;
        }
    }

    // Set (2,2)
    int pali = qu(1, 1, 2, 2);
    grid[2][2] = grid[1][1] ^ pali ^ 1;

    for (int i = 4; i <= n; i += 2) {
        int pali = qu(i - 2, 1, i, 1);
        grid[i][1] = grid[i - 2][1] ^ pali ^ 1;
    }

    for (int i = 2; i <= n; i += 2) {
        for (int j = 4; j <= n; j += 2) {
            int pali = qu(i, j - 2, i, j);
            grid[i][j] = grid[i][j - 2] ^ pali ^ 1;
        }
    }

    // Do 4 check
    int pali;
    if (n > 3) {
        pali = qu(1, 1, 1, 4);
    }
    else {
        pali = qu(1, 1, 3, 2);
    }

    

    return 0;
}