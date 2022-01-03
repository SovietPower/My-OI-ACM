/*
28320kb	8608ms
首先想到树剖+李超线段树。发现对于同一条重链上的点，以$dis[i]$作为自变量，它是单增的，所以就可以李超线段树维护了。
对于修改的形式，用$dis[i]$做自变量，拆一些常数出来即可。
查询时用经过的所有节点上的线段更新一次！（区间查询是用限制后的左右端点同时取$\min$）维护了$ans[rt]$又怎样啊。。→_→
另外$ans[rt]$不是$x=mid$时的值，是区间左右端点函数值的最小值！在替换掉当前节点线段时$ans[rt]$也要与自己取$\min$（不一定当前线段左右端点的最小值都更小）！
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;
const LL INF=123456789123456789ll;

int Enum,H[N],nxt[N<<1],to[N<<1],len[N<<1],dep[N],sz[N],fa[N],son[N],top[N],dfn[N],ref[N];
LL dis[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Line
{
	LL k,b,val;
	Line(LL k=0,LL b=INF,LL val=INF):k(k),b(b),val(val) {}
	inline LL f(LL x)
	{
		return k*x+b;
	}
};
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	LL dis[N],ans[S];
	Line mn[S];
	#undef S
	void Init(const int n)
	{
		for(int i=1; i<=n; ++i) dis[i]=::dis[ref[i]];
		for(int i=n<<2; i; --i) ans[i]=INF;
	}
	#define Update(rt) ans[rt]=std::min(ans[rt],std::min(ans[ls],ans[rs]))
	void Modify(int l,int r,int rt,Line v)
	{
		int m=l+r>>1;
		v.val=v.f(dis[m]);
		if(v.val<mn[rt].val) ans[rt]=std::min(ans[rt],std::min(v.f(dis[l]),v.f(dis[r]))), std::swap(v,mn[rt]);
		if(l==r) return;
		if(v.f(dis[l])>=mn[rt].f(dis[l]) && v.f(dis[r])>=mn[rt].f(dis[r])) return;
		if(v.k>mn[rt].k) Modify(lson,v);
		else Modify(rson,v);
		Update(rt);
	}
	void ModifyS(int l,int r,int rt,int L,int R,Line v)
	{
		if(L<=l && r<=R) {Modify(l,r,rt,v); return;}
		int m=l+r>>1;
		if(L<=m) ModifyS(lson,L,R,v);
		if(m<R) ModifyS(rson,L,R,v);
		Update(rt);
	}
	LL Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return ans[rt];
		LL res=std::min(mn[rt].f(dis[std::max(l,L)]),mn[rt].f(dis[std::min(r,R)]));//!!!
		int m=l+r>>1;
		if(L<=m) res=std::min(res,Query(lson,L,R));
		if(m<R) res=std::min(res,Query(rson,L,R));
		return res;
	}
}T;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline void AE(int w,int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, len[Enum]=w;
}
inline int LCA(int u,int v)
{
	while(top[u]!=top[v]) dep[top[u]]>dep[top[v]]?u=fa[top[u]]:v=fa[top[v]];
	return dep[u]>dep[v]?v:u;
}
void DFS1(int x)
{
	int mx=0; sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa[x])
			dep[v]=dep[x]+1, dis[v]=dis[x]+len[i], fa[v]=x, DFS1(v), sz[x]+=sz[v], sz[v]>mx&&(mx=sz[v],son[x]=v);
}
void DFS2(int x,int tp)
{
	static int Index=0;
	ref[dfn[x]=++Index]=x, top[x]=tp;
	if(son[x])
	{
		DFS2(son[x],tp);
		for(int i=H[x],v; i; i=nxt[i])
			if((v=to[i])!=fa[x] && v!=son[x]) DFS2(v,v);
	}
}
#define S 1,n,1
void Modify(const int n,int u,int w,Line v)
{
	while(top[u]!=top[w]) T.ModifyS(S,dfn[top[u]],dfn[u],v), u=fa[top[u]];
	T.ModifyS(S,dfn[w],dfn[u],v);
}
void Query(const int n)
{
	int u=read(),v=read(); LL res=INF;
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) std::swap(u,v);
		res=std::min(res,T.Query(S,dfn[top[u]],dfn[u])), u=fa[top[u]];
	}
	if(dep[u]>dep[v]) std::swap(u,v);
	res=std::min(res,T.Query(S,dfn[u],dfn[v]));
	printf("%lld\n",res);
}

int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);

	const int n=read(),m=read();
	for(int i=1; i<n; ++i) AE(read(),read(),read());
	DFS1(1), DFS2(1,1), T.Init(n);
	for(int i=1; i<=m; ++i)
		switch(read())
		{
			case 1:
			{
				int u=read(),v=read(),w=LCA(u,v); LL a=read(),b=read();
				Modify(n,u,w,Line(-a,b+dis[u]*a,0)), Modify(n,v,w,Line(a,b+a*(dis[u]-(dis[w]<<1)),0)); break;
			}
			case 2: Query(n); break;
		}

	return 0;
}
