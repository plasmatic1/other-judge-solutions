// ./tootsie-rolls.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N; cin >> N;
    if (N < 3) cout << "Rocket!\n";
    else if (N > 7) cout << "Tootsie Roll!";
    else cout << "NO\n";

    return 0;
}

