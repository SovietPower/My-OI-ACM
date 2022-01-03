/*
688K	329MS
直接跑费用流会T，但是也没必要。
如果残量网络存在负环（只走有流量的边），那么沿该负环继续增广，可以得到一组更优的解。否则就是当前流量下的最小费用流。
所以建出残量网络，找出负环来，在负环上走一遍就行了。
$S\to i$的每条边的流量肯定是流满的，所以不需要建（$i'\to T$的就不一定了）。
复杂度$O(nm)$。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=205,M=(105*105+N)*2,INF=0x3f3f3f3f;

int Enum,H[N],nxt[M],to[M],cost[M],dis[N],pre[N],g[105][105];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline void AE(int u,int v,int w,int c)
{
	if(w) to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, cost[Enum]=c;
}
int SPFA(const int n)
{
	static int tm[N];
	static bool inq[N];
	std::queue<int> q;
	memset(dis,0x3f,n+1<<2);
	dis[n]=0, q.push(n), tm[n]=1;
	while(!q.empty())
	{
		int x=q.front(); q.pop();
		inq[x]=0;
		for(int i=H[x],v; i; i=nxt[i])
			if(dis[to[i]]>dis[x]+cost[i])
			{
				dis[v=to[i]]=dis[x]+cost[i], pre[v]=x;
				if(!inq[v])
				{
					if(++tm[v]>=n) return v;
					q.push(v), inq[v]=1;
				}
			}
	}
	return -1;
}
void FindCircle(int x,const int n)
{
	static bool vis[N];
	while(!vis[x]) vis[x]=1, x=pre[x];//p不一定在环上（但是能回到环），应该先找出来啊。。
	int tmp=x;
	do
	{
		int v=pre[x];//v->x
		if(x<=n && v>n) --g[x][v-n];
		else if(x>n && v<=n) ++g[v][x-n];
		x=v;
	}while(x!=tmp);
}

int main()
{
	static int a[N],b[N],c[N],d[N],cap[N],use[N];
	const int n=read(),m=read(),T=n+m+1;
	for(int i=1; i<=n; ++i) a[i]=read(),b[i]=read(),read();
	for(int i=1; i<=m; ++i) c[i]=read(),d[i]=read(),cap[i]=read();
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
		{
			use[j]+=g[i][j]=read();
			int cost=std::abs(a[i]-c[j])+std::abs(b[i]-d[j])+1;
			AE(i,j+n,INF-g[i][j],cost), AE(j+n,i,g[i][j],-cost);//negative!
		}
	for(int i=1; i<=m; ++i) AE(i+n,T,cap[i]-use[i],0), AE(T,i+n,use[i],0);
	int p=SPFA(T);
	if(p==-1) puts("OPTIMAL");
	else
	{
		FindCircle(p,n), puts("SUBOPTIMAL");
		for(int i=1; i<=n; ++i,putchar('\n'))
			for(int j=1; j<=m; ++j) printf("%d ",g[i][j]);
	}

	return 0;
}
