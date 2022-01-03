//memset(0x7f)后的值并不是0x7fffffff(略小)！woc才知道。
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define pr std::pair<int,int>
#define mp std::make_pair
const int N=1e4+5,M=5e5+5,INF=0x3f3f3f3f;

int n,m,S,Enum,H[N],nxt[M],to[M],val[M],dis[N];
std::priority_queue<pr> q;
bool vis[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,int w){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, val[Enum]=w;
}
void Dijkstra()
{
	memset(dis,0x3f,sizeof dis);
	dis[S]=0, q.push(mp(0,S));
	while(!q.empty())
	{
		int x=q.top().second;q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int v,i=H[x]; i; i=nxt[i])
			if(dis[v=to[i]]>dis[x]+val[i])
			{
				dis[v]=dis[x]+val[i];
				if(!vis[v]) q.push(mp(-dis[v],v));
			}
	}
}

int main()
{
	n=read(),m=read(),S=read();
	for(int u,v,i=1; i<=m; ++i) u=read(),v=read(),AddEdge(u,v,read());
	Dijkstra();
	for(int i=1; i<=n; ++i) printf("%d ",dis[i]==INF?0x7fffffff:dis[i]);
	return 0;
}
