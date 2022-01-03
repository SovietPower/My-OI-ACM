/*
77ms	8800KB
$Description$
给定一张有向图，求哪些边一定在最短路上。对于不一定在最短路上的边，输出最少需要将其边权改变多少，才能使其一定在最短路上（边权必须为正，若仍不行输出NO）。
$Solution$
正反跑两遍Dijkstra。一条边$(u,v,w)$在最短路上当且仅当$dis[S][u]+dis[v][T]+w=dis[S][T]$。
一定在最短路上则满足，从$S$走最短路到$u$的方案数 * 从$v$走最短路到$T$的方案数 = 从$S$到$T$的最短路径数。
也可以再对最短路上的边建图，缩点求桥。
路径数要用双模数。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define mp std::make_pair
#define pr std::pair<LL,int>
#define mod 1000000007
#define mod2 805306457
typedef long long LL;
const int N=1e5+5;

int ss1[N],st1[N],ss2[N],st2[N];
LL ds[N],dt[N];
std::priority_queue<pr> q;
char IN[MAXIN],*SS=IN,*TT=IN;
struct Graph
{
	int Enum,H[N],nxt[N],fr[N],to[N],len[N];
	inline void AE(int u,int v,int w)
	{
		to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
	}
}G,R;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Dijkstra(int S,int T,int *sum,int *sum2,LL *dis,const Graph &g)
{
	static bool vis[N];
	memset(vis,0,sizeof vis);
	memset(dis,0x3f,sizeof ds);
	dis[S]=0, sum[S]=sum2[S]=1, q.push(mp(0,S));
	while(!q.empty())
	{
		int x=q.top().second; q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=g.H[x],v; i; i=g.nxt[i])
			if(dis[v=g.to[i]]>dis[x]+g.len[i])
				sum[v]=sum[x], sum2[v]=sum2[x], q.push(mp(-(dis[v]=dis[x]+g.len[i]),v));
			else if(dis[v]==dis[x]+g.len[i])
				sum[v]+=sum[x], sum[v]>=mod&&(sum[v]-=mod),
				sum2[v]+=sum2[x], sum2[v]>=mod2&&(sum2[v]-=mod2);
	}
}

int main()
{
	int n=read(),m=read(),S=read(),T=read();
	for(int i=1,u,v,w; i<=m; ++i) u=read(),v=read(),w=read(),G.AE(u,v,w),R.AE(v,u,w);
	Dijkstra(S,T,ss1,ss2,ds,G), Dijkstra(T,S,st1,st2,dt,R);
	for(int p=1,u,v,w; p<=m; ++p)
	{
		u=G.fr[p],v=G.to[p],w=G.len[p];
		if(ds[u]+w+dt[v]==ds[T] && 1ll*ss1[u]*st1[v]%mod==ss1[T] && 1ll*ss2[u]*st2[v]%mod2==ss2[T]) puts("YES");
		else if(ds[T]-ds[u]-dt[v]-1>0) printf("CAN %I64d\n",-(ds[T]-ds[u]-dt[v])+w+1);
		else puts("NO");
	}
	return 0;
}
