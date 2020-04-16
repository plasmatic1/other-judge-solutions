#include <bits/stdc++.h>
using namespace std;
const int MN = 201;
class NicePartition {
    int N;
    public:
    int minCost(vector<int> _h) {
        N = _h.size();
        sort(_h.begin(), _h.end());
        int t = 0;
        for (int i = 0; i < int(_h.size()); i += 2) 
            t += abs(_h[i] - _h[N - i - 1]);
        return t;
    }
};