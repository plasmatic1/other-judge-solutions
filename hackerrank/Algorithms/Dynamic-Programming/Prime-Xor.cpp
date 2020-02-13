#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

using ll = long long;
const ll MOD = 1e9 + 7;
ll fpow(ll x, ll y) {
    if (!y) return 1LL;
    return (fpow((x * x) % MOD, y >> 1) * (y & 1 ? x : 1)) % MOD;
}

void madd(ll &a, ll b) { a = (a + b) % MOD; }

// Complete the primeXor function below.
int primeXor(vector<int> a) {   
    vector<vector<ll>> dp(1002, vector<ll>(8192));
    vector<ll> count(1001), countOdd(1001), countEven(1001);
    for (auto x : a)
        count[x - 3500]++;
    for (int i = 0; i < 1001; i++) {
        int x = count[i];
        countOdd[i] = (x + 1) / 2;
        countEven[i] = x / 2 + 1;
    }

    // do dp
    dp[0][0] = 1LL;    
    for (int i = 1; i <= 1001; i++) {
        int val = i + 3499;
        for (int j = 0; j < 8192; j++) {
            madd(dp[i][j], (dp[i - 1][j] * countEven[i - 1]) % MOD);
            madd(dp[i][j], (dp[i - 1][j ^ val] * countOdd[i - 1]) % MOD);
        }
    }

    // sum answer
    ll tot = 0;
    for (int i = 2; i < 8192; i++) {
        bool isp = true;
        for (int j = 2; j * j <= i; j++)
            if (i % j == 0)
                isp = false;
        
        if (isp)
            madd(tot, dp[1001][i]);
    }
    cout << tot << endl;

    return tot;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string a_temp_temp;
        getline(cin, a_temp_temp);

        vector<string> a_temp = split_string(a_temp_temp);

        vector<int> a(n);

        for (int i = 0; i < n; i++) {
            int a_item = stoi(a_temp[i]);

            a[i] = a_item;
        }

        int result = primeXor(a);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
