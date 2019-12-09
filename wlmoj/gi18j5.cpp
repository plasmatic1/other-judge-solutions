#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int n;
    cin >> n;
    
    long long a[n + 1];
    a[0] = 0LL;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += a[i - 1];
    }
    
    long long tot = 0, mx = LLONG_MIN;
    int mxId = -1;
    for (int i = 1; i <= n; i++) {
        tot += (a[i] - a[i - 1]) * a[i - 1];
        if (tot > mx) {
            mx = tot;
            mxId = i;
        }
    }
    
    cout << mxId << '\n';
    
    return 0;
}
