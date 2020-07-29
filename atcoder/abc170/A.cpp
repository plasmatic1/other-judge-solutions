// a-five-variables.yml
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
template <typename V> using uset = unordered_set<V>;
template <typename K, typename V> using umap = unordered_map<K, V>;
template <typename C> int sz(C &v) { return v.size(); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (int i = 0; i < 5; i++) {
        int x;
        cin >> x;
        if (x == 0)
            cout << (i + 1) << '\n';
    }

    return 0;
}

