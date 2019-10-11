#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Defines and one-liners
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
template <typename T> inline T& back(vector<T> &vec) { return *(vec.end() - 1); }
template <typename T> inline void pop(vector<T> &vec) { return vec.erase(vec.end() - 1); }

// Scan, Debug, and other nonsense
template <typename T> ostream& operator<<(ostream& out,vector<T> iter){out<<"[";for(auto t:iter){out<<t<<", ";}out<<"]";return out;}
template <typename T> void printArray(ostream& out,T* arr,int sz){out<<"[";for(int i=0;i<sz;i++){out<<arr[i]<<", "; } out<<"]";}
#define OUT_OPERATOR(type, propa, propb) ostream& operator<<(ostream& out,type obj){out<<"("<<#propa<<"="<<obj. propa<<", "<<#propb<<"="<<obj. propb<<")";return out;}

void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F f,R... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

template <int MAX>
struct Graph {
    int n, m, __ba, __bb; vector<int> matrix[MAX];
    void init(int n0, int m0) { n = n0; m = m0; }
    inline void addEdge(int a, int b) { matrix[a].push_back(b); }
    inline auto& adjs(int x) { return matrix[x]; }
    Graph& operator=(const Graph o) { n = o.n; m = o.m; copy(o.matrix, o.matrix + n + 1, matrix); return *this; }
    void input(bool undirected) { // Reads a graph's edges from stdin
        for (int i = 0; i < m; i++) {
            cin >> __ba >> __bb;
            addEdge(__ba, __bb);
            if (undirected) addEdge(__bb, __ba);
        }
    }
};
template <int MAX, typename T>
struct CentroidDecomposition {
    int sz[MAX], pars[MAX], lay[MAX]; bool blocked[MAX]; T& graph;
    CentroidDecomposition(T& graph0) : graph(graph0) { memset(blocked, false, sizeof blocked); }
    int gsz(int cur, int par) {
        sz[cur] = 1;
        for (int adj : graph.adjs(cur))
            if ((adj ^ par) && !blocked[adj])
                sz[cur] += gsz(adj, cur);
        return sz[cur];
    }
    int gcentroid(int cur, int par, int half) {
        for (int adj : graph.adjs(cur))
            if ((adj ^ par) && !blocked[adj] && sz[adj] > half)
                return gcentroid(adj, cur, half);
        return cur;
    }
    void dfs() { assert(("Not implemented yet!", 0)); }
    int decomp(int cur = 1, int clay = 0) {
        gsz(cur, -1);
        if (sz[cur] == 1) {
            lay[cur] = clay; 
            return cur;
        }

        int centroid = gcentroid(cur, -1, sz[cur] >> 1);
        lay[centroid] = clay;
        for (int adj : graph.adjs(centroid)) {
            if (!blocked[adj]) {
                assert(("Not implemented yet!", 0)); // Implement subtree dfs
            }
        }

        blocked[centroid] = true;
        for (int adj : graph.adjs(centroid))
            if (!blocked[adj])
                pars[decomp(adj, clay + 1)] = centroid;
        return centroid;
    }
};

const int MN = 1e5 + 1;
int n, q, bt, ba, bb,
    val[MN];
Graph<MN> g;
CentroidDecomposition<MN, Graph<MN>> cent;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, q);

    for (int i = 1; i <= n; i++)
        scan(val[i]);

    g.init(n, n - 1);
    g.input(true);

    cent.pars[cent.decomp()] = -1;

    for (int i = 0; i < q; i++) {
        scan(bt, ba, bb);

        if (bt == 1) { 

        }
        else { // bt == 2
            //
        }
    }

    return 0;
}