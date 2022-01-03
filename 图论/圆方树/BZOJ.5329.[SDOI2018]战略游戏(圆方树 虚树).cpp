/*
36624kb	4516ms(第一个Rank1。。激动)
$Description$
给定一张无向图（有重边无自环）。$q$次询问，每次询问给定点集$S$，$|S|\geq 2$，你要删掉一个点以及所有与其相连的边，使得$S$中存在两个点不连通。求有多少种删点方案。
$n\leq 10^5,\ m\leq 2\times 10^5,\ q\leq 10^5$，$10$组数据。
$Solution$
显然先建圆方树，方点权值为0圆点权值为1，两点间的答案就是路径权值和减去起点终点。
对于询问，显然可以建虚树。但是只需要计算两关键点间路径权值，所以不需要建出虚树。统计DFS序相邻的两关键点间路径权值，最后除以2就好了。
因为这个前缀和统计不到根节点，所以要加上当前虚树的根节点的权值，即(LCA(A1,AK)<=n)。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 200000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=(2e5+5)*2;

int n,m,tot,K,A[N],Index,dfn[N],low[N],sk[N],top,sum[N],tp[N],dep[N],son[N],fa[N],sz[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Graph
{
	int Enum,H[N],nxt[N],to[N];

	void Init(){
		Enum=0, memset(H,0,sizeof H);
	}
	inline void Add_direct(int u,int v){
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	}
	inline void AddEdge(int u,int v){
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
	}
}G,T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline bool cmp_dfn(const int &a,const int &b){
	return dfn[a]<dfn[b];
}
void Tarjan(int x)
{
	low[x]=dfn[x]=++Index, sk[++top]=x;
	for(int v,i=G.H[x]; i; i=G.nxt[i])
		if(!dfn[v=G.to[i]])
		{
			fa[v]=x, Tarjan(v), low[x]=std::min(low[x],low[v]);
			if(dfn[x]<=low[v])
			{
				T.Add_direct(x,++tot);
				do{
					T.Add_direct(tot,sk[top--]);
				}while(sk[top+1]!=v);
			}
		}
		else low[x]=std::min(low[x],dfn[v]);
}
void DFS1(int x)
{
	int mx=0; sz[x]=1;
	for(int v,i=T.H[x]; i; i=T.nxt[i])
	{
		fa[v=T.to[i]]=x, dep[v]=dep[x]+1, sum[v]=sum[x]+(v<=n), DFS1(v), sz[x]+=sz[v];
		if(sz[v]>mx) mx=sz[v], son[x]=v;
	}
}
void DFS2(int x,int _tp)
{
	tp[x]=_tp, dfn[x]=++Index;
	if(son[x])
	{
		DFS2(son[x],_tp);
		for(int v,i=T.H[x]; i; i=T.nxt[i])
			if((v=T.to[i])!=son[x]) DFS2(v,v);
	}
}
inline int LCA(int u,int v)
{
	while(tp[u]!=tp[v]) dep[tp[u]]>dep[tp[v]]?u=fa[tp[u]]:v=fa[tp[v]];
	return dep[u]<dep[v]?u:v;
}
inline int Sum(int u,int v){
	return sum[u]+sum[v]-(sum[LCA(u,v)]<<1);
}

int main()
{
	int Case=read();
	while(Case--)
	{
		tot=n=read(), m=read(), G.Init(), T.Init(), Index=top=0;
		memset(son,0,sizeof son), memset(dfn,0,sizeof dfn);//清空这俩啊！！
		for(int i=1; i<=m; ++i) G.AddEdge(read(),read());
		Tarjan(1), /*sum[1]=1,*/ dep[1]=0, DFS1(1), Index=0, DFS2(1,1);
		int Q=read();
		while(Q--)
		{
			K=read();
			for(int i=1; i<=K; ++i) A[i]=read();
			std::sort(A+1,A+1+K,cmp_dfn);
			int ans=0;
			for(int i=1; i<K; ++i) ans+=Sum(A[i],A[i+1]);
			printf("%d\n",(ans+Sum(A[1],A[K]))/2-K+(LCA(A[1],A[K])<=n));
		}
	}
	return 0;
}
