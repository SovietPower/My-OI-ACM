/*
3876kb	148ms(哇Rank6！)
题意：q次询问仙人掌上两点的最短路。
圆方树。不写了。。
就是当LCA是方点时跳进那个环可以分类讨论一下用树剖而不必须用倍增：
如果v是u的(唯一的那个)重儿子，那么u的DFS序上+1的点即是要找的；否则v会引出一条新的链。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 50000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=10005<<1,M=N<<2;//点数！(方点)

int n,m,Q,tot,Index,dfn[N],low[N],fa[N],dis[N],cdis[N],sz[N],son[N],dep[N],top[N],ref[N],cnt;
char IN[MAXIN],*SS=IN,*TT=IN;
struct Edge
{
	int Enum,H[N],nxt[M],to[M],val[M];
	inline void AddEdge(int u,int v,int w){
		to[++Enum]=v, nxt[Enum]=H[u], val[Enum]=w, H[u]=Enum;
		to[++Enum]=u, nxt[Enum]=H[v], val[Enum]=w, H[v]=Enum;
	}
}g,t;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Build(int u,int v,int d)//v->...->u->v
{
	for(int i=v; i!=u; i=fa[i]) cdis[i]=d, d+=dis[i];//直接用个dis[]记来时边的权值 
	cdis[++tot]=d/*length of circle*/, t.AddEdge(tot,u,0);
	for(int i=v; i!=u/*fa[u]*/; i=fa[i]) t.AddEdge(tot,i,std::min(cdis[i],d-cdis[i]));
}
void Tarjan(int x)
{
	dfn[x]=low[x]=++Index;
	for(int v,i=g.H[x]; i; i=g.nxt[i])
		if(g.to[i]!=fa[x])
		{
			if(!dfn[v=g.to[i]])
				fa[v]=x, dis[v]=g.val[i], Tarjan(v), low[x]=std::min(low[x],low[v]);
			else low[x]=std::min(low[x],dfn[v]);
			if(low[v]>dfn[x]) t.AddEdge(x,v,g.val[i]);//Round point
		}
	for(int v,i=g.H[x]; i; i=g.nxt[i])
		if(fa[v=g.to[i]]!=x && dfn[v]>dfn[x]) Build(x,v,g.val[i]);//Square point
}
void DFS1(int x)
{
	int mx=0; sz[x]=1;
	for(int v,i=t.H[x]; i; i=t.nxt[i])
		if((v=t.to[i])!=fa[x])
		{
			dep[v]=dep[x]+1, dis[v]=dis[x]+t.val[i], fa[v]=x, DFS1(v), sz[x]+=sz[v];
			if(sz[v]>mx) mx=sz[v], son[x]=v;
		}
}
void DFS2(int x,int tp)
{
	top[x]=tp, ref[dfn[x]=++cnt]=x;
	if(son[x]){
		DFS2(son[x],tp);
		for(int i=t.H[x]; i; i=t.nxt[i])
			if(t.to[i]!=fa[x]&&t.to[i]!=son[x]) DFS2(t.to[i],t.to[i]);
	}
}
int LCA(int u,int v)
{
	while(top[u]!=top[v]) dep[top[u]]>dep[top[v]]?u=fa[top[u]]:v=fa[top[v]];
	return dep[u]<dep[v]?u:v;
}
int Get_p(int u,int lca)
{
	int las=u;
	while(top[u]!=top[lca]) u=fa[las=top[u]];
	return u==lca?las:ref[dfn[lca]+1];
}

int main()
{
	tot=n=read(),m=read(),Q=read();
	for(int u,v,i=1; i<=m; ++i) u=read(),v=read(),g.AddEdge(u,v,read());
	Tarjan(1), dis[1]=fa[1]=0, DFS1(1), DFS2(1,1);
	int u,v,w,p1,p2;
	while(Q--)
	{
		u=read(),v=read(),w=LCA(u,v);
		if(w<=n) printf("%d\n",dis[u]+dis[v]-(dis[w]<<1));//没有负边，圆上顺序。。无所谓了。
		else p1=Get_p(u,w), p2=Get_p(v,w), printf("%d\n",dis[u]-dis[p1]+dis[v]-dis[p2]+std::min(std::abs(cdis[p2]-cdis[p1]),cdis[w]-std::abs(cdis[p2]-cdis[p1])));//这是cdis[p]不是cdis[u/v]！mmpzz错误调了半个多小时 
	}
	return 0;
}
