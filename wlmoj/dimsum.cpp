#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    int tot = 0;
    while (n--) {
        int x;
        cin >> x;
        tot += x;
    }
    
    cout << tot << '\n';
    
    return 0;
}
