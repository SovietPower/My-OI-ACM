/*
31ms	100KB
复习了下[餐巾计划问题]。全忘了=-=
首先这是一道网络流。然后本题有$n$种建图方法，以及$smy$ dalao还有单纯形做法。
先假设所有物品都是买入的。那么对于每一天，拆成两个点$i,i'$，$S\to i$连边$(1,cost_{a_i})$（容量$1$费用$cost_{a_i}$），$i'\to T$连边$(1,0)$，$i\to i'$连边$(1,0)$。这样就能满足一些基本要求了。
然后考虑可以把某个$a_i$留到之后一天。考虑从$i-1$向$a_i$上次出现的位置$las_{a_i}$连边，容量$1$费用$-cost_{a_i}$；$i\to i+1$连边$(k-1,0)$。$las_{a_i}$那一天的流量可以流到$i-1$再流回$las_{a_i}'$，退回$cost_{a_i}$的钱。
边的含义是，表示允许保留$k-1$种物品在架子上（必须要保留当前物品所以是$k-1$）。当前物品的流量在$i$已经有了，所以让$a_i$上次的流量通过$i-1$流回去。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define S 0
#define gc() getchar()
typedef long long LL;
const int N=407,M=N*5,INF=0x3f3f3f3f;

int Cost,T,A[N],c[N],las[N],H[N],Enum,nxt[M],to[M],cap[M],cost[M],dis[N],cur[N];
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
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w, cost[Enum]=c;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0, cost[Enum]=-c;
}
bool SPFA()
{
	static bool inq[N];
	static std::queue<int> q;
	memset(inq,0,T+1), memset(dis,0x3f,T+1<<2);
	dis[S]=0, q.push(0);
	while(!q.empty())
	{
		int x=q.front(); q.pop();
		inq[x]=0;
		for(int i=H[x],v; i; i=nxt[i])
			if(cap[i]&&dis[v=to[i]]>dis[x]+cost[i])
				dis[v]=dis[x]+cost[i], !inq[v]&&(q.push(v),inq[v]=1);
	}
	return dis[T]<INF;
}
bool DFS(int x)
{
	if(x==T) return 1;
	vis[x]=1;
	for(int &i=cur[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]&&cap[i]&&dis[v]==dis[x]+cost[i]&&DFS(v))
			return --cap[i],++cap[i^1],Cost+=cost[i],1;
	return 0;
}
int MCMF()
{
	while(SPFA())
	{
		memset(vis,0,T+1), memcpy(cur,H,T+1<<2);
		while(DFS(S));
	}
	return Cost;
}

int main()
{
//	freopen("B.in","r",stdin);
//	freopen("B.out","w",stdout);

	int n=read(),K=read(); Enum=1, T=n<<1|1;
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<=n; ++i) c[i]=read();
	for(int i=1; i<=n; ++i)
	{
		AE(S,i,1,c[A[i]]), AE(i,i+n,1,0), AE(i+n,T,1,0);
		if(i<n&&K>1) AE(i,i+1,K-1,0);
		if(las[A[i]]) AE(i-1,las[A[i]]+n,1,-c[A[i]]);
		las[A[i]]=i;
	}
	printf("%d\n",MCMF());

	return 0;
}
