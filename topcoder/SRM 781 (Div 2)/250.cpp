#include <bits/stdc++.h>
using namespace std;
const int MN = 50 * 8 + 10;
class EasyPartition {
    bitset<MN> take;
    public:
    string getPartition(int N) {
        take.reset();

        int L = 2 * N - 1, R = L + 2;
        for (int i = 0; i < N; i++) {
            take[L] = true;
            take[R] = true;
            L--; R++;
        }

        string ans = take.to_string();
        ans = ans.substr(0, ans.length() - 1);
        reverse(ans.begin(), ans.end());
        ans = ans.substr(0, N * 8);
        return ans;
    }
};
