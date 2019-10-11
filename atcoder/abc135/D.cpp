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

const int MN = 1e5 + 1, MMO = 13 + 1;
const ll MOD = 1e9 + 7;
int n;
ll dp[MN][MMO];
string s;

inline int sub(int i, int j) {
    return (i - j + 13) % 13;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(s);
    n = s.length();
    // s = " " + s;

    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < MMO; j++) {
            if (!dp[i][j])
                continue;
            
            if (s[i] == '?') {
                for (int k = 0; k <= 9; k++) {
                    ll &val = dp[i + 1][(j * 10 + k) % 13];
                    val = (val + dp[i][j]) % MOD;
                }
            }
            else {
                ll &val = dp[i + 1][(j * 10 + (int)(s[i] - '0')) % 13];
                val = (val + dp[i][j]) % MOD;
            }
                // dp[i][j] = dp[i - 1][sub(j, (int)(s[i] - '0'))];
        }
    }

    cout << dp[n][5] << "\n";

    return 0;
}