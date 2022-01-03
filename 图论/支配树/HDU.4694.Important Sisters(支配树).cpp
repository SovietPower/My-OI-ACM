/*
1107MS	8292K
https://www.cnblogs.com/SovietPower/p/10123414.html
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=50005,M=1e5+5;

int Index,dfn[N],ref[N],F[N],fa[N],mn[N],semi[N],idom[N],Ans[N];
struct Graph
{
	int Enum,H[N],nxt[M],to[M];
	inline void Clear(int n)
	{
		Enum=0, memset(H,0,n+1<<2);
	}
	inline void AE(int u,int v)
	{
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	}
}G,RG,SG,T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void DFS0(int x)
{
	ref[dfn[x]=++Index]=x;
	for(int i=G.H[x],v; i; i=G.nxt[i])
		if(!dfn[v=G.to[i]]) fa[v]=x, DFS0(v);
}
int Find(int x)
{
	if(x==F[x]) return x;
	int tmp=F[x];
	F[x]=Find(F[x]);
	if(dfn[semi[mn[tmp]]]<dfn[semi[mn[x]]]) mn[x]=mn[tmp];
	return F[x];
}
void DFS(int x,int s)
{
	Ans[x]=s+=x;
	for(int i=T.H[x]; i; i=T.nxt[i]) DFS(T.to[i],s);
}
void Solve(int n)
{
	for(int k=n; k>1; --k)
	{
		int x=ref[k],t=n;//求半支配点 
		for(int i=RG.H[x],v; i; i=RG.nxt[i])
			if(dfn[v=RG.to[i]])
				if(dfn[v]<dfn[x]) t=std::min(t,dfn[v]);
				else Find(v), t=std::min(t,dfn[semi[mn[v]]]);
		F[x]=fa[x], SG.AE(semi[x]=ref[t],x);

		x=ref[k-1];//从半支配点到支配点 
		for(int i=SG.H[x],v; i; i=SG.nxt[i])
		{
			Find(v=SG.to[i]);
			if(semi[v]==semi[mn[v]]) idom[v]=semi[v];
			else idom[v]=mn[v];//idom[mn[v]]此时可能并未找到 
		}
	}
	for(int k=2,x; k<=n; ++k)
	{
		x=ref[k];
		if(idom[x]!=semi[x]) idom[x]=idom[idom[x]];
		T.AE(idom[x],x);
	}
	DFS(n,0);
	for(int i=1; i<n; printf("%d ",Ans[i++]));
	printf("%d\n",Ans[n]), memset(Ans,0,n+1<<2);
}

int main()
{
	int n,m;
	while(~scanf("%d%d",&n,&m))
	{
		for(int i=1,u,v; i<=m; ++i) u=read(),v=read(),G.AE(u,v),RG.AE(v,u);
		for(int i=1; i<=n; ++i) F[i]=semi[i]=mn[i]=i;
		Index=0, DFS0(n), Solve(n);
		G.Clear(n), RG.Clear(n), SG.Clear(n), T.Clear(n);
		memset(dfn,0,n+1<<2), memset(idom,0,n+1<<2), memset(ref,0,n+1<<2);//, memset(fa,0,n+1<<2);//不都清空会RE啊== 
	}
	return 0;
}
