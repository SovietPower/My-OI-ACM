/*
779ms	28900KB
先随便建一棵树。
如果两个点(u,v)不经过非树边，它们的dis可以直接算。
如果两个点经过非树边呢？即它们一定要经过该边的两个端点，可以直接用这两个点到(u,v)的最短路更新。
所以枚举每条非树边的两个端点，求一遍最短路。非树边最多21条，所以要求的点最多42个。
另外对于一条边的两个点只求一个就好了。因为要用这条非树边的话它们两个都要经过。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<LL,int>
//#define gc() getchar()
#define MAXIN 250000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int Enum,H[N],nxt[N<<1],to[N<<1],len[N<<1],fa[N],dep[N],sz[N],son[N],top[N],sk[N];
LL dist[N],dis[23][N];
bool upd[N],nottree[N];
std::priority_queue<pr> q;
char IN[MAXIN],*SS=IN,*TT=IN;

#define AE(u,v,w) to[++Enum]=v,nxt[Enum]=H[u],H[u]=Enum,len[Enum]=w,to[++Enum]=u,nxt[Enum]=H[v],H[v]=Enum,len[Enum]=w
inline int read()
{
	int now=0; register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int LCA(int u,int v)
{
	while(top[u]!=top[v]) dep[top[u]]>dep[top[v]]?u=fa[top[u]]:v=fa[top[v]];
	return dep[u]>dep[v]?v:u;
}
int Find(int x)
{
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
void DFS1(int x)
{
	int mx=0; sz[x]=1;
	for(int v,i=H[x]; i; i=nxt[i])
		if(!nottree[i] && (v=to[i])!=fa[x])
		{
			fa[v]=x, dep[v]=dep[x]+1, dist[v]=dist[x]+len[i], DFS1(v), sz[x]+=sz[v];
			if(sz[v]>mx) mx=sz[v], son[x]=v;
		}
}
void DFS2(int x,int tp)
{
	top[x]=tp;
	if(son[x])
	{
		DFS2(son[x],tp);
		for(int i=H[x]; i; i=nxt[i])
			if(!nottree[i] && to[i]!=fa[x] && to[i]!=son[x]) DFS2(to[i],to[i]);
	}
}
void Dijkstra(LL *dis,int s,int n)
{
	static bool vis[N];

	memset(vis,0,sizeof vis);
	memset(dis,0x3f,sizeof(LL)*(n+1));//dis是指针!
	dis[s]=0, q.push(mp(0,s));
	while(!q.empty())
	{
		int x=q.top().second; q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=H[x],v; i; i=nxt[i])
			if(dis[v=to[i]]>dis[x]+len[i]) q.push(mp(-(dis[v]=dis[x]+len[i]),v));
	}
}

int main()
{
	int n=read(), m=read(); Enum=1;
	for(int i=1; i<=n; ++i) fa[i]=i;

	int tote=0,cnt=0;
	for(int i=1,r1,r2,u,v,w; i<=m; ++i)
	{
		r1=Find(u=read()), r2=Find(v=read()), w=read();
		AE(u,v,w);
		if(r1==r2) nottree[Enum]=1, nottree[Enum^1]=1, sk[++tote]=Enum;
		else fa[r1]=r2;
	}
	fa[1]=1, DFS1(1), DFS2(1,1);
	for(int i=1; i<=tote; ++i)
	{
		int e=sk[i];
		if(!upd[to[e]]) upd[to[e]]=1, Dijkstra(dis[++cnt],to[e],n);
//		if(!upd[to[e^1]]) upd[to[e^1]]=1, Dijkstra(dis[++cnt],to[e^1],n);
	}

	for(int Q=read(),u,v; Q--; )
	{
		u=read(),v=read();
		LL ans=dist[u]+dist[v]-(dist[LCA(u,v)]<<1ll);
		for(int i=1; i<=cnt; ++i)
			ans=std::min(ans,dis[i][u]+dis[i][v]);
		printf("%I64d\n",ans);
	}

	return 0;
}
