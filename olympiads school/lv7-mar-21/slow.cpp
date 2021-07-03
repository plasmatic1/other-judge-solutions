
// ./dans-monkeys.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

// const int MN = 3e5 + 1;
const int MN = 1001;
int R, C, Q,
    fcol[MN];

int grid[MN][MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> R >> C >> Q;
    int ctr = 0;
    for (auto i = 0; i < R; i++)
        for (auto j = 0; j < C; j++)
            grid[i][j] = ctr++;

    while (Q--) {
        int r, c; cin >> r >> c;
        r--; c--;
        cout << grid[r][c]+1 << '\n';
        rotate(grid[r] + c, grid[r] + c + 1, grid[r] + C);
        // printf("grid=[\n");
        // for (auto i = 0; i < R; i++) {
        //     for (auto j = 0; j < C; j++) {
        //         printf("%d ", grid[i][j]);
        //     }
        //     printf("\n");
        // }
        vector<int> col;
        for (auto i = r; i < R; i++)
            col.push_back(grid[i][C-1]);
        rotate(col.begin(), col.begin()+1, col.end());
        for (auto i = r; i < R; i++)
            grid[i][C-1] = col[i-r];
        // printf("r=%d c=%d\n",r,c);
        // printf("grid=[\n");
        // for (auto i = 0; i < R; i++) {
        //     for (auto j = 0; j < C; j++) {
        //         printf("%d ", grid[i][j]);
        //     }
        //     printf("\n");
        // }
    }

    return 0;
}
