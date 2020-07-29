// f-pond-skater.yml
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3f;
template <typename V> using uset = unordered_set<V>;
template <typename K, typename V> using umap = unordered_map<K, V>;
template <typename C> int sz(C &v) { return v.size(); }

const int DIR[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

struct Pos {
    int x, y;
};

struct Ent { 
    int x, y, predir;
};

int R, C, K;
Pos st, en;
vector<vector<bool>> grid;
vector<vector<ll>> dis[5];
deque<Ent> q;

// priority_queue<Ent> q;


ll make_dp(ll dis, ll k) {
    return (k << 32LL) | dis;
}
const ll MSK = (1LL << 32) - 1;
inline ll gdis(ll dp) { return dp & MSK; }
inline ll gk(ll dp) { return dp >> 32LL; }

bool cmp(const ll a, const ll b) {
    return gdis(a) == gdis(b) ? gk(a) < gk(b) : gdis(a) < gdis(b);
}

inline void tryPush(int x, int y, int predir, int ndis, int k, bool inc) {
    ll disPair = make_dp(ndis, k);
    if (x < 0 || x >= R || y < 0 || y >= C || !grid[x][y] || cmp(dis[predir][x][y], disPair)) return;

    Ent ent{x, y, predir};
    if (gdis(dis[predir][x][y]) > ndis) {
        if (inc)
            q.push_back(ent);
        else
            q.push_front(ent);
    }
    dis[predir][x][y] = disPair;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> R >> C >> K;
    cin >> st.x >> st.y >> en.x >> en.y;
    grid.assign(R, vector<bool>(C, true));
    for (int i = 0; i < R; i++) {
        string tmp;
        cin >> tmp;
        for (int j = 0; j < C; j++)
            grid[i][j] = tmp[j] == '.';
    }
    st.x--; st.y--;
    en.x--; en.y--;

    for (int i = 0; i < 5; i++) {
        dis[i].assign(R, vector<ll>(C, make_dp(INF, 0)));
        // inq[i].assign(R, vector<bool>(C, false));
    }

    // assert(0);
    // cout << st.x<<' '<<st.y<<endl;

    dis[4][st.x][st.y] = make_dp(0, 0);
    q.push_back({st.x, st.y, 4});
    // assert(0);
    while (!q.empty()) {
        auto c = q.front();
        q.pop_front();
        int cdis = gdis(dis[c.predir][c.x][c.y]), ck = gk(dis[c.predir][c.x][c.y]);
        // inq[c.predir][c.x][c.y] = false;

        // if (c.x == en.x && c.y == en.y) {
        //     cout << cdis << '\n';
        //     return 0;
        // }

        if (cmp(dis[c.predir][c.x][c.y], make_dp(cdis, ck))) continue;

        // cout << "pos=("<<c.x<<", "<<c.y<<") dir="<<c.predir<<" dis=("<<c.dis<<", "<<c.k<<")"<<endl;

        if (c.predir == 4) {
            for (int i = 0; i < 4; i++) {
                tryPush(c.x + DIR[i][0], c.y + DIR[i][1], i, cdis + 1, 1, true);
            }
        }
        else {
            for (int i = 0; i < 4; i++) {
                bool inc = i != c.predir || ck == K;
                int newK = inc ? 1 : (ck + 1);
                tryPush(c.x + DIR[i][0], c.y + DIR[i][1], i, cdis + inc, newK, inc);
            }
        }
    }

    // cout << "-1\n";
    int ans = INF;
    for (int i = 0; i < 5; i++)
        ans = min(ans, (int)gdis(dis[i][en.x][en.y]));
    cout << (ans == INF ? -1 : ans) << '\n';

    return 0;
}

