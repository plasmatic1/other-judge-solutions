#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define gc getchar()
#define pc(x) putchar(x)
template<typename T> void scan(T &x){x = 0;bool _=0;T c=gc;_=c==45;c=_?gc:c;while(c<48||c>57)c=gc;for(;c<48||c>57;c=gc);for(;c>47&&c<58;c=gc)x=(x<<3)+(x<<1)+(c&15);x=_?-x:x;}
template<typename T> void printn(T n){bool _=0;_=n<0;n=_?-n:n;char snum[65];int i=0;do{snum[i++]=char(n%10+48);n/= 10;}while(n);--i;if (_)pc(45);while(i>=0)pc(snum[i--]);}
template<typename First, typename ... Ints> void scan(First &arg, Ints&... rest){scan(arg);scan(rest...);}
template<typename T> void print(T n){printn(n);pc(10);}
template<typename First, typename ... Ints> void print(First arg, Ints... rest){printn(arg);pc(32);print(rest...);}

using namespace std;
using ll = long long;

vector<string> split(const string &str, char sep){
	vector<string> s;
    stringstream ss(str);
    string sp;
    while(getline(ss, sp, sep)){
        if(sp != "")
            s.push_back(sp);
    }
    return s;
}

ll val(const string &s){
	auto v = split(s, '.');
	ll val = 0, mul = 1;
	for(int i = 3; i >= 0; i--){
		val += mul*stoll(v[i]);
		mul *= 1000;
	}
	return val;
}

int n, m, ans;
map<ll, int> mp;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin>>n>>m;
	for(int i = 0; i < n; i++){
		string s;
		cin>>s;
		auto v = split(s, '-');
		ll l = val(v[0]), r = val(v[1]);
		mp[l]++;
		mp[r+1]--;
	}
	mp[-1] = 0;
	mp[LLONG_MAX/2] = 0;
	int sum = 0;
	for(auto &i: mp){
		sum += i.second;
		i.second = sum;
	}
	while(m--){
		string s;
		cin>>s;
		ll i = val(s);
		auto it = --mp.upper_bound(i);
		ans += (it->second > 0);
	}
	cout<<ans<<'\n';
}