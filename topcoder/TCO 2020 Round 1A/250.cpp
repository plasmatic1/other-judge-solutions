#include <bits/stdc++.h>
using namespace std;
class AveragePrice {
    public:
    double nonDuplicatedAverage(vector<int> pr) {
        set<int> has;
        int cnt = 0;
        double res = 0;
        for (auto x : pr) {
            if (!has.count(x)) {
                has.insert(x);
                res += x;
                cnt++;
            }
        }
        return res / double(cnt);
    }
};