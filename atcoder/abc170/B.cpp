// b-crane-and-turtle.yml
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
template <typename V> using uset = unordered_set<V>;
template <typename K, typename V> using umap = unordered_map<K, V>;
template <typename C> int sz(C &v) { return v.size(); }

int X, Y;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> X >> Y;

    for (int i = 0; i <= 100; i++) {
        for (int j = 0; j <= 100; j++) {
            if (i + j == X && 2 * i + 4 * j == Y) {
                cout << "Yes\n";
                return 0;
            }
        }
    }

    cout << "No\n";

    return 0;
}

