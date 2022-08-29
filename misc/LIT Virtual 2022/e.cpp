// e.yml
#include <bits/stdc++.h>
#define DEBUG 0
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
#if __cplusplus == 201703L // CPP17 only things
template <typename T> using opt_ref = optional<reference_wrapper<T>>; // for some templates
#endif
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

const int MN = 201;
int N, M;
string s, t;
bool dpAux[MN][MN],
     matchLeft[MN][MN], matchRight[MN][MN];
int dp[MN][MN][MN];

void solve() {
    cin >> s >> t;
    N = SZ(s);
    M = SZ(t);

    if (DEBUG) { cout<<"[in]: "; cout<<"s="<<(s)<<", "; cout<<"t="<<(t)<<", "; cout << endl; } //__RAW_DEBUG_LINE__:db l:in,s,t

    // init
    memset(dpAux, 0, sizeof dpAux);
    for (auto i = 0; i <= N; i++)
        for (auto j = 0; j <= N; j++)
            for (auto k = 0; k <= N; k++)
                dp[i][j][k] = -INF;

    // fill out aux dp
    for (auto len = 1; len <= M; len++) {
        int end = M-len;
        for (auto l = 0; l <= end; l++) {
            int r = l+len-1;

            if (l == r)
                dpAux[l][r] = s[0] == t[l];
            else {
                if (s[len-1] == t[l])
                    dpAux[l][r] |= dpAux[l+1][r];
                if (s[len-1] == t[r])
                    dpAux[l][r] |= dpAux[l][r-1];
            }
        }
    }

    // init states
    dp[0][0][0] = 0;
    for (auto i = 0; i <= M-1; i++) {
        if (dpAux[0][i]) {
            dp[i+1][0][i+1] = 0;
        }
        if (dpAux[M-i-1][M-1]) {
            dp[i+1][i+1][0] = 0;
        }
    }
    if (dpAux[0][M-1])
        dp[M][M][M] = 1;

    // precompute match tables on left and right
    memset(matchLeft, 0, sizeof matchLeft);
    memset(matchRight, 0, sizeof matchRight);
    for (auto j = 0; j <= M; j++) {
        for (auto l = 0; l < j; l++) {
            matchLeft[j][l] = t.substr(M-j, l) == t.substr(M-l, l);
        }
    }
    for (auto k = 0; k <= M; k++) {
        for (auto l = 0; l < k; l++) {
            matchRight[k][l] = t.substr(k-l, l) == t.substr(0, l);
        }
    }

    // run dp
    for (auto i = 0; i < N; i++) {
        for (auto j = M; j >= 0; j--) {
            for (auto k = M; k >= 0; k--) {
                int curDp = dp[i][j][k];
                { // next char on left
                    int c = (M - j - 1) % M;
                    if (c < 0) c += M;

                    if (i==6&&j==3&&k==0) {
                        if (DEBUG) { cout<<"i="<<(i)<<", "; cout<<"j="<<(j)<<", "; cout<<"k="<<(k)<<", "; cout<<"c="<<(c)<<", "; cout<<"s[i]="<<(s[i])<<", "; cout<<"t[c]="<<(t[c])<<", "; cout << endl; } //__RAW_DEBUG_LINE__:db i,j,k,c,s[i],t[c]
                    }

                    // add 1
                    if (j < M && s[i] == t[c])
                        maxa(dp[i+1][j+1][k], curDp + (j+1 == M));
                    
                    // complete string
                    // if (j >= M-1 && s[i] == t[0]) {
                    //     if (t.substr(1) == tCopy.substr((c + 1) % M, M-1))
                    //         maxa(dp[i+1][M][k], curDp+1);
                    // }
                }

                { // next char on right
                    int c = k % M;

                    // add 1
                    if (k < M && s[i] == t[c])
                        maxa(dp[i+1][j][k+1], curDp + (k+1 == M));

                    // complete string
                    // int prev = c - 1;
                    // if (prev < 0) prev += M;

                    // if (k >= M-1 && s[i] == t.back()) {
                    //     if (t.substr(0, M-1) == tCopy.substr((k - (M - 1)) % M, M-1))
                    //         maxa(dp[i+1][j][M], curDp+1);
                    // }
                }

                // cdefg
                //     tot=abcdefg
                //     j=5
                //     l=3

                // Left Side
                // abcde
                // cde
                // 
                // Right side
                // abcde
                //   abc
                    
                // reduce length
                // left side
                for (auto l = 0; l < j; l++) {
                    if (matchLeft[j][l])
                        maxa(dp[i][l][k], curDp);
                }
                // right side
                for (auto l = 0; l < k; l++) {
                    if (matchRight[k][l])
                        maxa(dp[i][j][l], curDp);
                }

                maxa(dp[i+1][0][k], curDp); // add on left  arbitrarily
                maxa(dp[i+1][j][0], curDp); // add on right arbitrarily
            }
        }
    }

    // get ans
    int ans = -INF;
    for (auto i = 0; i <= N; i++)
        for (auto j = 0; j <= N; j++)
            for (auto k = 0; k <= N; k++) {
                maxa(ans, dp[i][j][k]);
                if (DEBUG) { cout<<"i="<<(i)<<", "; cout<<"j="<<(j)<<", "; cout<<"k="<<(k)<<", "; cout<<"dpv="<<(dp[i][j][k])<< ", "; cout << endl; } //__RAW_DEBUG_LINE__:db i,j,k,a:dpv:dp[i][j][k]
            }

    if (DEBUG) { cout<<"[-------------------------------------------------]: "; cout << endl; } //__RAW_DEBUG_LINE__:db l:-------------------------------------------------
    for (auto [i,j,k] : vector<tuple<int, int, int>>{
            {6,3,0},
            {7,4,0},
            }) {
        if (DEBUG) { cout<<"[+++]: "; cout<<"i="<<(i)<<", "; cout<<"j="<<(j)<<", "; cout<<"k="<<(k)<<", "; cout<<"dp[i][j][k]="<<(dp[i][j][k])<<", "; cout << endl; } //__RAW_DEBUG_LINE__:db l:+++,i,j,k,dp[i][j][k]
    }

    cout << (ans) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        // Input
        
        if (DEBUG) { cout<<"[startCase]: "; cout << endl; } //__RAW_DEBUG_LINE__:db l:startCase
        solve();

        // Reset
    }
}
