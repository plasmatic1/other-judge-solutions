#include <bits/stdc++.h>
using namespace std;
class ThreeNeighbors {
    public:
    vector<string> construct(int N) {
        vector<string> res(50);
        for (int i = 0; i < 50; i++)
            res[i].assign(50, '.');
        for (int i = 1; i < 46; i += 3) {
            res[i][0] = 'X';
            res[i][1] = 'X';
            for (int j = 1; j < 50 - 1; j++) {
                if (N >= 2) {
                    N -= 2;
                    res[i][j + 1] = 'X';
                }
            }
            if (N < 2)
                break;
        }
        if (N == 1) {
            for (int i = 0; i < 3; i++)
                res[49][i] = 'X';
        }
        return res;
    }
};
