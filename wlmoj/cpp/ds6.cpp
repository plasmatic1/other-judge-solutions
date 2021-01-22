#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MM = 2e5+5;

struct Tree{
#define l T[x].ch[0]
#define r T[x].ch[1]
    struct node{
        int ch[2] = {0, 0}, p = 0, flip = 0, pp = 0;
        ll sz = 0, val = 0, max = INT_MIN, min = INT_MAX, sum = 0, lp = 0, fix = 0;
        ll fixv = 0;
    } T[MM];
    
    int dir(int x, int y){
        if(x) assert(T[x].ch[1] == y or T[x].ch[0] == y);
        return T[x].ch[1] == y;
    }
    
    void set(int x, int d, int y){
        if(x) T[x].ch[d] = y, pull(x);
        if(y) T[y].p = x;
    }
    
    void pull(int x){
        if(!x) return;
        push(l); push(r);
        T[x].max = max({T[x].val, T[l].max, T[r].max});
        T[x].min = min({T[x].val, T[l].min, T[r].min});
        T[x].sum = T[x].val + T[l].sum + T[r].sum;
        T[x].sz = 1 + T[l].sz + T[r].sz;
    }
    
    void push(int x){
        if(!x) return;
        if(T[x].flip){
            swap(l, r);
            T[l].flip ^= 1, T[r].flip ^= 1;
            T[x].flip = 0;
        }
        if(T[x].fix){
            T[x].val = T[x].min = T[x].max = T[x].lp;
            T[x].sum = T[x].sz*T[x].lp;

            T[l].lp = T[r].lp = T[x].lp;
            T[x].lp = 0;
            T[l].fix = T[r].fix = 1;
            T[x].fix = 0;
        }
        else{
            T[x].val += T[x].lp;
            T[x].max += T[x].lp;
            T[x].min += T[x].lp;
            T[x].sum += T[x].sz*T[x].lp;

            T[l].lp += T[x].lp;
            T[r].lp += T[x].lp;
            T[x].lp = 0;
        }
    }
    
    void rotate(int x, int d){
        if(!x) return;
        int y = T[x].p, z = T[y].p, w = T[x].ch[d];
        swap(T[x].pp, T[y].pp); //if !z
        set(y, !d, w);
        set(x, d, y);
        set(z, dir(z, y), x);
    }
    
    void splay(int x){
        if(!x) return;
        push(x);
        while(T[x].p){
            int y = T[x].p, z = T[y].p;
            push(z); push(y); push(x);
            int dx = dir(y, x), dy = dir(z, y);
            if(!z)
                rotate(x, !dx);
            else if(dx == dy)
                rotate(y, !dy), rotate(x, !dx);
            else
                rotate(x, !dx), rotate(x, !dy);
        }
    }
    
    int access(int u){
        int x = 0, y = u;
        while(y){
            splay(y); splay(x);
            int w = T[y].ch[1];
            T[x].pp = 0;
            swap(T[w].p, T[w].pp);
            set(y, 1, x);

            x = y;
            y = T[y].pp;
        }
        splay(u);
        return x;
    }
    
    void root(int x){
        access(x);
        T[l].flip ^= 1;
        swap(T[l].p, T[l].pp);
        set(x, 0, 0);
    }
    
    int lca(int x, int y){
        access(x);
        return access(y);
    }

    void update(int x, int y, int v, int fix){
        root(x), access(y);
        if(fix){
            T[y].fix = 1;
            T[y].lp = v;
        }
        else{
            T[y].lp += v;
        }
    }
    node query(int x, int y){
        root(x); access(y);
        return T[y];
    }
    
    void cut(int x, int y){
        root(x); access(x); splay(y);
        assert(T[y].pp == x);
        T[y].pp = 0;
    }
    
    void link(int x, int y){
        root(y);
        T[y].pp = x;
    }
    
    void change(int x, int y){
        if(lca(x, y) != x){
            access(x);
            cut(x, T[x].ch[0]);
            link(x, y);
        }
    }
    
} LCT;

int n, q, root;
ll a[MM];

int main(){
//    freopen("in.txt", "r", stdin);
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>q;
    for(int i = 1; i <= n; i++){
        cin>>a[i];
        LCT.update(i, i, a[i], 1);
    }
    for(int i = 0,u,v; i < n-1; i++){
        cin>>u>>v;
        LCT.link(u, v);
    }
    cin>>root;
    
    for(int i = 0,op,x,y; i < q; i++){
        ll z;
        LCT.root(root);
        x=y=z=-69;
        cin>>op>>x;
        if(op)
            cin>>y;
        if(op == 1 or op == 2)
            cin>>z;
        
//        cout<<op<<' '<<x<<' '<<y<<' '<<z<<endl;
        
        if(op == 0)
            root = x;
        if(op == 1)
            LCT.update(x, y, z, 1);
        if(op == 2)
            LCT.update(x, y, z, 0);
        if(op == 3)
            cout<<LCT.query(x, y).min<<'\n';
        if(op == 4)
            cout<<LCT.query(x, y).max<<'\n';
        if(op == 5)
            cout<<LCT.query(x, y).sum<<'\n';
        if(op == 6)
            LCT.change(x, y);
        if(op == 7)
            cout<<LCT.lca(x, y)<<'\n';
    }
    
    return 0;
}