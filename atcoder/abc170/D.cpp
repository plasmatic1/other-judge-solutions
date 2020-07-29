// d-not-divisible.yml
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
template <typename V> using uset = unordered_set<V>;
template <typename K, typename V> using umap = unordered_map<K, V>;
template <typename C> int sz(C &v) { return v.size(); }

const int MN = 2e5 + 1, MV = 1e6 + 1;
int N,
    val[MN], cnt[MV];
bool bad[MV], seen[MV];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> val[i];
        cnt[val[i]]++;
    }

    for (int i = 0; i < N; i++) {
        if (cnt[val[i]] > 1) {
            bad[val[i]] = true;
        }
        if (seen[val[i]]) continue;
        seen[val[i]] = true;
        for (int j = val[i] + val[i]; j < MV; j += val[i]) {
            bad[j] = true;
        }
    }
    int ans = 0;
    for (int i = 0; i < N; i++)
        ans += !bad[val[i]];
    cout << ans << '\n';

    return 0;
}

