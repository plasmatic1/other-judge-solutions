#include "bits/stdc++.h"
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
template<typename T> int sz(const T &a){return int(a.size());}
const int MN=402;
int kmp[MN];
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int q;
    cin>>q;
    while(q--){
        string s,t;
        cin>>s>>t;
        int ans=0;
        for(int i=0;i<(1<<sz(s));i++){
            deque<char> deq;
            for(int j=0;j<sz(s);j++){
                if(i&(1<<j)){
                    deq.push_back(s[j]);
                }
                else{
                    deq.push_front(s[j]);
                }
            }
            string a(deq.begin(),deq.end());
            a=t+"$"+a;
            int cnt=0;
            for(int j=1;j<sz(a);j++){
                int p=kmp[j-1];
                while(p!=0&&a[p]!=a[j])p=kmp[p-1];
                if(a[p]==a[j])p++;
                kmp[j]=p;
                if(kmp[j]==sz(t))cnt++;
            }
            ans=max(ans,cnt);
        }
        printf("%d\n",ans);
    }
    return 0;
}
