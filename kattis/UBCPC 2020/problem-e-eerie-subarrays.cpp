// ./problem-e-eerie-subarrays.yml
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

// const int MN = 1001, B = 2, D = 2000, CLEN = MN * 5;
const int MN = 2e5 + 1, B = 660, D = 400000, CLEN = MN * 4;
int N,
    P[MN], L[MN], R[MN], bno[MN];
ll ans = 0;

using Mt = unordered_map<int, int>;
struct block {
    int cnts[CLEN];
    vector<int> vs;
    int delta, l;

    inline int get(int idx) {
        return vs[idx - l];
    }
} bs[MN / B + 2];

// #define _C(x) do{if (!(0 <= (x) && (x) < CLEN)){cout <<"x="<<x<<endl;assert(0);}}while(0)
#define _C(x)

void fix(int idx) {
    auto &b = bs[idx];
    if (b.delta) {
        for (auto &x : b.vs) {
            b.cnts[x + D]--;
            _C(x + D);
            x += b.delta;
            b.cnts[x + D]++;
            _C(x + D);
        }

        b.delta = 0;
    }
}

int query(int l, int qv) {
    if (l > N) return 0;

    fix(bno[l]);
    int res = 0;
    for (; l <= N && l != L[bno[l]]; l++)
        res += bs[bno[l]].get(l) == qv;
    for (auto i = bno[l]; i <= bno[N]; i++) {
        res += bs[i].cnts[qv - bs[i].delta + D];
        // cout<<"i="<<(i)<<", "; cout<<"res="<<(res)<<", "; cout << endl; // db i,res
        // _C(qv - bs[i].delta + D);
    }
    return res;
}

void update(int l, int v) { // r == N 
    if (l > N) return;

    if (l != L[bno[l]]) {
        fix(bno[l]); 
        auto &b = bs[bno[l]];
        for (int i = l; i <= R[bno[l]]; i++) {
            int trueIdx = i - b.l, old = b.vs[trueIdx];
            // cout<<"l="<<(l)<<", "; cout<<"bno[l]="<<(bno[l])<<", "; cout<<"v="<<(v)<<", "; cout<<"trueIdx="<<(trueIdx)<<", "; cout << "b.vs=["; for (auto __x:b.vs)cout<<__x<<", "; cout<<"], "; cout << endl; // db l,bno[l],v,trueIdx,I:b.vs
            b.cnts[old + D]--;
            b.cnts[old + v + D]++;
            _C(old + D);
            _C(old + v + D);
            b.vs[trueIdx] += v;
        }
        if (bno[l] == bno[N]) // last
            return;
        l = L[bno[l] + 1];
    }
    for (auto i = bno[l]; i <= bno[N]; i++)
        bs[i].delta += v;
}

void debugsqrt() {
    cout << ("DEBUG-----") << '\n';
    int lst = bno[N];
    for (auto i = 1; i <= lst; i++) {
        auto &b = bs[i];
        // cout<<"i="<<(i)<<", "; cout<<"L[i]="<<(L[i])<<", "; cout<<"R[i]="<<(R[i])<<", "; cout<<"b.l="<<(b.l)<<", "; cout << endl; // db i,L[i],R[i],b.l
        cout<<"i="<<(i)<<", "; cout<<"b.l="<<(b.l)<<", "; cout<<"b.delta="<<(b.delta)<<", "; cout << "b.vs=["; for (auto __x:b.vs)cout<<__x<<", "; cout<<"], "; cout << endl; // db i,b.l,b.delta,I:b.vs

        vector<int> keys(all(b.vs));
        UNIQUE(keys);
        for (auto x : keys) {
            cout<<"x="<<(x)<<", "; cout<<"b.cnts[x+D]="<<(b.cnts[x+D])<<", "; cout << endl; // db x,b.cnts[x+D]
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<pii> vs;
    cin >> (N);
    for (auto i = 1; i <= N; i++) {
        cin >> (P[i]);
        vs.eb(P[i], i);

        bno[i] = (i + B - 1) / B;
        if (!L[bno[i]]) L[bno[i]] = i;
        R[bno[i]] = i;
    }
    bno[N + 1] = bno[N] + 1;
    L[bno[N + 1]] = N + 1;
    bno[0] = bno[1] - 1;
    R[bno[0]] = 0;

    // initially everything is smaller
    for (auto i = 1; i <= N; i++) {
        auto &b = bs[bno[i]];
        if (!b.l)
            b.l = i;
        b.delta = 0;
        b.cnts[-i + D]++;
        b.vs.pb(-i);
    }

    sort(all(vs), greater<pii>());
    for (auto p : vs) { // (value, pos)
        fix(bno[p.sn]);
        // cout<<"bs[bno[p.sn]].get(p.sn)="<<(bs[bno[p.sn]].get(p.sn))<<", "; cout << endl; // db bs[bno[p.sn]].get(p.sn)
        ans += 1 + query(p.sn + 1, bs[bno[p.sn]].get(p.sn));
        update(p.sn, 2);
        // cout<<"p.fs="<<(p.fs)<<", "; cout<<"p.sn="<<(p.sn)<<", "; cout<<"ans="<<(ans)<<", "; cout << endl; // db p.fs,p.sn,an

        // debugsqrt();
    }
    cout << (ans) << '\n';

    return 0;
}

