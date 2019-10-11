#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F f,R... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

template <ll MOD>
struct FastPow {
    ll fastPow(ll x, ll y) {
        ll ans = 1;
        for (ll mag = 1, cpow = x; mag <= y; mag <<= 1, cpow = (cpow * cpow) % MOD)
            if (y & mag)
                ans = (ans * cpow) % MOD;
        return ans;
    }
    ll divMod(ll x, ll y) { return (x * fastPow(y, MOD - 2)) % MOD; }
};

const int MAX = 100001;
const ll MOD = 1000000007;
int pars[MAX];
ll dp[MAX][2][3];
vector<int> matrix[MAX];
FastPow<MOD> fp;

void setPar(int cur, int par) {
    pars[cur] = par;
    for (int adj : matrix[cur])
        if (adj ^ par)
            setPar(adj, cur);
}

ll rec(int cur, bool clr, int sz) {
    ll &ret = dp[cur][clr][sz];
    if (ret != -1) return ret;
    
    ret = 1;
    if (sz == 1) {
        for (int adj : matrix[cur])
            if (adj ^ pars[cur])
                ret = (ret * rec(adj, !clr, 2)) % MOD;
    }
    else { // sz == 2
        for (int adj : matrix[cur])
            if (adj ^ pars[cur])
                ret = (ret * (rec(adj, !clr, 2) + rec(adj, clr, 1) + rec(adj, clr, 2))) % MOD;
        ret = (ret - rec(cur, clr, 1) + MOD) % MOD;
    }

    return ret;
}

// Complete the kingdomDivision function below.
int kingdomDivision(int n, vector<vector<int>> roads) {
    for (int i = 0; i < n - 1; i++) {
        matrix[roads[i][0]].push_back(roads[i][1]);
        matrix[roads[i][1]].push_back(roads[i][0]);
    }

    setPar(1, -1);
    memset(dp, -1, sizeof dp);
    ll ans = (rec(1, 0, 2) + rec(1, 1, 2)) % MOD;
    cout << ans << "\n";
    return ans;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> roads(n-1);
    for (int i = 0; i < n-1; i++) {
        roads[i].resize(2);

        for (int j = 0; j < 2; j++) {
            cin >> roads[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int result = kingdomDivision(n, roads);

    fout << result << "\n";

    fout.close();

    return 0;
}
