#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll digsum(ll x) {
    int ret = 0;
    while (x > 0) {
        ret += x % 10;
        x /= 10;
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int Q; 
    cin >> Q;

    while (Q--) {
        ll a, b;
        cin >> a >> b;
        if (a > b) swap(a, b);

        ll bb = b / 10, pow = 10, best = digsum(b);
        while (bb > 0) {
            ll num = stoll(to_string(bb - 1) + to_string(pow - 1));
            // cout << "bb: " << bb << ", pow: " << pow << ", num: " << num << '\n';

            if (num >= a) {
                best = max(best, digsum(num));
            }

            bb /= 10;
            pow *= 10;
        }

        cout << best << '\n';
    }
}