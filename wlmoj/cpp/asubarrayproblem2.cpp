#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int n, k;
    cin >> n >> k;
    
    long long a[n + 1];
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    a[0] = 0;
    for (int i = 1; i <= n; i++)
        a[i] += a[i - 1];
    
    // get 1
    long long msum = LLONG_MIN;
    for (int i = k - 1; i <= n; i++)
        msum = max(msum, a[i] - a[i - (k - 1)]);
    
    // ct
    int ct = 0;
    for (int i = k; i <= n; i++)
        ct += a[i] - a[i - k] > msum;
    cout << ct << '\n';

    return 0;
}