// ./median-sort.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

int ask(int i, int j, int k) {
    cout << i << ' ' << j << ' ' << k << '\n'; cout.flush();
    int res; cin >> res; assert(res != -1);
    return res;
}

int N, Q;

void solve() {
    vector<int> ans{1, 2};
    for (auto i = 3; i <= N; i++) {
        int l = -1, r = ans.size()-1, loc = -1; // if l==r
        while (l < r) {
            int d = (r-l-1)/3, m1 = l+d+1, m2 = r-d;
            if (l + 1 == r) { m1 = l; m2 = r; } // special case
            if (m1 == -1) { m1++; m2++; }

            int lo = ans[m1], hi = ans[m2], res = ask(lo, hi, i);
            if (res == lo) {
                r = m1-1;
            }
            else if (res == hi) {
                l = m2;
            }
            else {
                l = m1;
                r = m2-1;
            }
        }
        loc = l+1;
        ans.insert(ans.begin()+loc, i);
    }

    for (auto x : ans) cout << x << ' ';
    cout << '\n'; cout.flush();
    int verdict; cin >> verdict;
    assert(verdict == 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T >> N >> Q;
    Q *= T;

    for (int caseno = 1; caseno <= T; caseno++)
        solve();
}

