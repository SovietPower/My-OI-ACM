/*
836ms	640K
考虑两个$\#$之间产生的花费是怎样的。设这之间放了$k$个棋子，花费是$\frac{k(k-1)}{2}$。
在$(r,c)$处放棋子，行和列会同时产生花费，且花费和该行该连通块与该列该连通块当前有多少个有关。想到网络流就很简单了，建图比较简单，类似[[WC2007]剪刀石头布]。
点数写了3n^2，其实2n^2就够了...
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=55,N2=N*N*3,M=2e5+5,INF=0x3f3f3f3f;

int S,T,mp[N][N],idr[N][N],idc[N][N],Enum,H[N2],nxt[M],to[M],cap[M],cost[M],q[10005],Ans[N*N],cur[N2],Cost,dis[N2];
bool vis[N2];

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
void NumberCol(int x,int y,int id)
{
	int tx=x,cnt=1;
	for(idc[x][y]=id; mp[x+1][y]; idc[++x][y]=id,++cnt);
	for(x=tx; mp[x-1][y]; idc[--x][y]=id,++cnt);
	for(int i=0; i<cnt; ++i) AE(id,T,1,i);
}
inline void Col(int x,int y,int id)
{
	idr[x][y]=id, AE(id+1,idc[x][y],1,0);
}
void NumberRow(int x,int y,int id)
{
	int ty=y,cnt=1;
	for(Col(x,y,id); mp[x][y+1]; Col(x,++y,id),++cnt);
	for(y=ty; mp[x][y-1]; Col(x,--y,id),++cnt);
	for(int i=0; i<cnt; ++i) AE(id,id+1,1,i);
	AE(S,id,cnt,0);
}
void Build(int n)
{
	int tot=0; S=0, T=n*n*3+1, Enum=1;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j) if(mp[i][j]&&!idc[i][j]) NumberCol(i,j,++tot);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j) if(mp[i][j]&&!idr[i][j]) NumberRow(i,j,++tot), ++tot;
}
bool SPFA()
{
	static bool inq[N2];//N2!
	static std::queue<int> q;
	memset(dis,0x3f,T+1<<2);
	q.push(S), dis[S]=0;
	while(!q.empty())
	{
		int x=q.front(); q.pop(), inq[x]=0;
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
	for(int &i=cur[x]; i; i=nxt[i])
		if(cap[i]&&dis[to[i]]==dis[x]+cost[i]&&!vis[to[i]]&&DFS(to[i]))
			return --cap[i],++cap[i^1],Cost+=cost[i],1;
	return 0;
}
void Flow(int tot)
{
	int flow=0;
	while(SPFA())
	{
		memcpy(cur,H,T+1<<2), memset(vis,0,T+1);
		while(flow<tot&&DFS(S)) Ans[++flow]=Cost;
		if(flow>=tot) break;
	}
}

int main()
{
//	freopen("A.in","r",stdin);
//	freopen("A.out","w",stdout);

	int n=read();
	for(int i=1; i<=n; ++i)
	{
		register char c=gc(); while(c!='.'&&c!='#') c=gc(); mp[i][1]=c=='.';
		for(int j=2; j<=n; ++j) mp[i][j]=gc()=='.';
	}
	Build(n);
	int m=read(),mx=0;
	for(int i=1; i<=m; ++i) mx=std::max(mx,q[i]=read());
	Flow(mx);
	for(int i=1; i<=m; printf("%d\n",Ans[q[i++]]));

	return 0;
}
