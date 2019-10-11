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

const string DIG[10] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"},
    TEENS[10] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"},
    TENS[10] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

string numToString(int x) {
    if (0 <= x && x <= 9)
        return DIG[x];
    else if (10 <= x && x <= 19)
        return TEENS[x - 10];
    else if (20 <= x && x <= 99)
        return TENS[x / 10] + numToString(x % 10);
    else if (100 <= x && x <= 999)
        return DIG[x / 100] + "hundred" + (x % 100 ? "and" : "") + numToString(x % 100);
    else if (x == 1000)
        return "onethousand";
    assert(0);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (int i = 1; i <= 1000; i++) {
        debug(i, numToString(i));
    }
    
    int totLen = 0;
    for (int i = 1; i <= 1000; i++) {
        totLen += numToString(i).length();
    }
    debug(totLen);

    return 0;
}