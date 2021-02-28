// ./bobs-kingdom.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
#define fs first
#define sn second
using pii = pair<int, int>;

const int MN = 2001;
int R, C,
    H[MN][MN];

int minv = INF;

bool check(int k) {
    auto revH = [&] () {
        for (auto i = 1; i <= R; i++)
            reverse(H[i]+1, H[i]+C+1);
    };
    auto revV = [&] () {
        for (auto i = 1; i <= C; i++) {
            for (int j = 1; j <= R/2; j++)
                swap(H[j][i], H[R-j+1][i]);
        }
    };
    auto checkDMOJ = [&] () {
        int cantR = 0; // needR->max of minv, cantR->min of >minv+k

        int pegmax = -INF, pegmin = INF;

        for (auto i = C; i >= 1; i--) {
            int needR = R+1;
            for (auto j = 1; j <= R; j++) {
                if (H[j][i] == minv) needR = min(needR, j);
                else if (H[j][i] > minv+k) cantR = max(cantR, j);
            }
            if (needR <= cantR) return false;

            for (int j = 1; j <= cantR; j++) {
                pegmax = max(pegmax, H[j][i]);
                pegmin = min(pegmin, H[j][i]);
            }
            if (pegmax - pegmin > k) return false;
        }
        return true;
    };

    bool ans = false;
    for (int i = 0; i < 2; i++) {
        ans |= checkDMOJ();
        revV();
        ans |= checkDMOJ();
        revV();

        revH();
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> R >> C;
    for (auto i = 1; i <= R; i++) {
        for (auto j = 1; j <= C; j++) {
            cin >> H[i][j];
            minv = min(minv, H[i][j]);
        }
    }

    int l = -1, r = 1e9;
    while (l+1 < r) {
        int mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid;
    }
    cout << r << '\n';

    return 0;
}

