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

const int MAX = 100001;
int n, negc = 0,
	arr[MAX];
bool zero = false;
ll tot = 0;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n);

	for (int i = 0; i < n; ++i) {
		scan(arr[i]);
		negc += arr[i] < 0;
		zero |= arr[i] == 0;
		tot += abs(arr[i]);

		arr[i] = abs(arr[i]);
	}
	sort(arr, arr + n);

	if (zero || (negc % 2 == 0))
		cout << tot << "\n";
	else
		cout << tot - (arr[0] << 1) << "\n";

	return 0;
}
