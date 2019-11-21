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
 
// int t;
int n;
string s, t;
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    int tDD; scan(tDD);
    while (tDD--) {
        scan(s,t);
        reverse(s.begin(), s.end()  );reverse(t.begin(), t.end());
 
        int id2 = -1;
        for (int i = 0; i < t.length(); i++) {
            if (t[i] == '1') {
                id2 = i;
                break;
            }
        }
 
        int id = -1;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '1' && i >= id2) {
                id = i;
                break;
            }
        }
 
        // debug(id2, id, s, t);
 
        if (id == -1) { 
            cout << "0\n";
            continue;
        }
 
        cout << (id - id2) << "\n";
    }
 
    return 0;
}