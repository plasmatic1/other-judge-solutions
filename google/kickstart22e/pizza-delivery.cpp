// ./pizza-delivery.yml
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

const int DIRS[4][2] = {{-1, 0}, {0, 1}, {0, -1}, {1, 0}};
const int MN = 10, MM = 20+1, MP = 10, MPSUB = 1<<MP;
int N, M, P;
ll dp[MM][MN][MN][MPSUB];
char op[4];
int opv[4];
pii pizza[MN][MN];

bool inbound(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < N;
}

ll doOp(int dirIdx, ll v) {
    char curOp = op[dirIdx];
    int curOpv = opv[dirIdx];

    ll ret = 0;
    switch (curOp) {
        case '+':
            ret = v+curOpv;
            break;
        case '-': 
            ret = v-curOpv;
            break;
        case '/': 
            if (v >= 0)
                ret = v / curOpv;
            else { // ceildiv since div is towards 0
                v = -v;
                ret = (v + curOpv - 1) / curOpv;
                ret = -ret;
            }
            break;
        case '*': 
            ret = v*curOpv;
            break;
        default:
            assert(0);
            break;
    }

    return ret;
}

void solve() {
    cin >> N >> P >> M;
    int sx, sy; cin >> sx >> sy;

    for (auto i = 0; i < 4; i++) {
        cin >> op[i] >> opv[i];
    }

    // get pizzas
    memset(pizza, -1, sizeof pizza);
    for (auto i = 0; i < P; i++) {
        int x, y, p; cin >> x >> y >> p;
        pizza[x-1][y-1] = {i, p};
    }

    // reset+init dp
    int msub = 1<<P;
    for (auto i = 0; i <= M; i++)
        for (auto j = 0; j < N; j++)
            for (auto k = 0; k < N; k++)
                for (auto l = 0; l < msub; l++)
                    dp[i][j][k][l] = -LLINF;

    dp[0][sx-1][sy-1][0] = 0;

    // do dp
    ll ans = -LLINF;
    for (auto i = 0; i <= M; i++) {
        // transit
        if (i < M) {
            for (auto j = 0; j < N; j++) {
                for (auto k = 0; k < N; k++) {
                    for (auto m = 0; m < msub; m++) {
                        ll curDp = dp[i][j][k][m];
                        if (curDp == -LLINF) continue;

                        // pick directions
                        for (auto d = 0; d < 4; d++) {
                            int nx = j+DIRS[d][0], ny = k+DIRS[d][1];
                            if (inbound(nx, ny)) {
                                ll newVal = doOp(d, curDp);
                                int newMsk = m;

                                // assume no take Pizza
                                maxa(dp[i+1][nx][ny][newMsk], newVal);
                                // assume take pizza (can try)
                                auto [pizzaIdx, pizzaVal] = pizza[nx][ny];
                                if (pizzaIdx != -1 && !((newMsk >> pizzaIdx) & 1)) {
                                    newMsk |= 1 << pizzaIdx;
                                    newVal += pizzaVal;
                                    maxa(dp[i+1][nx][ny][newMsk], newVal);
                                }
                            }
                        }
                    }
                }
            }
        }

        // update ans
        for (auto j = 0; j < N; j++)
            for (auto k = 0; k < N; k++)
                maxa(ans, dp[i][j][k][msub-1]);
    }

    if (ans == -LLINF)
        cout << ("IMPOSSIBLE") << '\n';
    else
        cout << (ans) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for (int caseno = 1; caseno <= T; caseno++) {
        // Input
       
        cout << "Case #" << caseno << ": ";
        solve();

        // Reset
    }
}

