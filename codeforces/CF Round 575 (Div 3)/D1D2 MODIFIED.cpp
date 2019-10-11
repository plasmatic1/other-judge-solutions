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

const int MN = 2e5;
int n, k;
vector<int> pfx;
string s, ans;

namespace asjdofaisdfoisdjfo {
    int idxOf[(int)'Z' + 1];
    const string S = "RGB"; 

    void init() {
        idxOf['G'] = 1;
        idxOf['B'] = 2;
    }
    char next(char ch) {
        return S[(idxOf[(int)ch] + 1) % 3];
    }
    char prev(char ch) {
        return S[(idxOf[(int)ch] + 2) % 3]; // - 1 + 3
    }
}
using asjdofaisdfoisdjfo::init; using asjdofaisdfoisdjfo::prev; using asjdofaisdfoisdjfo::next; 

void solve() {
    pfx.push_back(0);
    char last = prev(s[0]);
    for (int i = 0; i < n; i++) {
        char prevCur = prev(s[i]);
        while (last != prevCur) {
            pfx.push_back(1);
            last = next(last);
        }
        pfx.push_back(0);
        last = s[i];
    }

    debug(pfx);

    int sz = pfx.size();
    for (int i = 1; i <= sz; i++)
        pfx[i] += pfx[i - 1];
    
    int best = INF;
    for (int i = k; i <= sz; i++)
        best = min(best, pfx[i] - pfx[i - k]);
    cout << best << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();

    int t; scan(t);
    while (t--) {
        scan(n, k, s);
        pfx.clear();

        solve();
    }

    return 0;
}