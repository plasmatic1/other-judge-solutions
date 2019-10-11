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

const int MN = 101;
int n, k;
string s;
ll dp1[MN][MN], dp2[MN][MN]; // i -> index, j -> size, Include letter i, not include letter i

bool cmp(const string &a, const string &b) {
    return a.length() > b.length();
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    scan(n, k, s);

    dp1[1][1] = dp2[1][0] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int l = 1; l < i; l++) {
                dp2[i][j] += dp2[l][j] + dp1[l][j];
                dp1[i][j] += dp1[l][j - 1];
                if (s[i - 1] != s[l - 1])
                    dp1[i][j] += dp2[l][j - 1];
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << i << ": ";
        printArray(cout, dp1[i], n + 1);
        printArray(cout, dp2[i], n + 1);
        cout << "\n";
    }

    // if (subs.size() < (size_t)k)
    //     cout << "-1\n";
    // else {
    //     int tot = 0;
    //     for (int i = 0; i < k; i++)
    //         tot += n - subs[i].length(), debug(i, subs[i]);
    //     cout << tot << "\n";
    // }

    return 0;
}
