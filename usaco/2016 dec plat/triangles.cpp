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

struct p {
    int x, y;
    bool operator<(const p &o) const {
        return x < o.x;
    }
};

struct slope {
    ll xDelta, yDelta;
    slope() : xDelta(0), yDelta(0) {}
    slope(p &a, p &b) : xDelta(b.x - a.x), yDelta(b.y - a.y) {
        if (xDelta <= 0) {
            xDelta *= -1;
            yDelta *= -1;
        }
    }
    bool operator<(const slope &o) const {
        // debug(*this, o, yDelta * o.xDelta < o.yDelta * xDelta);
        return yDelta * o.xDelta < o.yDelta * xDelta;
    }
    friend ostream& operator<<(ostream &out, const slope sl) {
        out << "(" << sl.yDelta << " / " << sl.xDelta << " (" << ((double)sl.yDelta / sl.xDelta) << "))";
        return out;
    }
};

const int MN = 3e2 + 1;
int n, ranksIPtr, ranksJPtr,
    cnt[MN], ctot[MN];
p pts[MN];
slope slopeFrom[MN][MN], ranksI[MN], ranksJ[MN];

// (x, v) add v to the xth element of the array
// (x) sum of elements from 1 to x (inclusive)

// Binary indexed tree
int cbs, bit[MN];
inline void upd(int x) {
    for (; x <= cbs; x += x & -x)
        bit[x]++;
}

inline int query(int x) {
    int sum = 0;
    for (; x; x -= x & -x)
        sum += bit[x];
    return sum;
}

// rank compress
inline int rankOfI(slope &val) {
    return lower_bound(ranksI, ranksI + ranksIPtr, val) - ranksI + 1;
}

inline int rankOfJ(slope &val) {
    return lower_bound(ranksJ, ranksJ + ranksJPtr, val) - ranksJ + 1;
}

// reset BIT
inline void resetBit() {
    memset(bit, 0, sizeof bit);
}

int main(){
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    freopen("triangles.in", "r", stdin);
    freopen("triangles.out", "w", stdout);

    scan(n);

    for (int i = 0; i < n; i++)
        scan(pts[i].x, pts[i].y);
    sort(pts, pts + n);

    // for (int i = 0; i < n; i++)
    //     debug(i, pts[i].x, pts[i].y);

    // Precalculate
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            slopeFrom[i][j] = slope(pts[i], pts[j]);

    // debug(ranks);

    for (int i = 0; i < n; i++) {
        ranksIPtr = 0;
        for (int j = i + 1; j < n; j++)
            ranksI[ranksIPtr++] = slopeFrom[i][j];
        sort(ranksI, ranksI + ranksIPtr);

        for (int j = i + 1; j < n; j++) {
            ranksJPtr = 0;
            for (int k = i; k < j; k++)
                ranksJ[ranksJPtr++] = slopeFrom[k][j]; // k > j, l -> r
            sort(ranksJ, ranksJ + ranksJPtr);
            // printArray(cout, ranksJ, ranksJPtr); cout << "\n";

            // Calculate left side (dividing point K)
            int rankIJ = rankOfI(slopeFrom[i][j]); // precalculate
            resetBit();
            cbs = ranksIPtr;
            for (int k = i + 1; k < j; k++) {
                int rankIK = rankOfI(slopeFrom[i][k]);
                // debug("lhs", i, j, k, slopeFrom[i][k], slopeFrom[i][j], rankIK, rankIJ);
                ctot[k] = query(max(rankIK, rankIJ) - 1) - query(min(rankIK, rankIJ));
                upd(rankIK);
            }

            // Calculate right side (dividing point K)
            int rankJI = rankOfJ(slopeFrom[i][j]);
            resetBit();
            cbs = ranksJPtr;
            for (int k = j - 1; k > i; k--) {
                int rankJK = rankOfJ(slopeFrom[k][j]); // j > k, l -> r
                // debug("rhs", i, j, k, slopeFrom[k][j], slopeFrom[i][j], rankJK, rankJI, ctot[k]);
                ctot[k] += query(max(rankJK, rankJI) - 1) - query(min(rankJK, rankJI));
                upd(rankJK);
                // debug(bit.query(16) - bit.query(15));
                // debug(bit.query(17) - bit.query(15));
            }

            for (int k = i + 1; k < j; k++) {
                cnt[ctot[k]]++;
                // debug(i, j, k, ctot[k]);
            }
        }
    }

    for (int i = 0; i < n - 2; i++)
        cout << cnt[i] << "\n";

    return 0;
}