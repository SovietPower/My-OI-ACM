/*
3072kb	220ms
首先预处理出$dis[i][j]$，表示从$i$到$j$的最短路。可以用$Floyd$处理。
注意$i,j$是没有大小关系限制的（$i>j$的$dis[i][j]$也要求，虽然后面用不到），因为可以从$i$经过中间点$k,\ i<k<j$，到达$j$。同时$i\to j$只能经过$k<\max(i,j)$的点，否则是走不了$k$的。

然后题意可以转化为用不超过$k$条路径覆盖所有点，最小化边权和。
拆点，建二分图。对于任意两点$i,j,\ i<j$，只由$i$向$j'$连边，容量$1$，费用为$dis[i][j]$。这样建有向边也符合从编号小的向大的走，也不会出现环。
从$S$向$1,...,n$连容量$1$，费用$0$的边；$1,...,n$向$T$连容量$1$，费用$0$的边。
$S$向$0$连容量$k$，费用$0$的边；$0$向每个拆点后的点$1',...,n'$连容量$1$，费用$dis[0][i]$的边。
然后跑最小费用最大流即可。

这样为什么可以满足$k$路径覆盖呢。。从$0$向$i'$流就表示新建一条$0\to i'\to...$的路径，不会超过$k$条。（如果是$i\to j',\ i\neq0$，则表示在一条已有的路径中从$i$走到了$j$）
同时图是$DAG$，且会满流，所以一定合法。

终于遇到zkw比SPFA慢的题了/托腮。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=305,M=(N*N/2+3*N)*2,INF=0x3f3f3f3f;

int S,T,Cost,Enum,H[N],nxt[M],fr[M],to[M],cap[M],cost[M],dis[N][N],pre[N];
bool vis[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v,int w,int c)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w, cost[Enum]=c;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0, cost[Enum]=-c;
}
bool SPFA()
{
	static int dis[N];
	static bool inq[N];
	static std::queue<int> q;
	memset(dis,0x3f,sizeof dis);
	dis[S]=0, q.push(S);
	while(!q.empty())
	{
		int x=q.front(); q.pop();
		inq[x]=0;
		for(int i=H[x],v; i; i=nxt[i])
			if(cap[i] && dis[to[i]]>dis[x]+cost[i])
				dis[v=to[i]]=dis[x]+cost[i], pre[v]=i, !inq[v]&&(q.push(v),inq[v]=1);
	}
	return dis[T]<INF;
}
inline void Augment()
{
	for(int i=T; i!=S; i=fr[pre[i]])
		--cap[pre[i]], ++cap[pre[i]^1], Cost+=cost[pre[i]];
}
int MCMF()
{
	while(SPFA()) Augment();
	return Cost;
}

int main()
{
	const int n=read(),m=read(),K=read();
	Enum=1, S=2*n+1, T=2*n+2;
	memset(dis,0x3f,sizeof dis);
	for(int i=0; i<=n; ++i) dis[i][i]=0;
	for(int i=1,u,v; i<=m; ++i)
		u=read(), v=read(), dis[u][v]=dis[v][u]=std::min(dis[v][u],read());
	for(int k=0; k<=n; ++k)
		for(int i=0; i<=n; ++i)
			for(int j=0; j<=n; ++j)
				if(k<i||k<j) dis[i][j]=std::min(dis[i][j],dis[i][k]+dis[k][j]);
	AE(S,0,K,0);
	for(int i=1; i<=n; ++i) AE(S,i,1,0), AE(i+n,T,1,0);
	for(int i=0; i<n; ++i)
		for(int j=i+1; j<=n; ++j)
			AE(i,j+n,1,dis[i][j]);
	printf("%d\n",MCMF());

	return 0;
}
