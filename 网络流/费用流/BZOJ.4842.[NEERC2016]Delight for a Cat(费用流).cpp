/*
980kb	4212ms
首先如果一个活动的时间满足条件，那么另一个活动也一定满足。~~还有就是这题就是费用流没有为什么。~~不妨假设最初所有时间都用来睡觉，那么我们要对每个$k$大小区间选出$[t2,k-t1]$个时刻打游戏，同时要让选出的$\sum s_i-e_i$尽量小。

假如要求打游戏的时间恰好为$t2$怎么做呢？
对每个时刻建一个点$i$，由$i$向$i+k$连边（不存在则直接连向汇点），容量$1$费用$s_i-e_i$。建一个虚点$p$，$p$向$1\sim k$每个点连容量$1$费用$0$的边，源点$S$向$p$连容量$t2$费用$0$的边。
这样如果选了$i$就一定会选$i+k$，所以每个$k$区间都会恰好选了$t2$个时刻。

那现在打游戏的时间可以提高到$k-t1$呢。
由$i$向$i+1$连边，容量$k-t1-t2$费用$0$。$S$向$p$的连边容量改成$k-t1$。
这样对于每个$k$区间，应该有的$t2$条打游戏的边和之前一样，不会少走。还可以多选$k-t1-t2$个时刻打游戏。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1007,M=3*N*2;
const LL INF=0x3f3f3f3f3f3f3f3f;

int S,T,A[N],B[N],Enum,H[N],nxt[M],to[M],cap[M],len[M],cur[N];
bool vis[N];
LL Cost,dis[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v,int w,int c)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w, len[Enum]=c;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0, len[Enum]=-c;
}
bool SPFA()
{
	static bool inq[N];
	static std::queue<int> q;
	memset(dis,0x3f,T+1<<3);//<<3!!!
	dis[S]=0, q.push(S);
	while(!q.empty())
	{
		int x=q.front();
		q.pop(), inq[x]=0;
		for(int i=H[x],v; i; i=nxt[i])
			if(cap[i]&&dis[to[i]]>dis[x]+len[i])
				dis[v=to[i]]=dis[x]+len[i], !inq[v]&&(q.push(v),inq[v]=1);
	}
	return dis[T]<INF;
}
bool DFS(int x)
{
	if(x==T) return 1;
	vis[x]=1;
	for(int &i=cur[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]&&dis[v]==dis[x]+len[i]&&cap[i]&&DFS(v))//&&cap[i]!!! 有必要的啊 
			return --cap[i],++cap[i^1],Cost+=len[i],1;
	return 0;
}
void MCMF()
{
	while(SPFA())
	{
		memcpy(cur,H,T+1<<2), memset(vis,0,T+1);
		while(DFS(S));
	}
}

int main()
{
	static int e[N];
	int n=read(),K=read(),t1=read(),t2=read(),P=n+1;
	Enum=1, S=0, T=n+2; LL ans=0;
	for(int i=1; i<=n; ++i) ans+=A[i]=read();
	for(int i=1; i<=n; ++i) B[i]=read();
	AE(S,P,K-t1,0);
	for(int i=1; i<=K; ++i) AE(P,i,1,0);
	for(int i=1,tmp=K-t1-t2; i<=n; ++i) AE(i,i+1>n?T:i+1,tmp,0), AE(i,i+K>n?T:i+K,1,A[i]-B[i]), e[i]=Enum;
	MCMF(), printf("%lld\n",ans-Cost);
	for(int i=1; i<=n; ++i) putchar(cap[e[i]]?'E':'S');

	return 0;
}
