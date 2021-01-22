#include "bits/stdc++.h"
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
template<typename T>
int sz(const T &a){return int(a.size());}
int n;
#define MID int mid = (l + r) / 2, lhs = i + 1, rhs = i + (mid - l + 1) * 2;
const int MAXN=2e5+1;
const int MN = 2e5 + 1;
int seg[MN*2], lazy[MN*2];
void push(int i, int l, int r) {
    if (lazy[i]) {
        MID;
        seg[i] += lazy[i];
        if (l != r) {
            lazy[lhs] += lazy[i];
            lazy[rhs] += lazy[i];
        }
        lazy[i] = 0;
    }
}
int query(int ql, int qr, int i=1, int l=1, int r=n) {
    if (l > qr || r < ql) return INT_MAX;
    push(i, l, r);
    if (l >= ql && r <= qr) return seg[i];
    MID;
    return min(query(ql, qr, lhs, l, mid), query(ql, qr, rhs, mid+1, r));
}
int update(int ql, int qr, int qv, int i=1, int l=1, int r=n) {
    push(i, l, r);
    if (l > qr || r < ql) return seg[i];
    if (l >= ql && r <= qr) {
        lazy[i] = qv;
        push(i, l, r);
        return seg[i];
    }
    MID;
    return seg[i] = min(update(ql, qr, qv, lhs, l, mid), update(ql, qr, qv, rhs, mid+1, r));
}
map<int,stack<int>> colour;
vector<int> clowns[MAXN];
pii shoes[MAXN];
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int m;
    cin>>n>>m;
    for(int i=0;i<n;i++){
        cin>>shoes[i].second>>shoes[i].first;
    }
    sort(shoes,shoes+n);
    int a,b;
    for(int i=0;i<n;i++){
        cin>>a>>b;
        int loc=lower_bound(shoes,shoes+n,b,[&](const pii it, const int val){
            return it.first<val;
        })-shoes;
        clowns[loc].push_back(a);
    }
    int clownam=0;
    int ans=0;
    for(int i=n-1;i>=0;i--){
        colour[shoes[i].second].push(i);
        clownam+=sz(clowns[i]);
        update(i+1,i+1,n-i-clownam);
        for(auto x:clowns[i]){
            if(sz(colour[x])){
                if(i+2<=colour[x].top()+1)update(i+2,colour[x].top()+1,-1);
                if(query(1,n)>=0){
                    ans++;
                    colour[x].pop();
                }
                else update(i+2,colour[x].top()+1,1);
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}