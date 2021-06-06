// ./high-fiver.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N; cin >> N;
    if (N % 2 == 0 && N % 3 == 0 && N % 10 != 2) cout << "not a memer\n";
    else cout << "memer\n";

    return 0;
}

