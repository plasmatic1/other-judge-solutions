#include <bits/stdc++.h>

using namespace std;

// Complete the abbreviation function below.
string abbreviation(string a, string b) {
    int n = a.length(), m = b.length(),
        dp[n + 1][m + 1];
    a = " " + a;
    b = " " + b;
    memset(dp, 0, sizeof dp);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i] == tolower(a[i]))
                dp[i][j] = max(dp[i][j], dp[i - 1][j]);
            if (toupper(a[i]) == b[j])
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
            
            // printf("i=%d j=%d x=%d\n", i, j, dp[i][j]);
        }
    }

    // cout << (dp[n][m] == m ? "YES" : "NO") << endl;
    return dp[n][m] == m ? "YES" : "NO";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string a;
        getline(cin, a);

        string b;
        getline(cin, b);

        string result = abbreviation(a, b);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
