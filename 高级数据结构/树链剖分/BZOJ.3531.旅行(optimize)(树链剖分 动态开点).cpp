//不知道为什么只需nlogn个节点 不需要回收 
//+各种函数简化 
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
		int sum,maxn,ls,rs;
		inline void Init() {sum=maxn=ls=rs=0;}
	}node[MAXN];
	inline int new_Node() {return ++idx;}
//	inline int new_Node() {return pool[++idx];}
//	inline void del_Node(int rt) {now.Init(), pool[idx--]=rt;}
	inline void PushUp(int rt)
	{
		now.sum = node[lson].sum + node[rson].sum,
		now.maxn= std::max(node[lson].maxn, node[rson].maxn);
	}
	void Update(int l,int r,int &rt,int p,int v)
	{
		if(!rt) rt=new_Node();
		if(l==r) now.sum=now.maxn=v;
		else
		{
			int m=l+r>>1;
			if(p<=m) Update(l,m,lson,p,v);
			else Update(m+1,r,rson,p,v);
			PushUp(rt);
		}
	}
	int Query(int l,int r,int rt,int L,int R,bool opt)
	{
		if(!rt) return 0;
		if(L<=l && r<=R) return opt?now.sum:now.maxn;
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return opt?Query(l,m,lson,L,R,opt)+Query(m+1,r,rson,L,R,opt)
							  :std::max(Query(l,m,lson,L,R,opt),Query(m+1,r,rson,L,R,opt));
			else return Query(l,m,lson,L,R,opt);
		return Query(m+1,r,rson,L,R,opt);
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
	sz[x]=1; int mx=-1;
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
void Query_Chain(int x,int y,bool opt)
{
	int res=0;int rt=root[rel[x]];
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) std::swap(x,y);
		if(opt) res += t.Query(1,n,rt,id[top[x]],id[x],1);
		else res = std::max(res, t.Query(1,n,rt,id[top[x]],id[x],0));
		x=fa[top[x]];
	}
	if(id[x]>id[y]) std::swap(x,y);
	if(opt) res += t.Query(1,n,rt,id[x],id[y],1);
	else res = std::max(res, t.Query(1,n,rt,id[x],id[y],0));
	printf("%d\n",res);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("35312.in","r",stdin);
	freopen("my.out","w",stdout);
#endif

	n=read(),q=read();
	for(int i=1; i<MAXN; ++i) pool[i]=i;
	for(int i=1; i<=n; ++i) W[i]=read(), rel[i]=read();
	for(int u,v,i=1; i<n; ++i) u=read(),v=read(),AddEdge(u,v);
	DFS1(1), DFS2(1,1);
	for(int i=1; i<=n; ++i) t.Update(1,n,root[rel[i]],id[i],W[i]); 
	char opt[5]; int x,y;
	while(q--)
	{
		scanf("%s",opt), x=read(), y=read();
		switch(opt[1])
		{
			case 'C': t.Update(1,n,root[rel[x]],id[x],0), rel[x]=y, t.Update(1,n,root[y],id[x],W[x]);
					  break;
			case 'W': t.Update(1,n,root[rel[x]],id[x],y),W[x]=y; break;
			case 'S': Query_Chain(x,y,1); break;
			case 'M': Query_Chain(x,y,0); break;
		}
	}
	return 0;
}
