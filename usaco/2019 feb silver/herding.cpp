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

const int MAX = 1e5 + 1;
int n,
    arr[MAX];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("herding.in", "r", stdin);
    freopen("herding.out", "w", stdout);

    scan(n);

    for (int i = 0; i < n; i++)
        scan(arr[i]);
    sort(arr, arr + n);

    // Get min
    int r = 0, best = INF;
    for (int i = 0; i < n; i++) {
        while (r < (n - 1) && arr[r] - arr[i] + 1 < n)
            r++;
        if (arr[r] - arr[i] + 1 < n) break;

        int cans = n - (r - i + 1) + (arr[r] - arr[i] + 1 != n);
        if (r - i + 1 == n && arr[r] - arr[i] + 1 != n)
            cans++;
        // debug(r - i + 1, r, i);
        best = min(best, cans);
    }
    cout << best << "\n";

    // Get max
    cout << (max(arr[n - 2] - arr[0], arr[n - 1] - arr[1]) - (n - 2)) << "\n";
    // (arr[r] - arr[l] + 1) - n + 1 = arr[r] - arr[l] - n + 2

    return 0;
}
