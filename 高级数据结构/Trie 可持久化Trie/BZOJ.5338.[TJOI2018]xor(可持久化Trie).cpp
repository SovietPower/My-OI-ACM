/*
83472kb	3316ms
询问一就用以DFS序为前缀得到的可持久化Trie做，询问二很经典的树上差分。
注意求询问二路径的时候，为了方便就先算一下LCA的答案。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define BIT 29
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int Enum,H[N],nxt[N<<1],to[N<<1],A[N],root1[N],root2[N],dfn[N],R[N],sz[N],dep[N],fa[N],son[N],top[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Trie
{
	#define S N*(BIT+2)//+2!
	int tot,sz[S],son[S][2];
	void Insert(int x,int y,int v)
	{
		for(int i=BIT; ~i; --i)
		{
			int c=v>>i&1;
			son[x][c]=++tot, son[x][c^1]=son[y][c^1];
			x=tot, y=son[y][c], sz[x]=sz[y]+1;
		}
	}
	int Query1(int x,int y,int v)
	{
		int res=0;
		for(int i=BIT; ~i; --i)
		{
			int c=(v>>i&1)^1;
			if(sz[son[x][c]]-sz[son[y][c]]>0) res|=1<<i;
			else c^=1;
			x=son[x][c], y=son[y][c];
		}
		return res;
	}
	int Query2(int x,int y,int z,int v)
	{
		int res=0,tmp=A[z]^v; z=root2[z];
		for(int i=BIT; ~i; --i)
		{
			int c=(v>>i&1)^1;
			if(sz[son[x][c]]+sz[son[y][c]]-2*sz[son[z][c]]>0) res|=1<<i;
			else c^=1;
			x=son[x][c], y=son[y][c], z=son[z][c];
		}
		return std::max(res,tmp);
	}
}T1,T2;

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
inline int LCA(int u,int v)
{
	while(top[u]!=top[v]) dep[top[u]]>dep[top[v]]?u=fa[top[u]]:v=fa[top[v]];
	return dep[u]>dep[v]?v:u;
}
void DFS1(int x)
{
	int mx=0; sz[x]=1, T2.Insert(root2[x]=++T2.tot,root2[fa[x]],A[x]);
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa[x])
			fa[v]=x, dep[v]=dep[x]+1, DFS1(v), sz[x]+=sz[v], sz[v]>mx&&(mx=sz[v],son[x]=v);
}
void DFS2(int x,int tp)
{
	static int Index=0;
	top[x]=tp, dfn[x]=++Index, T1.Insert(root1[Index]=++T1.tot,root1[Index-1],A[x]);
	if(son[x])
	{
		DFS2(son[x],tp);
		for(int i=H[x],v; i; i=nxt[i])
			if((v=to[i])!=fa[x]&&v!=son[x]) DFS2(v,v);
	}
	R[x]=Index;
}

int main()
{
	const int n=read(),Q=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<n; ++i) AE(read(),read());
	DFS1(1), DFS2(1,1);
	for(int i=1,x,y; i<=Q; ++i)
		switch(read())
		{
			case 1: x=read(),printf("%d\n",T1.Query1(root1[R[x]],root1[dfn[x]-1],read())); break;
			case 2: x=read(),y=read(),printf("%d\n",T2.Query2(root2[x],root2[y],LCA(x,y),read())); break;
		}

	return 0;
}
