// p3.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int N, K;
    cin >> N >> K;
    vector<int> A(N), B(N);
    for (auto &x : A) cin >> x;
    for (auto &x : B) cin >> x;

    auto run2 = [&] () {
        sort(A.begin(), A.end());
        ll res = -LLINF;
        do {
            ll cur = 0;
            for (auto i = 0; i < K; i++)
                cur += A[i] * B[i];
            if (cur>res) {
                printf("newbest=%lld\n", cur);
                for (auto i = 0; i < K; i++)
                    printf("%d %d\n", A[i],B[i]);
                res = cur;
            }
        } while (next_permutation(A.begin(), A.end()));
        return res;
    };
    auto run = [&] () {
        vector<int> aneg, bneg, apos, bpos;
        // deque<int> aneg, bneg, apos, bpos;
        for (auto x : A) {
            if (x <= 0) aneg.push_back(-x);
            else apos.push_back(x);
        }
        sort(apos.begin(), apos.end());
        sort(aneg.begin(), aneg.end());
        for (auto x : B) {
            if (x <= 0) bneg.push_back(-x);
            else bpos.push_back(x);
        }
        sort(bpos.begin(), bpos.end());
        sort(bneg.begin(), bneg.end());

        ll res = 0;
        vector<int> p;
        // same sign
        while (!apos.empty() && !bpos.empty()) {
            p.push_back(apos.back() * bpos.back());
            apos.pop_back();
            bpos.pop_back();
        }
        while (!aneg.empty() && !bneg.empty()) {
            p.push_back(aneg.back() * bneg.back());
            aneg.pop_back();
            bneg.pop_back();
        }
        sort(p.begin(), p.end());
        int ck = K;
        while (ck > 0 && !p.empty()) {
            res += p.back();
            p.pop_back();
            ck--;
        }
        // printf("AS= +%d -%d BS= +%d -%d\n", (int)apos.size(), (int)aneg.size(), (int)bpos.size(),(int)bneg.size()); fflush(stdout);
        // printf("CRES=%lld\n", res);
        // opposite sign | WLOG SZ(apos)>0 && SZ(bneg)>0
        if (!bpos.empty() && !aneg.empty()) {
            swap(bpos, apos);
            swap(aneg, bneg);
        }
        assert(apos.size() == bneg.size());
        assert(apos.size() >= ck);
        for (auto i = 0; i < ck; i++)
            res -= apos[i] * bneg[ck-i-1];

        return res;
    };
    // printf("TRUE=%lld\n", run2());

    ll maxv = run();
    for (auto &x : A) x *= -1;
    ll minv = -run();
    cout << minv << ' ' << maxv << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    int tc = 1;
    while (t--) {
        cout << "Case #" << (tc++) << ": ";
        solve();
    }

    return 0;
}

