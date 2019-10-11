#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Defines and one-liners
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
template <typename T> inline T& back(vector<T> &vec) { return *(vec.end() - 1); }
template <typename T> inline void pop(vector<T> &vec) { return vec.erase(vec.end() - 1); }

// Scan, Debug, and other nonsense
template <typename T> ostream& operator<<(ostream& out,vector<T> iter){out<<"[";for(auto t:iter){out<<t<<", ";}out<<"]";return out;}
template <typename T> void printArray(ostream& out,T* arr,int sz){out<<"[";for(int i=0;i<sz;i++){out<<arr[i]<<", "; } out<<"]";}
#define OUT_OPERATOR(type, propa, propb) ostream& operator<<(ostream& out,type obj){out<<"("<<#propa<<"="<<obj. propa<<", "<<#propb<<"="<<obj. propb<<")";return out;}

void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F f,R... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

const int MN = 1e7 + 1;
unordered_map<ll, int> dp;

int rec(ll x) {
    if (x == 1) return 1;
    if (dp.find(x) != dp.end()) return dp[x];
    if (x & 1) return dp[x] = rec(x * 3 + 1) + 1;
    else return dp[x] = rec(x >> 1) + 1;
}

void recTest(int x, int it =0) {
    if (x == 1) return;
    debug(x, it);

    if (x & 1) 
        recTest(x * 3 + 1, it + 1);
    else 
        recTest(x >> 1, it + 1);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // memset(dp, -1, sizeof dp);

    int best = -1, bestI = -1;
    for (int i = 1; i <= 1000000; i++) {
        int ret = rec(i);
        if (ret > best) {
            best = ret;
            bestI = i;
        }

        if (i % 10000 == 0)
            debug(i, best, bestI);
    }

    debug(best, bestI);

    // recTest(626331, 1);

    return 0;
}
