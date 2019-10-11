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

const int MN = 3e5 + 1;
int n, m, k;
ll pfx[MN];

ll ceilDiv(ll a, ll b) {
    return (a + b - 1) / b;
}

ll sim(int sz) {
    if (sz < 0) return -LLINF;

    ll best = -LLINF;
    for (int i = sz; i <= n; i++)
        best = max(best, pfx[i] - pfx[i - sz]);
    return best - k * ceilDiv(sz, m);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, m, k);

    for (int i = 1; i <= n; i++) {
        scan(pfx[i]);
        pfx[i] += pfx[i - 1];
    }

    int l = -1, r = n + 1;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        if (sim(mid - 1) < sim(mid)) // before peak
            l = mid;
        else
            r = mid;
    }

    // debug(l, r);
    cout << sim(l) << "\n";

    return 0;
}