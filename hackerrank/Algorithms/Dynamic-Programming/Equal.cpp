#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<string> split_string(string);

const int MAX = 10001, MV = 1021;
int dp[MV][MV], vals[3] = {1, 2, 5};

void init() {
    memset(dp, 0x3f, sizeof dp);
    for (int i = 1000; i >= 0; i--) {
        dp[i][i + 10] = 0;
        for (int j = i; j >= -10; j--)
            for (int k : vals)
                dp[i][j + 10] = min(dp[i][j + 10], dp[i][j + k + 10] + 1);
    }
}

// Complete the equal function below.
int equal(vector<int> arr) {
    int n = arr.size(), minv = *min_element(arr.begin(), arr.end());
    ll best = 0x3f3f3f3f3f3f3f3f;
    for (int i = minv; i >= minv - 10; i--) {
        ll cTot = 0;
        for (int j = 0; j < n; j++)
            cTot += dp[arr[j]][i + 10];
        best = min(best, cTot);
    }

    printf("%lld\n", best);
    return best;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    init(); // init dp table

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string arr_temp_temp;
        getline(cin, arr_temp_temp);

        vector<string> arr_temp = split_string(arr_temp_temp);

        vector<int> arr(n);

        for (int i = 0; i < n; i++) {
            int arr_item = stoi(arr_temp[i]);

            arr[i] = arr_item;
        }

        int result = equal(arr);

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
