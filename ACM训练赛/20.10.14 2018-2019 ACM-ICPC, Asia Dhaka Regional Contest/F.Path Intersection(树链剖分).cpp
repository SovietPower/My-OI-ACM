/*
421ms	5700KB
树剖维护全局最大值及其个数即可。
可以剪剪枝以及注意Clear（不过n只有10000，logn很小）。
*/
#include <bits/stdc++.h>
#define gc() getchar()
typedef long long LL;
const int N=2e4+5;

int n,Index,H[N],Enum,nxt[N<<1],to[N<<1],L[N],fa[N],dep[N],son[N],sz[N],top[N];
struct Segment_Tree
{
	#define S N*18
	int mx[S],sum[S],tag[S];
	bool clear[S];
	#undef S
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	inline void Update(int rt)
	{
		mx[rt]=std::max(mx[ls],mx[rs]);
		if(mx[ls]<mx[rs]) sum[rt]=sum[rs];
		else if(mx[ls]>mx[rs]) sum[rt]=sum[ls];
		else sum[rt]=sum[ls]+sum[rs];
	}
	inline void Add(int rt,int v)
	{
		mx[rt]+=v, tag[rt]+=v;
	}
	inline void Clear(int rt,int m)
	{
		mx[rt]=0, tag[rt]=0, sum[rt]=m, clear[rt]=1;
	}
	inline void PushDown(int rt,int m)
	{
		if(clear[rt]) Clear(ls,m-(m>>1)), Clear(rs,m>>1), clear[rt]=0;
		if(tag[rt]) Add(ls,tag[rt]), Add(rs,tag[rt]), tag[rt]=0;
	}
	void Build(int l,int r,int rt)
	{
		tag[rt]=mx[rt]=clear[rt]=0, sum[rt]=r-l+1;
		if(l==r) return;
		int m=l+r>>1;
		Build(lson), Build(rson);
	}
	void Modify(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) {Add(rt,1); return;}
		PushDown(rt,r-l+1);
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R);
		if(m<R) Modify(rson,L,R);
		Update(rt);
	}
	void Clear(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) {Clear(rt,r-l+1); return;}
		PushDown(rt,r-l+1);
		int m=l+r>>1;
		if(L<=m) Clear(lson,L,R);
		if(m<R) Clear(rson,L,R);
		Update(rt);
	}
}T;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS1(int x)
{
	int mx=0; sz[x]=1, son[x]=0;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa[x])
			fa[v]=x, dep[v]=dep[x]+1, DFS1(v), sz[x]+=sz[v], sz[v]>mx&&(mx=sz[v],son[x]=v);
}
void DFS2(int x,int tp)
{
	top[x]=tp, L[x]=++Index;
	if(son[x])
	{
		DFS2(son[x],tp);
		for(int i=H[x],v; i; i=nxt[i])
			if((v=to[i])!=fa[x] && v!=son[x])
				DFS2(v,v);
	}
}
void Modify(int u,int v)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) std::swap(u,v);
		T.Modify(1,n,1,L[top[u]],L[u]), u=fa[top[u]];
	}
	if(dep[u]>dep[v]) std::swap(u,v);
	T.Modify(1,n,1,L[u],L[v]);
}
void Clear(int u,int v)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) std::swap(u,v);
		T.Clear(1,n,1,L[top[u]],L[u]), u=fa[top[u]];
	}
	if(dep[u]>dep[v]) std::swap(u,v);
	T.Clear(1,n,1,L[u],L[v]);
}

int main()
{
	static int qa[100],qb[100];

	for(int TS=read(),Ts=1; Ts<=TS; ++Ts)
	{
		printf("Case %d:\n",Ts);
		int n=read(); ::n=n;
		for(int i=1; i<n; ++i) AE(read(),read());
		fa[1]=0, dep[1]=1, DFS1(1), DFS2(1,1);
		T.Build(1,n,1);

		int Q=read();
		for(int i=1; i<=Q; ++i)
		{
			int k=read(),p=1;
			for(int j=1; j<=k; ++j) qa[j]=read(), qb[j]=read();
			for(p=1; p<=k&&T.mx[1]==p-1; ++p) Modify(qa[p],qb[p]);
			printf("%d\n",T.mx[1]==k?T.sum[1]:0);
			for(int j=1; j<p; ++j) Clear(qa[j],qb[j]);
		}
		Index=Enum=0, memset(H,0,n+2<<2);
	}

	return 0;
}
