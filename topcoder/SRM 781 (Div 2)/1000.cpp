#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define db(x) cout << (#x) << ": " << (x) << ", "
#define dblb(s) cout << "[" << (s) << "] "
#define dba(alias, x) cout << (alias) << ": " << (x) << ", "
template<typename F> inline string __generic_tostring(F f) { stringstream ss; ss << f; return ss.str(); }
template<typename F> inline string __join_comma(F f) {return __generic_tostring(f);}
template<typename F, typename... R> string __join_comma(F f, R... r) { return __generic_tostring(f) + ", " + __join_comma(r...); }
#define dbp(alias, ...) cout << (alias) << ": (" << __join_comma(__VA_ARGS__) << "), "
#define dbbin(x, n) cout << (#x) << ": " << bitset<n>(x) << ", "
#define dbarr(x, n) cout << (#x) << ": " << arrayStr((x), (n)) << ", "
#define dbln cout << endl;

const ll MOD = 1e9 + 7;
ll madd(ll a, ll b) { return (a + b) % MOD; }
ll msub(ll a, ll b) { return (a - b + MOD) % MOD; }
ll mmul(ll a, ll b) { return (a * b) % MOD; }
ll fpow(ll x, ll y) {
    if (!y) return 1LL;
    return mmul(fpow(mmul(x, x), y >> 1), (y & 1) ? x : 1LL);
}
ll mdiv(ll x, ll y) { return mmul(x, fpow(y, MOD - 2)); }

class PolygonalRegions {
    public:
    int expectedRegions(int N) {
        ll res = 1;
        vector<ll> prob(N + 1);
        for (int i = 1; i <= N; i++)
            prob[i] = mdiv(i, N);
        for (int i = 1; i <= N; i++)
            for (int j = i + 2; j <= N; j++)
                if (!(i == 1 && j == N))
                res = madd(res, mmul(prob[i], prob[j]));
        for (int i = 1; i <= N; i++)
            for (int j = i + 2; j <= N; j++)
                if (!(i == 1 && j == N))
                    for (int k = 1; k <= N; k++)
                        for (int l = k + 2; l <= N; l++)
                            if (!(k == 1 && l == N))
                                if (k < j && k > i && l > j)
                                    res = madd(res, mmul(mmul(mmul(prob[i], prob[j]), prob[k]), prob[l])); //, db(i), db(j), db(k), db(l), dbln;

        return res;
    }
};
