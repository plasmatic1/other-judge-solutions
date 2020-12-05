// C.yml
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
// PBDS order statistic tree
#include <ext/pb_ds/assoc_container.hpp> // Common file 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds; 
template <typename T, class comp = less<T>> using os_tree = tree<T, null_type, comp, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename V, class comp = less<K>> using treemap = tree<K, V, comp, rb_tree_tag, tree_order_statistics_node_update>;
// HashSet
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
const ll RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { ll operator()(ll x) const { return x ^ RANDOM; } };
template <typename T, class Hash> using hashset = gp_hash_table<T, null_type, Hash>;
template <typename K, typename V, class Hash> using hashmap = gp_hash_table<K, V, Hash>;
// More utilities
int SZ(string &v) { return v.length(); }
template <typename C> int SZ(C &v) { return v.size(); }
template <typename C> void UNIQUE(vector<C> &v) { sort(v.begin(), v.end()); v.resize(unique(v.begin(), v.end()) - v.begin()); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const ll MOD = 1e9 + 7;
ll madd(ll a, ll b, ll mod = MOD) { return (a + b) % mod; }
ll msub(ll a, ll b, ll mod = MOD) { return (a - b + mod) % mod; }
ll mmul(ll a, ll b, ll mod = MOD) { return (a * b) % mod; }
ll fpow(ll x, ll y, ll mod = MOD) {
    if (!y) return 1LL;
    return mmul(fpow(mmul(x, x, mod), y >> 1, mod), (y & 1) ? x : 1LL, mod);
}
ll mdiv(ll x, ll y, ll mod = MOD) { return mmul(x, fpow(y, mod - 2, mod), mod); }

void init_file_io() {
#ifndef LOCAL
    const string PROBLEM_ID = "prob";
    freopen((PROBLEM_ID + ".in").c_str(), "r", stdin);
    freopen((PROBLEM_ID + ".out").c_str(), "w", stdout);
#endif
}

template <typename T> void read_fhc_array(vector<T> &v, int k, int inc = 1, ll dval = -1) {
    for (auto i = 0; i < k; i++)
        cin >> v[i];
    ll a, b, c, d;
    cin >> a >> b >> c;
    if (dval == -1) cin >> d;
    else d = dval;
    for (auto i = k; i < (int)v.size(); i++)
        v[i] = (a * v[i - 2] + b * v[i - 1] + c) % d + inc;
}

using MS = multiset<ll>;
ll max(MS &s) { return *(--s.end()); }
ll min(MS &s) { return *s.begin(); }
void rem(MS &s, ll w) { s.erase(s.find(w)); }
// void rem(MS &s, ll w) { 
//     auto ptr = s.find(w);
//     if (ptr == s.end()) {
//         cout<<"[notfound]: "; cout << "s=["; for (auto __x:s)cout<<__x<<", "; cout<<"], "; cout<<"w="<<(w)<<", "; cout << endl; // db l:notfound,I:s,w
//         assert(0);
//     }
//     s.erase(ptr);
// }

struct LG {
    MS w;
    ll tot;

    void init(int sz) {
        tot = 0;
        for (auto i = 0; i < sz; i++) {
            w.insert(1);
            tot++;
        }
    }
    void upd(ll oldw, ll neww) {
        rem(w, oldw); w.insert(neww); tot += neww - oldw;
    }
    bool empty() {
        return w.empty();
    }
    ll mst() {
        return empty() ? 0 : (tot - max(w));
    }
};
struct Circle {
    int idx;
    LG side[2], tot;

    void upd(bool s2, ll oldw, ll neww) {
        tot.upd(oldw, neww);
        side[s2].upd(oldw, neww);
    }
    ll mst() {
        return tot.mst();
    }
    ll mst2() {
        return side[0].mst() + side[1].mst();
    }
};

void solve() {
    int N, M, Q, K;
    cin >> N >> M >> Q >> K;
    int edc = N * M + N;
    vector<ll> X(N), Y(N), I(Q), W(Q);
    read_fhc_array(X, K, 0, M);
    read_fhc_array(Y, K, 0, M);
    read_fhc_array(I, K, 0, edc);
    read_fhc_array(W, K, 0, 1000000000);

    // extra things
    vector<ll> edges(edc, 1);

    // small circles
    ll smallSum = 0;
    vector<Circle> cs(N);
    MS gain2;

    // big circle and globs
    LG bigw;

    // init
    bigw.init(N);
    for (auto i = 0; i < N; i++) {
        if (X[i] > Y[i]) swap(X[i], Y[i]);
        auto &c = cs[i];
        c.idx = i;
        c.side[0].init(Y[i] - X[i]);
        c.side[1].init(M - (Y[i] - X[i]));
        c.tot.init(M);

        gain2.insert(c.mst() - c.mst2());
        smallSum += c.mst();
    }

    // answer queries
    ll ans = 1;
    for (auto _ = 0; _ < Q; _++) {
        ll idx = I[_], w = W[_];
        // cout<<"[upd]: "; cout<<"idx="<<(idx)<<", "; cout<<"w="<<(w)<<", "; cout << endl; // db l:upd,idx,w

        // update
        if (idx >= N * M) { // big boi edge
            bigw.upd(edges[idx], w);
        } 
        else { // small boi edge
            int cidx = idx / M, eidx = idx % M;
            auto &c = cs[cidx];

            // cout<<"[small]: "; cout<<"cidx="<<(cidx)<<", "; cout<<"eidx="<<(eidx)<<", "; cout<<"X[cidx]="<<(X[cidx])<<", "; cout<<"Y[cidx]="<<(Y[cidx])<<", "; cout << endl; // db l:small,cidx,eidx,X[cidx],Y[cidx]
            // cout << "c.side[0].w=["; for (auto __x:c.side[0].w)cout<<__x<<", "; cout<<"], "; cout << "c.side[1].w=["; for (auto __x:c.side[1].w)cout<<__x<<", "; cout<<"], "; cout << "c.tot.w=["; for (auto __x:c.tot.w)cout<<__x<<", "; cout<<"], "; cout << endl; // db I:c.side[0].w,I:c.side[1].w,I:c.tot.w
            ll oldw = c.mst(), oldDiff = oldw - c.mst2();
            c.upd(!(X[cidx] <= eidx && eidx < Y[cidx]), edges[idx], w);

            smallSum += c.mst() - oldw;
            rem(gain2, oldDiff);
            gain2.insert(c.mst() - c.mst2());
        }
        edges[idx] = w;

        // get mst
        ll mst = smallSum + bigw.mst(), mstCircle = smallSum - max(gain2) + bigw.tot;
        // cout<<"_="<<(_)<<", "; cout<<"idx="<<(idx)<<", "; cout<<"w="<<(w)<<", "; cout<<"mst="<<(mst)<<", "; cout<<"mstCircle="<<(mstCircle)<<", "; cout << endl; // db _,idx,w,mst,mstCircle
        ll cans = min(mst, mstCircle);
        ans = mmul(ans, cans % MOD);
    }
    cout << (ans) << '\n';
    cout.flush();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_file_io();

    int T;
    cin >> T;
    for (int caseno = 1; caseno <= T; caseno++) {
        // Input
       
        cout << "Case #" << caseno << ": ";
        solve();

        // Reset
#ifndef LOCAL
        cerr << "Done case #" << caseno << endl;
#endif
    }

    return 0;
}

