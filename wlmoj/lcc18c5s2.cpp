#include <bits/stdc++.h>

using namespace std;

/*
Basic idea: (first mul by 100, then) take all #s modulo 5.  Sum up the non-modulo 5s

Pair up 4s with 3s -> 7s -> +2 savings
Pair up 3s with 3s -> 6s -> +1 savings

Nothing else matters
i.e. 3 with 1, 1 -> +0 savings vs 3 -> -2 savings, 1, 1 -> +2 savings -> 0 savings
i.e. 3 with 2 -> +0 savings vs 3 -> -2 savings, 2 -> +2 savings -> 0 savings
i.e. 4 with 1 -> +0 savings vs 4, 1 -> -1, +2 savings -> 0 savings
i.e. 4 with 2 -> +1 savings vs 4, 2 -> -1, +2, savings -> +1 savings

1 and 2 are trivial, maximize those
*/

string pad0(int x) {
	if (x < 10) return "0" + to_string(x);
	return to_string(x);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int n;
    cin >> n;
    
    int c[6];
    fill(c, c + 6, 0);
    
    long long ttot = 0;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        long long x = stoi(s.substr(0, s.length() - 3)) * 100LL + stoi(s.substr(s.length() - 2, 2));
        ttot += x - (x % 5);
        c[x % 5]++;
    }
    
    // pair 4 with 3
    while (c[4] > 0 && c[3] > 0) {
        c[4]--;
        c[3]--;
        ttot += 5;
    }

    // pair 4 with 4 with 4
    while (c[4] > 2) {
        c[4] -= 3;
        ttot += 10;
    }
    
    // pair 3 with 3
    while (c[3] > 1) {
        c[3] -= 2;
        ttot += 5;
    }
    
    // count extra 4 and 3
    ttot += c[3] * 5;
    ttot += c[4] * 5;
    
    cout << (ttot / 100) << '.' << pad0((ttot % 100)) << '\n';
    
    return 0;
}
