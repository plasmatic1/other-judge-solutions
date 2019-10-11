#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Scan and Debug
void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F f, R... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

const int MAX = 100010;
int n,
	arr[MAX], pfx[MAX], sfx[MAX];

int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n);

	for (int i = 1; i <= n; ++i) {
		scan(arr[i]);
		pfx[i] = sfx[i] = arr[i];
	}
	for (int i = 1; i <= n; ++i)
		pfx[i] = gcd(pfx[i - 1], pfx[i]);
	for (int i = n; i >= 1; --i)
		sfx[i] = gcd(sfx[i + 1], sfx[i]);

	int best = -1;
	for (int i = 1; i <= n; i++)
		best = max(best, gcd(pfx[i - 1], sfx[i + 1]));

	cout << best << "\n";

	return 0;
}
