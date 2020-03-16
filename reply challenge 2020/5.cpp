#pragma region
#include <bits/stdc++.h>
using namespace std;
// Common Type shorteners and int128
using ll = long long; using ull = unsigned long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<ll, ll>;
template <typename T> using vec = vector<T>;
template <typename K, typename V> using umap = unordered_map<K, V>; template <typename K> using uset = unordered_set<K>;
using vi = vec<int>; using vl = vec<ll>; using vpi = vec<pii>; using vpl = vec<pll>;
#ifdef __SIZEOF_INT128__
using int128 = __int128_t; using uint128 = __uint128_t;
#endif
template<typename I> string intStr(I x) { string ret; while (x > 0) { ret += (x % 10) + '0'; x /= 10; } reverse(ret.begin(), ret.end()); return ret; } // Int to string
// Shorthand Macros
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define mpr make_pair
#define mtup make_tuple
#define pb push_back
#define popcount __builtin_popcount
#define clz __builtin_clz
#define ctz __builtin_ctz
#define finline __attribute__((always_inline))
// Shorthand Function Macros
#define sz(x) ((int)((x).size()))
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for (__typeof(a) i = a; i < b; i++)
#define reprev(i, a, b) for (__typeof(a) i = a; i > b; i--)
#define repi(a, b) rep(i, a, b)
#define repj(a, b) rep(j, a, b)
#define repk(a, b) rep(k, a, b)
#define Cmplt(type) bool operator<(const type &o) const
#define Cmpgt(type) bool operator>(const type &o) const
#define Cmpfn(name, type) bool name(const type &a, const type &b)
#define Inop(type) istream& operator>>(istream& in, type &o)
#define Outop(type) ostream& operator<<(ostream& out, type o)
#define Pow2(x) (1LL << (x))
#define scn(type, ...) type __VA_ARGS__; scan(__VA_ARGS__) // scn -> Short for SCan New
// Shorthand Functions
template<typename T> inline void maxa(T& st, T v) { st = max(st, v); }
template<typename T> inline void mina(T& st, T v) { st = min(st, v); }
inline void setprec(ostream& out, int prec) { out << setprecision(prec) << fixed; }
// Out operators and printing for arrays and vectors
template <typename T> ostream& operator<<(ostream& out,vector<T> iter){out<<"[";for(auto t:iter){out<<t<<", ";}out<<"]";return out;}
template <typename T> string arrayStr(T *arr,int sz){string ret = "[";for(int i=0;i<sz;i++){ret+=to_string(arr[i])+", "; } return ret + "]";}
template <typename T> void printArray(T *arr,int sz){for(int i=0;i<sz;i++){cout<<arr[i]<<" "; } cout<<"\n";}
// I/O Operations
inline void scan(){}
template<typename F, typename... R> inline void scan(F &f,R&... r){cin>>f;scan(r...);}
template <typename F> inline void println(F t){cout<<t<<'\n';}
template<typename F, typename... R> inline void println(F f,R... r){cout<<f<<" ";println(r...);}
inline void print(){}
template<typename F, typename... R> inline void print(F f,R... r){cout<<f;print(r...);}
// Debugging
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
#pragma endregion

const int MN = 501, MX = 5e5 + 50;
int N, M;
char grid[MN][MN * 2];
int from[MX];
bool gone[MX];
int st, en, val[MX],ogval[MX];
vi g[MX];
bool gst[MX];
bool gen[MX];
struct pp {
    int a, b, c;
}; pp uconv(int x) {
    return pp{x / (2 * M), (x % (2 * M)) / 2, x & 1};
}
int conv(int a, int b, bool c) {
    return a * 2 * M + b * 2 + c;
}

void buildGraph() {
    repi(0, N) {
        repj(0, M) {
            if (grid[i][2 * j] == 'S')
                st = conv(i, j, false);
            else if (grid[i][2 * j + 1] == 'S')
                st = conv(i, j, true);
            else if (grid[i][2 * j] == 'D')
                en = conv(i, j, false);
            else if (grid[i][2 * j + 1] == 'D')
                en = conv(i, j, true);

            if (grid[i][2 * j] != 'S' && grid[i][2 * j] != 'D')
                val[conv(i, j, false)] = grid[i][2 * j] - '0';
            if (grid[i][2 * j + 1] != 'S' && grid[i][2 * j + 1] != 'D')
                val[conv(i, j, true)] = grid[i][2 * j + 1] - '0';

            bool t = (i + j) & 1;
            if (!t) { // horizontal
                int c1 = conv(i, j, false), c2 = conv(i, j, true);
                if (j > 0) {
                    g[c1].pb(conv(i, j - 1, false));
                    g[c1].pb(conv(i, j - 1, true));
                }
                if (j < M - 1) {
                    g[c2].pb(conv(i, j + 1, false));
                    g[c2].pb(conv(i, j + 1, true));
                }
                g[c1].pb(c2);
                g[c2].pb(c1);
                if (i > 0) {
                    g[c1].pb(conv(i - 1, j, true));
                    g[c2].pb(conv(i - 1, j, true));
                }
                if (i < N - 1) {
                    g[c1].pb(conv(i + 1, j, false));
                    g[c2].pb(conv(i + 1, j, false));
                }
            }
            else { // vertical
                int c1 = conv(i, j, false), c2 = conv(i, j, true);
                if (i > 0) {
                    g[c1].pb(conv(i - 1, j, false));
                    g[c1].pb(conv(i - 1, j, true));
                }
                if (i < N - 1) {
                    g[c2].pb(conv(i + 1, j, false));
                    g[c2].pb(conv(i + 1, j, true));
                }
                g[c1].pb(c2);
                g[c2].pb(c1);
                if (j > 0) {
                    g[c1].pb(conv(i, j - 1, true));
                    g[c2].pb(conv(i, j - 1, true));
                }
                if (j < M - 1) {
                    g[c1].pb(conv(i, j + 1, false));
                    g[c2].pb(conv(i, j + 1, false));
                }
            }
        }
    }
    val[st] = val[en] = 50;
}

void clearGraph() {
    int sz = N * M * 2;
    repi(0, sz)
        g[i].clear();
}

bool bfs(){
    for(int i=0;i<=N*M*2-1;i++){
        gone[i]=false;
        from[i]=-1;
    }
    gone[st]=true;
    queue<int> q;
    q.push(st);
    while(sz(q)){
        int cur=q.front();
        q.pop();
        for(int x:g[cur]){
            if(!gone[x]&&val[x]&&!(cur==st&&x==en)){
                gone[x]=true;
                from[x]=cur;
                q.push(x);
            }
        }
    }
    return gone[en];
}
void bfsst(){
    gst[st]=true;
    gst[en]=true;
    queue<int> q;
    q.push(st);
    while(sz(q)){
        int cur=q.front();
        q.pop();
        for(int x:g[cur]){
            if(!gst[x]){
                gst[x]=true;
                if(val[x])q.push(x);
            }
        }
    }
}
void bfsen(){
    gen[en]=true;
    gen[st]=true;
    queue<int> q;
    q.push(en);
    while(sz(q)){
        int cur=q.front();
        q.pop();
        for(int x:g[cur]){
            if(!gen[x]){
                gen[x]=true;
                if(val[x])q.push(x);
            }
        }
    }
}
void markflow(){
    int cur=from[en];
    while(cur!=st){
        val[cur]--;
        cur=from[cur];
    }
}
void solve(int ca) {
    buildGraph();
    for(int i=0;i<=N*M*2-1;i++) ogval[i]=val[i],gst[i]=false,gen[i]=false;
    while(bfs()){
        markflow();
    }
    bfsst();
    bfsen();
    for(int i=0;i<=N*M*2-1;i++) {
        if(gst[i]&&gen[i]&&ogval[i]!=9&&i!=st&&i!=en){
            assert(val[i]==0);
            pp cur=uconv(i);
            printf("Case #%d: %d %d %d\n",ca,cur.a,cur.b,cur.c);
            return;
        }
    }
    printf("Case #%d: -1\n",ca);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
//    freopen("input-bandwidth-8dd1.txt","r",stdin);
//    freopen("data.out","w",stdout);
    freopen("data.txt","r",stdin);
    freopen("data.out","w",stdout);
    int T; cin >> T;
    int casin=1;
    while (T--) {
        // Input
        cin>>N>>M;
        for(int i=0; i<N; i++)
            for(int k=0; k<2*M; k++)
                cin >> grid[i][k];
        //Reset
        clearGraph();
        solve(casin);
        casin++;
    }
}