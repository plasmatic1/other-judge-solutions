#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

string s;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> s;

    if (isupper(s[0]))
        cout << "A\n";
    else
        cout << "a\n";

    return 0;
}
