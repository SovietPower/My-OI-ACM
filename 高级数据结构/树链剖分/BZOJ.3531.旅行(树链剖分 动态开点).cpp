/*
首先树剖可以维护树上的链Sum、Max 
可以对每个宗教建一棵线段树，那这题就很好做了 
不过10^5需要动态开点 (不明白为什么nlogn不需要回收就可以 不是每个Insert加log个节点?) 
操作修改完更改原数列！盲人一个。。 
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
#define gc() getchar()
#define now node[rt]
#define lson node[rt].ls
#define rson node[rt].rs
const int N=1e5+5,MAXN=N*19;

int n,q,cnt,H[N],Enum,to[N<<1],nxt[N<<1],fa[N],dep[N],id[N],son[N],sz[N],top[N];
int idx,pos[N],W[N],rel[N],root[N],pool[MAXN];
struct Seg_Tree
{
	struct Node
	{
		int sum,maxn,ls,rs,l,r;
		inline void Init() {sum=maxn=l=r=ls=rs=0;}
	}node[MAXN];
	inline int new_Node() {return pool[++idx];}
	inline void del_Node(int rt) {now.Init(), pool[idx--]=rt;}
	inline void PushUp(int rt)
	{
		now.sum = node[lson].sum + node[rson].sum,
		now.maxn= std::max(node[lson].maxn, node[rson].maxn);
	}
	void Insert(int l,int r,int &rt,int x)
	{
		if(!rt) rt=new_Node(), now.l=l, now.r=r;
		if(l==r) now.sum=now.maxn=W[x];
		else
		{
			int m=l+r>>1;
			if(id[x]<=m) /*lson?0:lson=new_Node(),*/ Insert(l,m,lson,x);//不想打括号-- 
			else /*rson?0:rson=new_Node(),*/ Insert(m+1,r,rson,x);
			PushUp(rt);
		}
	}
	void Delete(int rt,int x,int &son)//可以用Insert将其值变为0来删除 但是就不能重复利用了 
	{
		if(now.l==now.r) son=0, del_Node(rt);//父亲的这个儿子也要删!
		else
		{
			int m=now.l+now.r>>1;
			if(id[x]<=m) Delete(lson,x,lson);
			else Delete(rson,x,rson);
			if(now.sum==W[x]) del_Node(rt), son=0;
			else PushUp(rt);
		}
	}
	void Modify(int rt,int p,int v)
	{
		if(now.l==now.r) now.maxn=now.sum=v;
		else
		{
			int m=now.l+now.r>>1;
			if(p<=m) Modify(lson,p,v);
			else Modify(rson,p,v);
			PushUp(rt);
		}
	}
	int Query_Max(int rt,int L,int R)
	{
		if(!rt) return 0;
		if(L<=now.l && now.r<=R) return now.maxn;
		int m=now.l+now.r>>1;
		if(L<=m)
			if(m<R) return std::max(Query_Max(lson,L,R),Query_Max(rson,L,R));
			else return Query_Max(lson,L,R);
		return Query_Max(rson,L,R);
	}
	int Query_Sum(int rt,int L,int R)
	{
		if(!rt) return 0;
		if(L<=now.l && now.r<=R) return now.sum;
		int m=now.l+now.r>>1;
		if(L<=m)
			if(m<R) return Query_Sum(lson,L,R)+Query_Sum(rson,L,R);
			else return Query_Sum(lson,L,R);
		return Query_Sum(rson,L,R);
	}
}t;
#undef now
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS1(int x)
{
	sz[x]=1; int mx=0;
	for(int v,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=fa[x])
		{
			fa[v]=x, dep[v]=dep[x]+1, DFS1(v), sz[x]+=sz[v];
			if(mx<sz[v]) mx=sz[v], son[x]=v;
		}
}
void DFS2(int x,int tp)
{
	id[x]=++cnt, top[x]=tp;
	if(son[x])
	{
		DFS2(son[x],tp);
		for(int i=H[x]; i; i=nxt[i])
			if(to[i]!=fa[x] && to[i]!=son[x])
				DFS2(to[i], to[i]);
	}
}
void Query_Chain_Sum(int x,int y)
{
	long long res=0;int rt=root[rel[x]];
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) std::swap(x,y);
		res += t.Query_Sum(rt,id[top[x]],id[x]);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) std::swap(x,y);
	res += t.Query_Sum(rt,id[x],id[y]);
	printf("%lld\n",res);
}
void Query_Chain_Max(int x,int y)
{
	int res=0, rt=root[rel[x]];
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) std::swap(x,y);
		res = std::max(res, t.Query_Max(rt,id[top[x]],id[x]));
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) std::swap(x,y);
	res = std::max(res, t.Query_Max(rt,id[x],id[y]));
	printf("%d\n",res);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("3531.in","r",stdin);
	freopen("my.out","w",stdout);
#endif

	n=read(),q=read();
	for(int i=1; i<MAXN; ++i) pool[i]=i;
	for(int i=1; i<=n; ++i) W[i]=read(), rel[i]=read();
	for(int u,v,i=1; i<n; ++i) u=read(),v=read(),AddEdge(u,v);
	DFS1(1), DFS2(1,1);
	for(int i=1; i<=n; ++i) t.Insert(1,n,root[rel[i]],i); 
	char opt[5]; int x,y;
	while(q--)
	{
		scanf("%s",opt), x=read(), y=read();
		switch(opt[1])
		{
			case 'C': t.Delete(root[rel[x]],x,root[rel[x]]), rel[x]=y, t.Insert(1,n,root[y],x);
					  break;
			case 'W': t.Modify(root[rel[x]],id[x],y), W[x]=y;//!
					  break;
			case 'S': Query_Chain_Sum(x,y);
					  break;
			case 'M': Query_Chain_Max(x,y);
					  break;
		}
	}
	return 0;
}
