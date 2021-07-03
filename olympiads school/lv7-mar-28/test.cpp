#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

// #ifndef ONLINE_JUDGE
// template<typename T>
// void pr(T a){std::cerr<<a<<std::endl;}
// template<typename T,typename... Args>
// void pr(T a, Args... args) {std::cerr<<a<<' ',pr(args...);}
// #else
template<typename... Args>
void pr(Args... args){}
// #endif

using namespace std;
using ld = double;
const int MM = 2005;
const ld inf = 1e69;

int n, m, v, e;
int a[MM], b[MM];
ld p[MM];
int dis[MM][MM];
ld dp[MM][MM][3];
//dp[i][how many used][a, try for b but a, try for b but b]?

int main(){
	cin>>n>>m>>v>>e;
	for(int i = 1; i <= n; i++)
		cin>>a[i];
	for(int i = 1; i <= n; i++)
		cin>>b[i];
	for(int i = 1; i <= n; i++)
		cin>>p[i];
	memset(dis, 0x3f, sizeof dis);
	
	for(int i = 0,j,k,l; i < e; i++){
		cin>>j>>k>>l;
		dis[k][j] = dis[j][k] = min(dis[j][k], l);
	}
	for(int i = 1; i <= v; i++)
		dis[i][i] = 0;

	for(int k = 1; k <= v; k++){
		for(int i = 1; i <= v; i++){
			for(int j = 1; j <= v; j++){
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}
	}

	for(int i = 0; i < MM; i++){
		for(int j = 0; j < MM; j++){
			dp[i][j][0] = dp[i][j][1] = inf;
		}
	}
	dp[1][1][0] = 0;
	dp[1][2][1] = 0;
	dp[1][2][2] = 0;

	for(int i = 2; i <= n; i++){
		int aa = dis[a[i-1]][a[i]];
		int ab = dis[a[i-1]][b[i]];
		int ba = dis[b[i-1]][a[i]];
		int bb = dis[b[i-1]][b[i]];
		pr(i, aa, ab);
		for(int j = 1; j <= m+1; j++){
			dp[i][j][0] = min(dp[i-1][j][0] + aa,
				(dp[i-1][j][2] + ba)*p[i-1] + (dp[i-1][j][1] + aa)*(1-p[i-1]));
			
			dp[i][j][1] = dp[i-1][j-1][0] + aa;
			if(j > 1)
				dp[i][j][1] = min(dp[i][j][1], (dp[i-1][j-1][2] + ba)*p[i-1] + (dp[i-1][j-1][1] + aa)*(1-p[i-1]));
			
			dp[i][j][2] = dp[i-1][j-1][0] + ab;
			if(j > 1)
				dp[i][j][2] = min(dp[i][j][2], (dp[i-1][j-1][2] + bb)*p[i-1] + (dp[i-1][j-1][1] + ab)*(1-p[i-1]));
			pr("j", j, dp[i][j][0], dp[i][j][1], dp[i][j][2]);
		}
	}
	ld ans = inf;
	ans = dp[n][1][0];
	for(int i = 2; i <= m+1; i++){
		ans = min(ans, min(dp[n][i][0], dp[n][i][1]*(1-p[n]) + dp[n][i][2]*p[n]));
	}
	// cout<<fixed<<setprecision(2)<<ans<<'\n';
	printf("%.2lf\n", ans);
	fflush(stdout);
	assert(ans <= (n-1)*100*(v-1) + 1e-6);
}
