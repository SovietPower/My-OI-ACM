/*
对于$c_p$，如果存在一个最靠右的$i$使得$a_i\geq c_{i-1}+b_i$，则$c_p=a_i+\sum_{j=i+1}^pb_j=\max\{a_i,c_{i-1}+b_i\}+\sum_{j=i+1}^pb_j$。
因为是取$\max$，$a_i<c_{i-1}+b_i$时不会被算，$c_p$就可以直接写成$\max_{i=0}^p\{a_{i}+\sum_{j=i+1}^pb_j\}=\max_{i=0}^p\{a_{i}+\sum_{j=i+1}^nb_j\}-\sum_{j=p+1}^nb_j$。树状数组维护$b$的区间和，线段树维护括号里的值，每次询问区间查询最大值即可。
操作$1$即单点修改$a_i$；设操作$2$令$b_i$增加$v$，只需令线段树上$1\sim i-1$加$v$即可。
另一种推的方法是
$$\begin{aligned}c_p&=\max\{\max\{c_{i-2}+b_{i-1},a_{i-1}\}+b_i,a_i\}\\&=\max\{\max\{c_{i-2},a_{i-1}-b_{i-1}\},a_i-b_i-b_{i-1}\}+b_i+b_{i-1}\\&=...=\sum_{i=1}^pb_i+\max\{0,\max_{i=1}^p\{a_i-\sum_{j=i}^pb_j\}\}\end{aligned}$$

和上面一样做即可。
*/
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fir first
#define sec second
#define pb push_back
#define ll long long

const int N = 2e5+10;
const ll inf = 1e18;

int n, m;
ll a[N], b[N], c[N];
ll sumb[N];
void add(int x,ll y){
    for(; x<N; x += x&-x) c[x] += y;
}
ll ask(int x){
    ll ret = 0;
    for(; x; x -= x&-x)  ret = ret + c[x];
    return ret;
}
struct node{
    int l, r;
    ll d, val;
}T[N*4];
void build(int p,int L,int R){
    T[p].l = L; T[p].r = R;
    T[p].d = 0;
    if(L == R){
        T[p].val = a[L] + (sumb[n]-sumb[L);
        return ;
    }
    int mid = (L+R)/2;
    build(p*2, L, mid);
    build(p*2+1, mid+1, R);
    T[p].val = max(T[p*2].val, T[p*2+1].val);
}
void spread(int p){
    if(T[p].d){
        T[p*2].val += T[p].d;
        T[p*2].d += T[p].d;
        T[p*2+1].val += T[p].d;
        T[p*2+1].d += T[p].d;
        T[p].d = 0;
    }
}
void change(int p,int L,int R,ll x){
    if(L <= T[p].l && R >= T[p].r){
        T[p].val += x;
        T[p].d += x;
        return ;
    }
    spread(p);
    int mid = (T[p].l+T[p].r)/2;
    if(L<=mid)change(p*2, L, R, x);
    if(R >mid)change(p*2+1, L, R, x);
    T[p].val = max(T[p*2].val, T[p*2+1].val);
}

ll ask(int p,int L,int R){
    if(L<=T[p].l && R>=T[p].r){
        return T[p].val;
    }
    spread(p);
    int mid = (T[p].l+T[p].r)/2;
    ll ret = -inf;
    if(L<=mid) ret = max(ret, ask(p*2, L, R));
    if(R >mid) ret = max(ret, ask(p*2+1,L,R));
    return ret;
}

int main(){
    while(scanf("%d%d",&n,&m) == 2){
        for(int i=1; i<=n; i++) scanf("%lld", a+i);
        for(int i=0; i<=n; i++) c[i] = 0;
        sumb[0] = 0;
        for(int i=1; i<=n; i++) {
            scanf("%lld", b+i);
            add(i, b[i]);
            sumb[i] = sumb[i-1]+b[i];
        }
        build(1,1,n);
        ask(1,1,2);
        while(m--){
            int op; scanf("%d",&op);
            //cout<<op<<endl;
            if(op == 1){
                int x; ll y; scanf("%d%lld",&x,&y);
                change(1, x, x, y-a[x]);
                a[x] = y;
            } else if(op == 2){
                int x; ll y; scanf("%d%lld",&x,&y);
                if(x != 1) change(1, 1, x-1, y-b[x]);
                add(x, y-b[x]);
                b[x] = y;
            } else {
                int x; scanf("%d",&x);
                ll d = ask(n)-ask(x);
                ll ans = max(ask(x), ask(1,1,x)-d);
                printf("%lld\n",ans);
            }
        }
    }
    return 0;
}
