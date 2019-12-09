#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    vector<int> v;
    cin >> n;
    
    while (n--) {
        int x;
        cin >> x;
        v.push_back(x);
    }
    
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    
    for (int x : v)
        cout << x << ' ';
    cout << '\n';
    
    return 0;
}
