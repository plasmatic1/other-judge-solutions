// ./cheating-detection.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
using ld = double;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

ld sig(ld x) {
    return 1 / (1 + exp(-x));
}

// avg = approx. of average value of running probability for all possible difficulties/skill levels
// MAGIC is calculated from ternary searching in p5_test_magic.py
const ld MAGIC = 1.62614510620592, DIFF_TH = 2.; // DIFF_TH = difficulty threshold of questions to check
ld avg(ld x) { return (sig(x-MAGIC) + sig(x+MAGIC)) / 2.; }

const int N = 100, Q = 10000;
const ld EPS = 1e-5;
bitset<Q> ok[N];
ld diff[Q];

void solve() {
    for (auto i = 0; i < N; i++) {
        string _ok; cin >> _ok;
        reverse(_ok.begin(), _ok.end()); // make MSB (pos Q-1) at end for debugging purposes, though in practice this is irrelavent
        ok[i] = bitset<Q>(_ok);
    }

    // approximate difficulties
    for (auto i = 0; i < Q; i++) {
        ld p = 0;
        for (auto j = 0; j < N; j++) p += ok[j][i];
        p /= N;

        // EV of skill is 0
        ld l = -3, r = 3;
        while (l + EPS < r) {
            ld mid = (l + r) / 2;
            if (avg(-mid) > p) l = mid;
            else r = mid;
        }
        diff[i] = l;
    }

    // check for the cheater
    int wi = -1;
    ld worst = 0; // take cheater with greatest error
    for (auto i = 0; i < N; i++) {
        int right = ok[i].count();

        // binary search for skill level assuming they are legit
        ld l = -3, r = 3;
        while (l + EPS < r) {
            ld mid = (l + r) / 2, solve = 0;
            for (auto j = 0; j < Q; j++)
                solve += sig(mid - diff[j]);

            if (solve > right) r = mid; // too good
            else l = mid;
        }

        // calculate error (actual solved vs. expected solved for their skill level)
        ld alt = 0;
        for (auto j = 0; j < Q; j++) {
            if (abs(diff[j]) >= DIFF_TH) {
                alt += ok[i][j];
                alt -= sig(l - diff[j]);
            }
        }
        alt = abs(alt);

        // update answer
        if (alt > worst) {
            wi = i;
            worst = alt;
        }
    }
    cout << (wi+1) << '\n';

    // clear
    for (auto i = 0; i < N; i++) { ok[i].reset(); }
    fill(diff, diff+Q, 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifdef LOCAL
    cerr << "begin\n"; cerr.flush();
#endif
    int T, P;
    cin >> T >> P;
    for (int caseno = 1; caseno <= T; caseno++) {
        // Input
       
        cout << "Case #" << caseno << ": ";
        solve();
#ifdef LOCAL
        cerr << "Done Case #" << caseno << "\n"; cerr.flush();
#endif

        // Reset
    }
}
