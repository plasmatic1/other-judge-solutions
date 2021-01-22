#include <bits/stdc++.h>

using namespace std;
// , d[2001];
#define O 100000
#define __D 1000000007

typedef long long ll;

ll t[O << 2];
ll g(int i, int l, int r, int a, int b){
    if(l==a&&r==a)return t[i]=(t[i]+b)%__D;
    if(l>a||r<a)return t[i];
    int c=(l+r)>>1;
    return t[i]=(g(i<<1,l,c,a,b)+g(i<<1|1,c+1,r,a,b))%__D;
}

inline void f() {
    for ( int i = 0; i < O; i++)
        g(1,1,O,i+1,i);
}

int main() {
    for(int i = 0; i < 55; i++)
        f();

    puts("Hello, World!\n");

    return 0;
}