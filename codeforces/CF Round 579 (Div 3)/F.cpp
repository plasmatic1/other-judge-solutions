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

const int MN=101,MV=60001;
int n,ba,bb;
using pi=pair<int,int>;
using vpi=vector<pi>;

vpi a,b;
int r;

bool cmp(const pi &a, const pi& b){
    if(a.second==b.second){
        return a.first>b.first;
    }
    return a.second>b.second;
}

int dp[MV];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n,r);

    for (int i = 0; i < n; i++) {
        scan(ba,bb);
        if(bb>0){
            a.push_back(make_pair(ba,bb));
        }
        else{
            b.push_back(make_pair(ba,bb));
        }
    }
    sort(a.begin(), a.end());
    int tot=0;
    for(auto x:a){
        if(x.first <=r) {
            r+=x.second;tot++;
        }
    }

    sort(b.begin(), b.end());
    reverse(b.begin(), b.end());

int bs=b.size();
    for (int i = 0; i < bs; i++) {
        for
    }

    // sort(b.begin(), b.end(),cmp);
    // for(auto x:b){
    //     if (x.first<=r){
    //         r+=x.second;
    //         tot++;
    //     }
    // }

    cout << tot<<"\n";

    return 0;
}