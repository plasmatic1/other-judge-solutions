#include <bits/stdc++.h>
using namespace std;
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef pair<int,int> pii;

int T,N,L;
ll cnt[5005],tt[5005];

int main(){
    freopen("data.txt","r",stdin);
    freopen("data.out","w",stdout);
    scanf("%d",&T);
    int ttt = 1;
    while(T--){
        scanf(" %d %d",&N,&L);
        for(int i=1; i<=N;  i++)
            cnt[i] = tt[i] = 0;
        set<pair<int,pii>> s;
        while(L--){
            int t,team,prob,id,score;
            scanf(" %d %d %d %d %d",&t,&team,&prob,&id,&score);
//            if(score && s.count(mp(team,id))) assert(false);
            if(score && !s.count(mp(team,mp(prob,id)))){
                cnt[team]+=100*id;
                tt[team]+=t;
                s.insert(mp(team,mp(prob,id)));
            }
        }
        vector<int> v;
        for(int i=1; i<=N;  i++) v.pb(i);
        stable_sort(v.begin(),v.end(),[](int a, int b){
            if(cnt[a] == cnt[b]) {
                if (tt[a] == tt[b]) return a < b;
                return tt[a] < tt[b];
            }
            return cnt[a]>cnt[b];
        });
        printf("Case #%d: ",ttt++);
        for(int check:v)
            printf("%d ",check);
        printf("\n");
    }
}