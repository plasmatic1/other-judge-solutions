#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MN = 1e5 + 1;
int n, q,
    dis[26][26], par[26][26];
vector<int> g[26];
string s;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> q >> s;
    s = " " + s;

    for (int i = 1; i < n; i++) {
        int a = s[i] - 'a', b = s[i + 1] - 'a';
        g[a].push_back(b);
    }
    
    memset(dis, -1, sizeof dis);
    memset(par, -1, sizeof par);
    for (int i = 0; i < 26; i++) {
        queue<int> nxt;
        nxt.push(i);
        dis[i][i] = 0;
        while (!nxt.empty()) {
            int cur = nxt.front(); nxt.pop(); int lv = dis[i][cur];
            for (int adj : g[cur]) {
                if (dis[i][adj] == -1) {
                    dis[i][adj] = lv + 1;
                    par[i][adj] = cur;
                    nxt.push(adj);
                }
                else if (dis[i][adj] == lv + 1 && par[i][adj] > cur) {
                    par[i][adj] = cur;
                }
            }
        }
    }

    while (q--) {
        char aa, bb;
        cin >> aa >> bb;
        int a = aa - 'a', b = bb - 'a';

        if (dis[a][b] == -1)
            cout << "-1\n";
        else {
            string ans = "";
            int cp = b;
            while (cp != -1) {
                ans += (char)(cp + 'a');
                cp = par[a][cp];
            }
            reverse(ans.begin(), ans.end());

            cout << ans << '\n';
        }
    }
}
