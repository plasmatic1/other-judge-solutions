// ./build-a-pair.yml
#include "bits/stdc++.h"
using namespace std;

// Defines
#define fs first
#define sn second
#define pb push_back
#define eb emplace_back
#define mpr make_pair
#define mtp make_tuple
#define all(x) (x).begin(), (x).end()
// Basic type definitions
using ll = long long; using ull = unsigned long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<long long, long long>;
#ifdef __GNUG__
// PBDS order statistic tree
#include <ext/pb_ds/assoc_container.hpp> // Common file 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds; 
template <typename T, class comp = less<T>> using os_tree = tree<T, null_type, comp, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename V, class comp = less<K>> using treemap = tree<K, V, comp, rb_tree_tag, tree_order_statistics_node_update>;
// HashSet
#include <ext/pb_ds/assoc_container.hpp>
template <typename T, class Hash> using hashset = gp_hash_table<T, null_type, Hash>;
template <typename K, typename V, class Hash> using hashmap = gp_hash_table<K, V, Hash>;
const ll RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { ll operator()(ll x) const { return x ^ RANDOM; } };
#endif
// More utilities
int SZ(string &v) { return v.length(); }
template <typename C> int SZ(C &v) { return v.size(); }
template <typename C> void UNIQUE(vector<C> &v) { sort(v.begin(), v.end()); v.resize(unique(v.begin(), v.end()) - v.begin()); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 36, MD = 10, MP = 19;
int N,
    D[MN], fre[MD];
ll p10[MP];

bool skip[MN];
template <typename It> ll minmax(It d, int n) {
    ll mn = 0, mx = 0, p = 1;
    int tk = (n-1)/2; // ceil(n/2)
    for (auto i = 0; i < n; i++) {
        if (!skip[i]) {
            tk--;
            if (tk >= 0)
                mn = (mn*10) + d[i];
            else {
                mx += p*d[i];
                p *= 10;
            }
        }
    }

    return mn - mx;
}

void solve() {
    string s; cin >> s;
    N = SZ(s);
    for (auto i = 0; i < N; i++) {
        D[i] = s[i]-'0';
        fre[D[i]]++;
    }
    sort(D, D+N);

    ll ans = LLINF;
    if (N % 2) {
        int h = (N+1)/2;
        for (auto i = 0; i < N; i++) { // larger
            for (auto j = 0; j < N; j++) { // smaller
                if (i != j && D[i] && D[j]) {
                    skip[i] = skip[j] = true;
                    ans = min(ans, D[i]*p10[h-1] - D[j]*p10[h-2] + minmax(D, N));
                    skip[i] = skip[j] = false;
                }
            }
        }
    }
    else {
        bool only0 = fre[0] >= 2;
        for (auto i = 1; i < MD; i++) only0 &= fre[i] < 2;

        if (only0) {
            int h = N/2;
            for (auto i = 0; i < N; i++) { // larger
                for (auto j = 0; j < N; j++) { // smaller
                    if (i != j && D[i] && D[j]) {
                        skip[i] = skip[j] = true;
                        ans = min(ans, abs(D[i]*p10[h-1] - D[j]*p10[h-1] + minmax(D, N)));
                        skip[i] = skip[j] = false;
                    }
                }
            }
            goto done;
        }

        int iremCnt = 0;
        vector<int> d;
        for (auto i = 0; i < MD; i++) {
            iremCnt += fre[i] / 2;
            if (fre[i] % 2)
                d.pb(i);
        }

        for (auto i = 0; i <= MD; i++) {
            if (i == MD || fre[i] >= 2) {
                vector<int> rem = d;
                if (i != MD) {
                    rem.pb(i);
                    rem.pb(i);
                }
                sort(all(rem));

                int cnt0 = 0;
                for (auto x : rem) cnt0 += x == 0;
                int rem0Cnt = fre[0]-cnt0, remCnt = N-SZ(rem);
                if (remCnt > 0 && rem0Cnt == remCnt) continue;

                bool remAny = rem.size() != N;
                int csz = SZ(rem);
                if (csz == 0) ans = 0;
                else {
                    int h = csz/2;
                    for (auto i = 0; i < csz; i++) { // larger
                        for (auto j = 0; j < csz; j++) { // smaller
                            if (i != j && (remAny || (rem[i] && rem[j]))) {
                                skip[i] = skip[j] = true;
                                ans = min(ans, abs(rem[i]*p10[h-1] - rem[j]*p10[h-1] + minmax(rem.begin(), csz)));
                                skip[i] = skip[j] = false;
                            }
                        }
                    }
                }
            }
        }
    }
done:

    cout << (ans) << '\n';

    fill(fre, fre+MD, 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    p10[0] = 1;
    for (auto i = 1; i < MP; i++)
        p10[i] = p10[i-1]*10;

    int T;
    cin >> T;
    for (int caseno = 1; caseno <= T; caseno++) {
        // Input
       
        cout << "Case #" << caseno << ": ";
        solve();

        // Reset
    }
}

