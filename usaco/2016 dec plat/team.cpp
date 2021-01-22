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

const int MN = 1e3 + 2, MK = 10 + 2, MOD = 1e9 + 9;
int n, m, k,
    a[MN], b[MN], dp[MK][MN][MN];

inline void inc(int& toInc, int amt) {
    toInc = (toInc + amt) % MOD;
}

int main(){
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    freopen("team.in", "r", stdin);
    freopen("team.out", "w", stdout);

    scan(n, m, k);

    for (int i = 1; i <= n; i++)
        scan(a[i]);
    for (int i = 1; i <= m; i++)
        scan(b[i]);
    sort(a + 1, a + n + 1, greater<int>());
    sort(b + 1, b + m + 1, greater<int>());

    // printArray(cout, a, n + 1); cout << "\n";
    // printArray(cout, b, m + 1); cout << "\n";

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            dp[0][i][j] = 1;

    for (int c1 = 1; c1 <= k; c1++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int &cur = dp[c1][i][j];
                if (a[i] > b[j]) {
                    inc(cur, dp[c1 - 1][i - 1][j - 1]);
                }
                inc(cur, dp[c1][i - 1][j]);
                inc(cur, dp[c1][i][j - 1]);
                inc(cur, -dp[c1][i - 1][j - 1]);
            }
        }
    }

    // for (int i = 0; i <= k; i++) {
    //     debug(i);
    //     for (int j = 0; j <= n; j++) {
    //         cout << "[";
    //         for (int l = 0; l <= m; l++)
    //             cout << dp[i][j][l] << " ";
    //         cout << "]\n";
    //     }
    // }

    // int tot = 0;
    // for (int i = 0; i <= n; i++)
    //     for (int j = 0; j <= m; j++)
    //         inc(tot, dp[k][i][j]);

    cout << (dp[k][n][m] + MOD) % MOD << "\n";

    return 0;
}