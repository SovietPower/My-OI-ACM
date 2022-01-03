/*
序列上的主席树 某点是利用前一个点的根建树 
同理 树上的主席树 某个节点可以利用其父节点(is unique)的根建树 
排名可以利用树上前缀和求得: 对于(u,v),w=LCA(u,v)，u->v这条链的值就是 sum[u->root]+sum[v->root]-sum[w->root]-sum[fa[w]->root](减一个w)  
这样like序列上的主席树 用两棵树进行差分，树上的用四棵树即可 
每个节点是一棵权值线段树 和给的树是独立的 没什么关系 别想错 
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+5,MAXIN=2e5;

int n,m,cnt,W[N],A[N],ref[N],fa[N],Enum,H[N],to[N<<1],nxt[N<<1],root[N];
char IN[MAXIN],*SS=IN,*TT=IN;
namespace Subdivision//for LCA
{
	int dep[N],sz[N],son[N],top[N];
	void DFS1(int x)
	{
		sz[x]=1; int mx=0;
		for(int v,i=H[x]; i; i=nxt[i])
			if((v=to[i])!=fa[x])
			{
				dep[v]=dep[x]+1, DFS1(v), sz[x]+=sz[v];
				if(mx<sz[v]) mx=sz[v],son[x]=v;
			}
	}
	void DFS2(int x,int tp)
	{
		top[x]=tp;
		if(son[x])
		{
			DFS2(son[x],tp);
			for(int i=H[x]; i; i=nxt[i])
				if(to[i]!=fa[x] && to[i]!=son[x])
					DFS2(to[i],to[i]);
		}
	}
	int LCA(int u,int v)
	{
		while(top[u]!=top[v])
		{
			if(dep[top[u]]<dep[top[v]]) std::swap(u,v);
			u=fa[top[u]];
		}
		return dep[u]>dep[v] ? v : u;
	}
}
struct Seg_Tree
{
	int tot,sum[N*18],son[N*18][2];
	void Insert(int x,int &y,int l,int r,int p/*,int v*/)
	{
		sum[y=++tot]=sum[x]+1;
		if(l<r)
		{
			int m=l+r>>1;
			if(p<=m) son[y][1]=son[x][1],Insert(son[x][0],son[y][0],l,m,p);
			else son[y][0]=son[x][0],Insert(son[x][1],son[y][1],m+1,r,p);
		}
	}
	int Query(int faLca,int Lca,int x,int y,int l,int r,int k)
	{
		if(l==r) return l;
		int m=l+r>>1, tmp=sum[son[x][0]]+sum[son[y][0]]-sum[son[Lca][0]]-sum[son[faLca][0]];
		if(tmp>=k) return Query(son[faLca][0],son[Lca][0],son[x][0],son[y][0],l,m,k);
		else return Query(son[faLca][1],son[Lca][1],son[x][1],son[y][1],m+1,r,k-tmp);
	}
}t;
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
void DFS(int x,int f)
{
	t.Insert(root[f],root[x],1,cnt,A[x]/*,1*/);
	fa[x]=f;
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=fa[x]) DFS(to[i],x);
}
inline int Find(int x)
{
	int l=1,r=cnt,m;
	while(l<r)
	{
		if(ref[m=l+r>>1]<x) l=m+1;
		else r=m;
	}
	return l;
}
void Discrete()
{
	std::sort(ref+1,ref+1+n);
	cnt=1;
	for(int i=2; i<=n; ++i)
		if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	for(int p,i=1; i<=n; ++i)
		W[p=Find(A[i])]=A[i], A[i]=p;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("2588.in","r",stdin);
#endif

	n=read(),m=read()-1;
	for(int i=1; i<=n; ++i) ref[i]=A[i]=read();
	for(int u,v,i=1; i<n; ++i) u=read(),v=read(),AddEdge(u,v);
	Discrete(), DFS(1,0);
	Subdivision::DFS1(1), Subdivision::DFS2(1,1);
	int ans=0,u,v,k,w;
	while(m--)
	{
		u=ans^(read()),v=read(),k=read(),w=Subdivision::LCA(u,v);
		printf("%d\n",ans=W[t.Query(root[fa[w]],root[w],root[u],root[v],1,cnt,k)]);
	}
	u=ans^(read()),v=read(),k=read(),w=Subdivision::LCA(u,v);
	printf("%d",W[t.Query(root[fa[w]],root[w],root[u],root[v],1,cnt,k)]);

	return 0;
}
