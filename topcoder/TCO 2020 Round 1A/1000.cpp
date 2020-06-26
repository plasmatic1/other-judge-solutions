#include <bits/stdc++.h>
using namespace std;
template <typename T> using V = vector<T>;
class BlindBoxSets {
    public:
    int sets, N;
    V<V<V<V<double>>>> dp;
    V<V<V<V<bool>>>> done;
    double solve(int i, int j, int k, int l) {
        if (i == 0 && j == 0 && k == 0 && l == 0) return 0;
        double &res = dp[i][j][k][l];
        if (done[i][j][k][l]) return res;

        int zeroCnt = N - i - j - k - l;
        double DN = N;
        if (i > 0)
            res += solve(i - 1, j, k, l) * ((i + 0) / DN);
        if (sets > 1 && j > 0)
            res += solve(i + 1, j - 1, k, l) * ((j + 0) / DN);
        if (sets > 2 && k > 0)
            res += solve(i, j + 1, k - 1, l) * ((k + 0) / DN);
        if (sets > 3 && l > 0)
            res += solve(i, j, k + 1, l - 1) * ((l + 0) / DN);
        res += 1.;
        res /= (1 - zeroCnt / DN);
        
        done[i][j][k][l] = true;
        return res;
    }
    double expectedPurchases(int sets0, int N0) {
        sets = sets0;
        N = N0;
        dp.resize(N + 1, V<V<V<double>>>(N + 1, V<V<double>>(N + 1, V<double>(N + 1))));
        done.resize(N + 1, V<V<V<bool>>>(N + 1, V<V<bool>>(N + 1, V<bool>(N + 1))));

        if (sets == 1)
            return solve(N, 0, 0, 0);
        else if (sets == 2)
            return solve(0, N, 0, 0);
        else if (sets == 3)
            return solve(0, 0, N, 0);
        else
            return solve(0, 0, 0, N);
    }
};