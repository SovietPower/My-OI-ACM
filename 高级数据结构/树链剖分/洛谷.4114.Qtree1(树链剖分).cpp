//边权赋到点上 树剖模板 
//注意LCA、链的顶端不能统计到答案! 
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
const int N=1e5+5;

int n,m,cnt,ep[N],W[N],id[N],sz[N],dep[N],son[N],fa[N],top[N],Enum,H[N],to[N<<1],nxt[N<<1],val[N<<1];
struct Seg_Tree
{
	int A[N],mx[N<<2];
	inline void PushUp(int rt) {mx[rt]=std::max(mx[rt<<1],mx[rt<<1|1]);}
	void Build(int l,int r,int rt)
	{
		if(l==r) mx[rt]=A[l];
		else
		{
			int m=l+r>>1;
			Build(lson), Build(rson);
			PushUp(rt);
		}
	}
	void Modify(int l,int r,int rt,int p,int v)
	{
		if(l==r) mx[rt]=v;
		else
		{
			int m=l+r>>1;
			if(p<=m) Modify(lson,p,v);
			else Modify(rson,p,v);
			PushUp(rt);
		}
	}
	int Query_Max(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return mx[rt];
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return std::max(Query_Max(lson,L,R),Query_Max(rson,L,R));
			else return Query_Max(lson,L,R);
		return Query_Max(rson,L,R);
	}
}t;
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], val[Enum]=w, H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], val[Enum]=w, H[v]=Enum;
}
void DFS1(int x)
{
	int mx=0; sz[x]=1;
	for(int v,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=fa[x])
		{
			fa[v]=x, dep[v]=dep[x]+1, DFS1(v), sz[x]+=sz[v];
			W[v]=val[i], ep[i>>1]=v;
			if(mx<sz[v]) mx=sz[v], son[x]=v;
		}
}
void DFS2(int x,int tp)
{
	id[x]=++cnt, t.A[cnt]=W[x], top[x]=tp;
	if(son[x])
	{
		DFS2(son[x],tp);
		for(int i=H[x]; i; i=nxt[i])
			if(to[i]!=fa[x] && to[i]!=son[x])
				DFS2(to[i],to[i]);
	}
}
int Query_Chain(int x,int y)
{
	int res=0;
	while(top[x]!=top[y])//while(top[x]^top[y])
	{
		if(dep[top[x]]<dep[top[y]]) std::swap(x,y);
		res=std::max(res,t.Query_Max(1,n,1,id[top[x]],id[x])), x=fa[top[x]];
	}
	if(x==y) return res;//LCA不统计入答案！
	if(dep[x]>dep[y]) std::swap(x,y);
	return std::max(res,t.Query_Max(1,n,1,id[son[x]]/*not id[x]!*/,id[y]));
}

int main()
{
	Enum=1;
	n=read();
	for(int u,v,w,i=1; i<n; ++i)
		u=read(),v=read(),w=read(),AddEdge(u,v,w);
	DFS1(1), DFS2(1,1);
	t.Build(1,n,1);
	char opt[7]; int x,y;
	while(scanf("%s",opt),opt[0]!='D')
	{
		x=read(),y=read();
		if(opt[0]=='C') t.Modify(1,n,1,id[ep[x]],y);
		else printf("%d\n",Query_Chain(x,y));;
	}
	return 0;
}
