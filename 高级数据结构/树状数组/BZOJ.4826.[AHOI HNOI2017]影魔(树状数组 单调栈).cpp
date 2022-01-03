/*
25340kb	2440ms
令$x$左边第一个比它大的点为$L$，右边第一个比它大的点为$R$。考虑三种情况：
1. 对于区间$[L,R]$，答案为$P1$；
2. 对于左端点在$L$，右端点在$x+1\sim R-1$的区间，答案各是$P2$；
3. 对于左端点在$L+1\sim x-1$，右端点在$R$的区间，答案也都是$P2$。
（这里不算区间$[L,x]$和$[x,R]$的贡献，在子区间里算。。）

然后考虑离线，把询问按右端点排序。如果只有$1,3$两种情况，在$R$处，给每个对应范围内的左端点加上贡献即可。现在实际是求的一个左端点在$[q_l,q_r]$内的和，所以现在答案是更新到$R$时，区间$[q_l,q_r]$的和。
对于第$2$种情况比较麻烦，要拆成$O(n)$个单点加？
考虑把它变成区间加。注意到右端点在$p$处统计$L$的贡献$P2$，和在$L$处给右端点在$p$时的贡献加$P2$是一样的，所以就可以在$L$处给区间$x+1\sim R-1$加$P2$。
这样的话左端点的贡献可能会多算，更新到$L-1$处时，给$[q_l,q_r]$的询问减去$[q_l,q_r]$的和即可。

另一种理解方式：
也可以考虑把$[l,r]$的贡献看做平面上的点$(l,r)$。同样离线，如果只有$1,3$，在横坐标$R$处的对应区间加上对应的答案，询问$[l,r]$就是横纵坐标都在$[l,r]$的矩形的和。
对于$2$，同上面的分析，变成在$L$处给对应右端点加上贡献。虽然$(x,y)$和$(y,x)$的贡献相同，但这相当于把原先横着的长条变成竖着的。注意到每个询问都是对角线在$y=x$上的正方形，所以这么做是对的。

两种都是同样的区间加、区间求和，可以树状数组。
复杂度$O(n\log n)$。

另外对于$[i,i+1]$这种区间的答案没有统计到，加上即可。

再简单记一下**树状数组区间修改、区间求和**：
类似区间修改单点查询，维护差分数组$d_i$的前缀和，那么$$\begin{aligned}sum[1..p]&=\sum_{i=1}^p\sum_{j=1}^id_j\\&=\sum_{i=1}^p(p-i+1)d_i\\&=(p+1)\sum_{i=1}^pd_i-\sum_{i=1}^pi\cdot d_i\end{aligned}$$

维护$d_i$和$i\cdot d_i$的前缀和即可（区间修改就是两个最一般的单点。不要想错...）。
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5,INF=1<<30;

int A[N],sk[N],L[N],R[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Quries
{
	int l,r,p,id,val;
	bool operator <(const Quries &x)const
	{
		return p<x.p;
	}
}q[N<<1];
struct Opt
{
	int l,r,p,val;
	bool operator <(const Opt &x)const
	{
		return p<x.p;
	}
}opt[N*3];
struct BIT
{
	int n,t1[N]; LL t2[N];
	#define lb(x) (x&-x)
	inline void Add(int p,int v)
	{
		for(int v2=p*v; p<=n; p+=lb(p)) t1[p]+=v,t2[p]+=v2;
	}
	inline void Modify(int l,int r,int v)
	{
		Add(l,v), Add(r+1,-v);
	}
	inline LL Query2(int x)
	{
		LL res1=0,res2=0;
		for(int p=x; p; p^=lb(p)) res1+=t1[p],res2+=t2[p];
		return res1*(x+1)-res2;
	}
	inline LL Query(int l,int r)
	{
		return Query2(r)-Query2(l-1);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	static LL Ans[N];

//	freopen("sf.in","r",stdin);
//	freopen("sf.out","w",stdout);

	const int n=read(),Q=read(),P1=read(),P2=read(),Q2=Q<<1;
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1,l,r,t=0; i<=Q; ++i)
		l=read(), r=read(), Ans[i]+=(r-l)*P1, q[++t]=(Quries){l,r,l-1,i,-1}, q[++t]=(Quries){l,r,r,i,1};
	std::sort(q+1,q+1+Q2);

	int top=0; A[sk[0]=0]=INF;
	for(int i=1; i<=n; ++i)
	{
		while(A[sk[top]]<=A[i]) R[sk[top--]]=i;
		L[i]=sk[top], sk[++top]=i;
	}
	while(top) R[sk[top--]]=n+1;

	int tot=0;
	for(int i=1; i<=n; ++i)
	{
		int l=L[i],r=R[i];
		if(l&&r<=n) opt[++tot]=(Opt){l,l,r,P1};
		if(l&&i+1<r) opt[++tot]=(Opt){i+1,r-1,l,P2};//有左端点才会有这个贡献 
		if(l+1<i&&r<=n) opt[++tot]=(Opt){l+1,i-1,r,P2};
	}
	std::sort(opt+1,opt+1+tot);

	T.n=n, opt[tot+1].p=N, q[Q2+1].p=N;
	int nq=1,no=1;
	while(!q[nq].p) ++nq;//!
	for(int i=1; i<=n&&nq<=Q2; ++i)
	{
		while(opt[no].p==i) T.Modify(opt[no].l,opt[no].r,opt[no].val), ++no;
		while(q[nq].p==i) Ans[q[nq].id]+=q[nq].val*T.Query(q[nq].l,q[nq].r), ++nq;
	}
	for(int i=1; i<=Q; printf("%lld\n",Ans[i++]));

	return 0;
}
