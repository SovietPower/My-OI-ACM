/*
880kb	88ms
容易看出是个最短路+DP。既然答案和天数有关，那么就令f[i]表示前i天最小成本。
这个转移很好想: f[i]=min(f[i],f[j]+cost(j+1,i)+K)，cost(j+1,i)即第j+1天到第i天(使用同一道路)所需花费，即最短路，这个可以预处理出来。
注意是否可行的判断。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define pr std::pair<int,int>
#define mp std::make_pair
const int N=23,M=900,INF=0x3f3f3f3f;//边数n*n啊。。

int d,n,K,m,Enum,H[N],nxt[M],to[M],len[M],cost[102][102],dis[N],f[102];
bool vis[N],can_t[N][102];
std::priority_queue<pr> q;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, len[Enum]=w;
}
inline bool Judge(int x,int u,int v){
//	return st[x]>v||ed[x]<u;//WA:可能有多段！有毒！
	for(int i=u; i<=v; ++i) if(can_t[x][i]) return 0;
	return 1;
}
int Dijkstra(int a,int b)
{
	memset(vis,0,sizeof vis);
	memset(dis,0x3f,sizeof dis);
	while(!q.empty()) q.pop();
	dis[1]=0, q.push(mp(0,1));
	while(!q.empty())
	{
		int x=q.top().second;q.pop();
		if(x==n) return dis[n]*(b-a+1);
		if(vis[x]) continue;
		vis[x]=1;
		for(int v,i=H[x]; i; i=nxt[i])
			if(!vis[v=to[i]] && Judge(v,a,b) && dis[v]>dis[x]+len[i])
				dis[v]=dis[x]+len[i], q.push(mp(-dis[v],v));
	}
	return INF;
}

int main()
{
	d=read(),n=read(),K=read(),m=read();
	int u,v;
	while(m--) u=read(),v=read(),AddEdge(u,v,read());
	int t=read(),p;
	while(t--){
		p=read(),u=read(),v=read();
		for(int i=u; i<=v; ++i) can_t[p][i]=1;
	}
	for(int i=1; i<=d; ++i)
		for(int j=i; j<=d; ++j)
		{
			cost[i][j]=Dijkstra(i,j);
			if(cost[i][j]==INF){
				for(int k=j+1; k<=d; ++k) cost[i][k]=INF;
				break;
			}
		}
	for(int i=1; i<=d; ++i) f[i]=cost[1][i];
	for(int i=2; i<=d; ++i)
		for(int j=i-1; j; --j)
			if(cost[j+1][i]<INF)//注意INF的判断。
				f[i]=std::min(f[i],f[j]+cost[j+1][i]+K);
			else break;
	printf("%d",f[d]);

	return 0;
}
