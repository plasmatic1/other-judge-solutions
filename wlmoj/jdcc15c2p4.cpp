#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll digsum(string x) {
    int ret = 0;
    for (char c : x) {
        ret += c - '0';
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int Q; 
    cin >> Q;

    while (Q--) {
        string s;
        cin >> s;
        int n = s.length(), h = n / 2;

        int sa = digsum(s.substr(0, h));
        int sb = digsum(s.substr(h, h));

        // Decrease
        if (sb >= sa) {
            bool carry = 0;
            for (int i = h - 1; i >= 0; i--) {
                int dig = s[h + i] - '0';
                if (dig + carry == 10) {
                    sb -= dig;
                }
                else {
                    if (sb >= sa) {
                        sb -= dig;
                        carry = true;
                        s[i + h] = '0';
                    }
                    else {
                        if (carry) {
                            s[i + h]++;
                            carry = false;
                        }
                    }
                }
            }

            if (carry)
                s[h - 1]++;
        }

        for (int i = h - 1; i >= 0; i--) {
            int dig = s[h + i] - '0';
            int req = min(9 - dig, sa - sb);
            s[i] = (char)((dig + req) + '0');
            sb += req;
        }

        cout << sa << sb << '\n';
    }
}
