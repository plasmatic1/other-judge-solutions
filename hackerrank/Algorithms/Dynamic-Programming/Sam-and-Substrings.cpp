#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007

// Complete the substrings function below.
int substrings(string s) {
    int n = s.length();
    long long dp[n + 1];
    memset(dp, 0, sizeof dp);

    for (int i = 1; i <= n; i++) {
        int add = s[i - 1] - '0';
        dp[i] = (dp[i - 1] * 10) + add * i;
        dp[i] %= MOD;
    }

    long long tot = 0;
    for (int i = 1; i <= n; i++)
        tot += dp[i];
    tot %= MOD;

    cout << tot << endl;
    return tot;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n;
    getline(cin, n);

    int result = substrings(n);

    fout << result << "\n";

    fout.close();

    return 0;
}
