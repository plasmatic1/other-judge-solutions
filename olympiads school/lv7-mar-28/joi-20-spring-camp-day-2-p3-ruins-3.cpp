// ./joi-20-spring-camp-day-2-p3-ruins-3.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 13;
int N,
    H[MN], A[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (auto i = 0; i < N; i++) cin >> A[i];
    for (auto i = 0; i < 2*N; i++) H[i] = (i/2)+1;
    do {

    } while (next_permutation(H, H+2*N));

    return 0;
}

