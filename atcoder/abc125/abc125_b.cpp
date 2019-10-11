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

const int MAX = 51;
int n, tot = 0,
		v[MAX], c[MAX];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n);

	for (int i = 0; i < n; ++i)
		scan(v[i]);
	for (int i = 0; i < n; ++i)
		scan(c[i]);

	for (int i = 0; i < n; ++i) {
		int dif = v[i] - c[i];
		if (dif > 0)
			tot += dif;
	}

	cout << tot << "\n";

	return 0;
}
