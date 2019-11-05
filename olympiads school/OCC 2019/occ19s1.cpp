#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Defines
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f

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

struct p {
    int i; ll x;
    bool operator<(const p &o) const {
        return x < o.x;
    }
};
OUT_OPERATOR(p, i, x)

ll a, b, c, d, e, f, g, h, ans = 0;
vector<p> xs, ys;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(a, b, c, d, e, f, g, h);
    ans = abs(c - a) * abs(d - b) + abs(g - e) * abs(h - f);

    xs = {{0, a}, {0, c}, {1, e}, {1, g}};
    ys = {{0, b}, {0, d}, {1, f}, {1, h}};
    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());

    // debug(xs);debug(ys);

    // Check if they intersect
    if ((xs[0].i != xs[1].i || xs[2].i != xs[3].i) && 
        (ys[0].i != ys[1].i || ys[2].i != ys[3].i))
        ans -= (xs[2].x - xs[1].x) * (ys[2].x - ys[1].x);
    
    cout << ans << "\n";

    return 0;
}