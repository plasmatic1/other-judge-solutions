// c-forbidden-list.yml
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

    int X, N;
    cin >> X >> N;

    vector<bool> good(102, true);
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        good[x] = false;
    }

    int best = 1e9, besti = 1e9;
    for (int i = 0; i < 102; i++) {
        if (good[i]) {
            int d = abs(i - X);
            if (d < best)
                best = d, besti = i;
            else if (d == best)
                besti = min(besti, i);
        }
    }

    cout << besti << '\n';

    return 0;
}

