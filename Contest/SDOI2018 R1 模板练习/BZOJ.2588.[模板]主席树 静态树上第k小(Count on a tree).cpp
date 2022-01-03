//10^5还是需要18*10^5的空间！
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e5+5;

int n,Q,cnt,ref[N],A[N],H[N],Enum,nxt[N<<1],to[N<<1],root[N],top[N],dep[N],sz[N],son[N],fa[N];

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
namespace T//Seg_Tree
{
	#define lson son[x][0]
	#define rson son[x][1]

	int tot,sum[N*17],son[N*17][2];
	void Insert(int x,int &y,int l,int r,int p)
	{
		sum[y=++tot]=sum[x]+1;
		if(l<r){
			int m=l+r>>1;
			if(p<=m) son[y][1]=rson,Insert(lson,son[y][0],l,m,p);
			else son[y][0]=lson,Insert(rson,son[y][1],m+1,r,p);
		}
	}
	int Query(int x,int y,int lca,int falca,int l,int r,int k)
	{
		if(l==r) return l;
		int delta=sum[lson]+sum[son[y][0]]-sum[son[lca][0]]-sum[son[falca][0]];
		if(delta<k) return Query(rson,son[y][1],son[lca][1],son[falca][1],(l+r>>1)+1,r,k-delta);
		return Query(lson,son[y][0],son[lca][0],son[falca][0],l,l+r>>1,k);
	}
}

int Find(int x)
{
	int l=1,r=cnt,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}
void DFS1(int x)
{
	int mx=0; sz[x]=1;
	T::Insert(root[fa[x]],root[x],1,cnt,A[x]);
	for(int v,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=fa[x])
		{
			fa[v]=x, dep[v]=dep[x]+1, DFS1(v), sz[x]+=sz[v];
			if(sz[v]>mx) mx=sz[v],son[x]=v;
		}
}
void DFS2(int x,int tp)
{
	top[x]=tp;
	if(son[x]){
		DFS2(son[x],tp);
		for(int i=H[x]; i; i=nxt[i])
			if(to[i]!=fa[x] && to[i]!=son[x]) DFS2(to[i],to[i]);
	}
}
int LCA(int u,int v)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) std::swap(u,v);
		u=fa[top[u]];
	}
	return dep[u]>dep[v]?v:u;
}

int main()
{
	n=read(),Q=read();
	for(int i=1; i<=n; ++i) ref[i]=A[i]=read();
	for(int u,v,i=1; i<n; ++i) u=read(),v=read(),AddEdge(u,v);
	std::sort(ref+1,ref+1+n), cnt=1;
	for(int i=2; i<=n; ++i) if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	for(int i=1; i<=n; ++i) A[i]=Find(A[i]);
	DFS1(1), DFS2(1,1);
	int res=0,u,v,w,k;
	while(Q--)
		u=read()^res,v=read(),k=read(),w=LCA(u,v),
		printf("%d\n",res=ref[T::Query(root[u],root[v],root[w],root[fa[w]],1,cnt,k)]);

	return 0;
}
