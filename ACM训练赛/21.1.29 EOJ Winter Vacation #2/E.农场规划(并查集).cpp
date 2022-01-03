/*
首先考虑所有 两端点编号都$\le K$的边（点$1\sim K$的生成子图），它们无论如何最终是构成一棵树。
如果在剩余的（有一点编号$>K$的）一条边中，使$u,v$($u,v\le K$)连通，那么直接断掉树上$u,v$路径上的一条边，显然不会比断掉$K+1\sim n$中使$u,v$连通的路径更差（后者可能需要断掉很多边）。
扩展一下，树部分应该是考虑有一点编号$\le K$的所有边，这些边要求一棵树。然后剩下$n-K$个点的生成子图的边是任意加的，所以先把它们合并，再对前者合并，如果前者出现环，就需要断掉树上的一条边。用并查集即可。
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb push_back
typedef long long LL;
const int N=1e6+5;

int fa[N];
struct Edge
{
	int u,v;
}e[N<<1];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
int Find(int x)
{
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}

int main()
{
	int n=read(),m=read(),K=read();
	for(int i=1; i<=n; ++i) fa[i]=i;
	int ans=0;
	for(int i=1; i<=m; ++i) e[i]=(Edge){read(),read()};
	for(int i=1; i<=m; ++i)
		if(e[i].u>K && e[i].v>K) fa[Find(e[i].u)]=Find(e[i].v);
	for(int i=1; i<=m; ++i)
		if(e[i].u<=K||e[i].v<=K)
		{
			int u=Find(e[i].u),v=Find(e[i].v);
			if(u==v) ++ans;
			else fa[v]=u;
		}
	printf("%d\n",ans);

	return 0;
}
