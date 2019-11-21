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
 
struct px {
    ll x, y;
};
 
const int MN = 2e5 + 1;
string s;
int n;
px pos[MN], pfxMin[MN], pfxMax[MN], sfxMin[MN], sfxMax[MN];
 
#define setAll(x) pos[(x)] = pfxMin[(x)] = pfxMax[(x)] = sfxMin[(x)] = sfxMax[(x)]
 
const int DIRS[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    int sssss; scan(sssss);
    while (sssss--) {
        scan(s);
        n = s.length();
 
        setAll(0) = {0, 0};
        for (int i = 1; i <= n; i++) {
            switch(s[i- 1]) {
                case 'D':
                    setAll(i) = {pos[i - 1].x, pos[i - 1].y + 1};
                    break;
                case 'A':
                    setAll(i) = {pos[i - 1].x, pos[i - 1].y - 1};
                    break;
                case 'S':
                    setAll(i) = {pos[i - 1].x + 1, pos[i - 1].y};
                    break;
                case 'W':
                    setAll(i) = {pos[i - 1].x - 1, pos[i - 1].y};
                    break;
            }
 
            // debug(i, pfxMin[i].x, pfxMin[i].y, pfxMax[i].x, pfxMax[i].y);
        }
 
        for (int i = 1; i <= n; i++) {
            pfxMin[i].x = min(pfxMin[i].x, pfxMin[i - 1].x);
            pfxMin[i].y = min(pfxMin[i].y, pfxMin[i - 1].y);
            pfxMax[i].x = max(pfxMax[i].x, pfxMax[i - 1].x);
            pfxMax[i].y = max(pfxMax[i].y, pfxMax[i - 1].y);
            // debug(pfxMax[i].x, pfxMax[i].y, pfxMin[i].x, pfxMin[i].y);
        }
 
        for (int i = n - 1; i >= 0; i--) {
            sfxMin[i].x = min(sfxMin[i].x, sfxMin[i + 1].x);
            sfxMin[i].y = min(sfxMin[i].y, sfxMin[i + 1].y);
            sfxMax[i].x = max(sfxMax[i].x, sfxMax[i + 1].x);
            sfxMax[i].y = max(sfxMax[i].y, sfxMax[i + 1].y);
        }
 
        ll bestArea = (pfxMax[n].x - pfxMin[n].x + 1) * (pfxMax[n].y - pfxMin[n].y + 1);
        // debug(pfxMax[n].x - pfxMin[n].x, pfxMax[n].y - pfxMin[n].y);
 
        // debug(bestArea);
 
        for (int i = 1; i <= n; i++) {
            // Insert instruction before I
            for (auto dir : DIRS) {
                ll xMin, yMin, xMax, yMax;
 
                // xMin = min(pos[i - 1].x + dir[0], min(pfxMin[i - 1].x, sfxMin[i].x + dir[0]));
                // xMax = max(pos[i - 1].x + dir[0], max(pfxMax[i - 1].x, sfxMax[i].x + dir[0]));
                // yMin = min(pos[i - 1].y + dir[1], min(pfxMin[i - 1].y, sfxMin[i].y + dir[1]));
                // yMax = max(pos[i - 1].y + dir[1], max(pfxMax[i - 1].y, sfxMax[i].y + dir[1]));
                xMin = min(pos[i - 1].x + dir[0], min(pfxMin[i - 1].x, sfxMin[i].x + dir[0]));
                xMax = max(pos[i - 1].x + dir[0], max(pfxMax[i - 1].x, sfxMax[i].x + dir[0]));
                yMin = min(pos[i - 1].y + dir[1], min(pfxMin[i - 1].y, sfxMin[i].y + dir[1]));
                yMax = max(pos[i - 1].y + dir[1], max(pfxMax[i - 1].y, sfxMax[i].y + dir[1]));
 
                // debug(i, xMin, xMax, yMin, yMax, dir[0], dir[1]);
 
                bestArea = min(bestArea, (xMax - xMin + 1) * (yMax - yMin + 1));
            }
        }
 
        cout << bestArea << "\n";
    }
 
    return 0;
}
