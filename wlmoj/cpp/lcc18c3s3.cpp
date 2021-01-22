#include <bits/stdc++.h>

using namespace std;

long long n;
const int INF = 0x3f3f3f3f;

int rec(long long x, int csteps) {
    if (x == 1) return csteps;
    if (csteps > 24) return INF;
    
    long long dsum=0, xx=x;
    while (xx>0) {
        dsum += xx%10;
        xx /= 10;
    }
    
    return min(rec(x/dsum,csteps+1), rec(x-1, csteps+1));
}

int main() {
    
    cin >> n;
    cout << rec(n,0) << '\n';
    
    return 0;
}