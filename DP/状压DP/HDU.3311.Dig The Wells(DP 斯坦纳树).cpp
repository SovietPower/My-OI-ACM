/*
46MS	1544K
$Description$
有n座庙、一共n+m个点，可以在任意一些点修建水井，不同位置花费不同；也可以某些点之间连无向边共享水。求使n座庙都有水的最小花费。
$Solution$
因为每个点都可以通过一定费用使其自己满足，直接像上题那样不会做。。
新建一个点0，其到每个点的边权为使每个点成为井的花费，那么就是求使0点与n座庙连通的最小花费。
那么初始状态就是对于每座庙，f[1<<i-1][i]=0。可以套模板了。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=1009,M=1e4+5+N*2/*!*/,INF=1e9;

int cost[N],f[(1<<5)+1][N],Enum,H[N],nxt[M],to[M],len[M];
std::queue<int> q;
bool inq[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int w,int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, len[Enum]=w;
}
void SPFA(int *f)
{
	while(!q.empty())
	{
		int x=q.front();
		q.pop(), inq[x]=0;
		for(int v,i=H[x]; i; i=nxt[i])
			if(f[v=to[i]]>f[x]+len[i])
			{
				f[v]=f[x]+len[i];
				if(!inq[v]) q.push(v), inq[v]=1;
			}
	}
}

int main()
{
	int n;
	while(~scanf("%d",&n))
	{
		int m=read()+n, p=read();
		Enum=0, memset(H,0,sizeof H), memset(f,0x3f,sizeof f);

		for(int i=1; i<=n; ++i) f[1<<i-1][i]=0, AddEdge(read(),0,i);
		for(int i=n+1; i<=m; ++i) AddEdge(read(),0,i);
		while(p--) AddEdge(read(),read(),read());

		for(int s=1,lim=1<<n; s<lim; ++s)
		{
			for(int i=0; i<=m; ++i)
			{
				for(int sub=(s-1)&s; sub; sub=(sub-1)&s)
					f[s][i]=std::min(f[s][i],f[sub][i]+f[sub^s][i]);
				if(f[s][i]<INF) q.push(i), inq[i]=1;
			}
			SPFA(f[s]);
		}
		printf("%d\n",f[(1<<n)-1][0]);
	}

	return 0;
}
