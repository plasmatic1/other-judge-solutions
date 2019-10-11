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

const int MW = 1e3 + 10, MWV = 1e3 + 1;
int n, k, ba, bb, bc, bd,
    pfx[MW][MW];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("paintbarn.in", "r", stdin);
    freopen("paintbarn.out", "w", stdout);

    scan(n, k);

    for (int i = 0; i < n; i++) {
        scan(ba, bb, bc, bd);
        ba++; bb++; bc++; bd++;

        pfx[ba][bb]++;
        pfx[ba][bd]--;
        pfx[bc][bb]--;
        pfx[bc][bd]++;
    }

    for (int i = 1; i <= MWV; i++)
        for (int j = 1; j <= MWV; j++)
            pfx[i][j] += pfx[i - 1][j] + pfx[i][j - 1] - pfx[i - 1][j - 1];
    
    // for (int i = 0; i <= 10; i++)
    //     printArray(cout, pfx[i], 11), cout << "\n";
    
    int tot = 0;
    for (int i = 1; i <= MWV; i++)
        for (int j = 1; j <= MWV; j++)
            tot += pfx[i][j] == k;
    cout << tot << "\n";

    return 0;
}

// nick = ba