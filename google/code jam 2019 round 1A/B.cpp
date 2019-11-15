//============================================================================
// Name        : 548C.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Scan and Debug
void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F &f, R&... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

const int COS[7] = {4, 3, 5, 7, 11, 13, 17};
int t, n, m, buf, verdict;

int main(){
	cin >> t >> n >> m;
	
	int comul = 1;
	for (int x : COS)
	    comul *= x;

	for (int tcn_ = 1; tcn_ <= t; ++tcn_) {
		int mod[7]; 
		memset(mod, 0, sizeof mod);
		
		for (int i = 0; i < 7; i++) {
		    for (int j = 0; j < 18; j++)
		        cout << COS[i] << ' ';
		    cout << '\n';
		    cout.flush();
		    
		    for (int j = 0; j < 18; j++) {
		        int x;
		        cin >> x;
		        assert(x != -1);
		        mod[i] += x;
		    }
		    mod[i] %= COS[i];
		}
		
		int work = -1;
		for (int i = 1; i <= comul; i++) {
		    bool flag = true;
		    for (int j = 0; j < 7; j++)
		        flag &= i % COS[j] == mod[j];
		    if (flag) {
		        work = i;
		        break;
		    }
		}
		
		cout << work << '\n';
		cout.flush();
		int res;
		cin >> res;
		assert(res == 1);
	}
}
