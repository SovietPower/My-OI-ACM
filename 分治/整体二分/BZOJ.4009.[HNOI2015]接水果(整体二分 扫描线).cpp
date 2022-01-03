/*
15268kb	1128ms
$Description$
给定一棵树和一个路径集合（每条路径有一个权值）。$Q$次询问，每次询问给定一条路径，求路径集合中完全被这条路径包含的路径中，权值第$k$大的是多少。
$n,m,Q\leq40000$。
$Solution$
首先考虑一条路径$(a,b)$完全包含路径$(u,v)$，需要满足什么条件。
记$L[x]$为$x\ DFS$序的编号，$R[x]=L[x]+size[x]-1$为$x$子树$DFS$序编号的最后一个。
若$LCA(u,v)\neq u$，那么$L[u]\leq L[a]\leq R[u],\ L[v]\leq L[b]\leq R[v]$。也即点$(L[a],L[b])$在矩形$[L[u]\sim R[u],\ L[v]\sim R[v]]$中。
若$LCA(u,v)=u$，记$w$为$u\to v$路径上的第二个点（$u$在$v$子树方向上的儿子），则$a$在$w$子树外，$b$在$v$子树内，即$L[a]$在区间$[1,L[w]-1]\bigcup[R[w]+1,n]$中，$L[b]$在$[L[v],R[v]]$中。
那么每个盘子就是一个矩形，每个水果是一个点，我们要对每个点求，包含它的矩形中第$k$大的是多少。
整体二分+扫描线。

具体：先把矩形拆成扫描线，再对扫描线按权值排序。每次加入权值$\leq mid$的扫描线，同时处理每个询问。
若对于一个询问，包含它的矩形个数$\geq k$，则它的答案$\leq mid$；否则$k$减掉对应个数，它的答案$\gt mid$。

细节：判$LCA(u,v)$是否$u$可以直接判$v$在$u$的子树里。
要让修改和询问的$x$都小于等于$y$。
最好对权值离散化一下下。
树状数组是区间修改单点查询。。差分一下。

变量名写的有点恶心=-=
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=40005,M=N<<2;

int Enum,H[N],nxt[N<<1],to[N<<1],val[N],L[N],R[N],Ans[N],fa[N],dep[N],sz[N],son[N],top[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Quries
{
	int x,y,k,id;
	bool operator <(const Quries &a)const
	{
		return x<a.x;
	}
}q[N],tmpq1[N],tmpq2[N];
struct OPT
{
	int p,l,r,v;
	bool operator <(const OPT &a)const
	{
		return p<a.p;
	}
}opt[N<<2],tmpo1[M],tmpo2[M];
struct BIT
{
	int n,t[N];
	#define lb(x) (x&-x)
	inline void Modify(int l,int r,int v)
	{
		for(int p=l; p<=n; p+=lb(p)) t[p]+=v;
		for(int p=r+1; p<=n; p+=lb(p)) t[p]-=v;
	}
	inline int Query(int p)
	{
		int res=0;
		for(; p; p^=lb(p)) res+=t[p];
		return res;
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
inline int Jump(int u,int v)
{
	int las=v;
	while(top[u]!=top[v]) v=fa[las=top[v]];
	return u==v?las:son[u];
}
void DFS1(int x)
{
	int mx=0; sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa[x]) fa[v]=x, dep[v]=dep[x]+1, DFS1(v), sz[x]+=sz[v], sz[v]>mx&&(mx=sz[v],son[x]=v);
}
void DFS2(int x,int tp)
{
	static int Index=0;
	top[x]=tp, L[x]=++Index;
	if(son[x])
	{
		DFS2(son[x],tp);
		for(int i=H[x],v; i; i=nxt[i])
			if((v=to[i])!=fa[x]&&v!=son[x]) DFS2(v,v);
	}
	R[x]=Index;
}
void Solve(int l,int r,int ho,int to,int hq,int tq)
{
	if(l==r||ho>to||hq>tq)
	{
		for(int i=hq,v=val[l]; i<=tq; ++i) Ans[q[i].id]=v;
		return;
	}
	int m=l+r>>1,v=val[m],now=ho,to1=0,to2=0,tq1=0,tq2=0;
	for(int i=hq; i<=tq; ++i)
	{
		while(now<=to && opt[now].p<=q[i].x)
			if(std::abs(opt[now].v)<=v) T.Modify(opt[now].l,opt[now].r,opt[now].v>0?1:-1), tmpo1[to1++]=opt[now++];
			else tmpo2[to2++]=opt[now++];
		int t=T.Query(q[i].y);
		if(q[i].k>t) q[i].k-=t, tmpq2[tq2++]=q[i];
		else tmpq1[tq1++]=q[i];
	}
	while(now<=to)
		if(std::abs(opt[now].v)<=v) T.Modify(opt[now].l,opt[now].r,opt[now].v>0?1:-1), tmpo1[to1++]=opt[now++];
		else tmpo2[to2++]=opt[now++];
	for(int i=ho,p=0; p<to1; opt[i++]=tmpo1[p++]);
	for(int i=ho+to1,p=0; p<to2; opt[i++]=tmpo2[p++]);
	for(int i=hq,p=0; p<tq1; q[i++]=tmpq1[p++]);
	for(int i=hq+tq1,p=0; p<tq2; q[i++]=tmpq2[p++]);
	Solve(l,m,ho,ho+to1-1,hq,hq+tq1-1), Solve(m+1,r,ho+to1,to,hq+tq1,tq);
}

int main()
{
	int n=read(),m=read(),Q=read();
	for(int i=1; i<n; ++i) AE(read(),read());
	DFS1(1), DFS2(1,1);
	int tot=0;
	for(int i=1; i<=m; ++i)
	{
		int u=read(),v=read(); val[i]=read();
		if(L[u]>L[v]) std::swap(u,v);
		if(L[v]<L[u]||L[v]>R[u])
		{
			opt[++tot]=(OPT){L[u],L[v],R[v],val[i]};
			if(R[u]<n) opt[++tot]=(OPT){R[u]+1,L[v],R[v],-val[i]};
		}
		else
		{
			int w=Jump(u,v);
			//if(L[w]>1) 这个显然不用判啊=-= （但是下面那个要判啊 
			opt[++tot]=(OPT){1,L[v],R[v],val[i]}, opt[++tot]=(OPT){L[w],L[v],R[v],-val[i]};
			if(R[w]<n) opt[++tot]=(OPT){L[v],R[w]+1,n,val[i]}, opt[++tot]=(OPT){R[v]+1,R[w]+1,n,-val[i]};//加上可能的p=n+1的操作好惹，以便清空树状数组。
		}
	}
	for(int i=1,u,v; i<=Q; ++i)
		u=read(),v=read(),q[i]=(Quries){std::min(L[u],L[v]),std::max(L[u],L[v]),read(),i};
	std::sort(opt+1,opt+1+tot), std::sort(q+1,q+1+Q), std::sort(val+1,val+1+m);
	int cnt=1;
	for(int i=2; i<=m; ++i) if(val[i]!=val[i-1]) val[++cnt]=val[i];
	T.n=n, Solve(1,cnt,1,tot,1,Q);
	for(int i=1; i<=Q; printf("%d\n",Ans[i++]));

	return 0;
}
