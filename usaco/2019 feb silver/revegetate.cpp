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

struct ed {
    int v; char t;
};

const int MN = 1e5 + 1;
int n, m, ba, bb;
vector<ed> matrix[MN];
char bc;
bool vis[MN], clrs[MN];

void tryColor(int cur, bool clr) {
    if (vis[cur]) return;

    vis[cur] = true;
    clrs[cur] = clr;
    for (ed adj : matrix[cur]) {
        if (adj.t == 'D')
            tryColor(adj.v, !clr);
        else
            tryColor(adj.v, clr);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("revegetate.in", "r", stdin);
    freopen("revegetate.out", "w", stdout);

    scan(n, m);

    for (int i = 0; i < m; i++) {
        scan(bc, ba, bb);
        matrix[ba].push_back({bb, bc});
        matrix[bb].push_back({ba, bc});
    }

    int tot = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            tryColor(i, false);
            tot++;
        }
    }

    for (int i = 1; i <= n; i++) {
        bool flag = true;
        for (ed adj : matrix[i]) {
            if (adj.t == 'D')
                flag &= clrs[i] != clrs[adj.v];
            else
                flag &= clrs[i] == clrs[adj.v];
        }
        if (!flag) {
            cout << "0\n";
            return 0;
        }
    }

    cout << "1";
    for (int i = 0; i < tot; i++)
        cout << "0";
    cout << "\n";

    return 0;
}