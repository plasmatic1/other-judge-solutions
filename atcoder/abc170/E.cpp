// e-smart-infants.yml
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
template <typename V> using uset = unordered_set<V>;
template <typename K, typename V> using umap = unordered_map<K, V>;
template <typename C> int sz(C &v) { return (int)v.size(); }

const int MN = 2e5 + 1;
int N, Q,
    rating[MN], group[MN];

multiset<int> ratings;
multiset<int, greater<int>> groups[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    for (int i = 0; i < N; i++) {
        cin >> rating[i] >> group[i];
        groups[group[i]].insert(rating[i]);
    }
    for (int i = 0; i < MN; i++)
        if (!groups[i].empty())
            ratings.insert(*groups[i].begin());

    while (Q--) {
        int c, d;
        cin >> c >> d;
        c--;

        int og = group[c];
        ratings.erase(ratings.find(*groups[og].begin()));
        groups[og].erase(groups[og].find(rating[c]));
        if (!groups[og].empty())
            ratings.insert(*groups[og].begin());

        if (!groups[d].empty())
            ratings.erase(ratings.find(*groups[d].begin()));
        groups[d].insert(rating[c]);
        ratings.insert(*groups[d].begin());

        group[c] = d;

        cout << *ratings.begin() << '\n';
    }

    return 0;
}

