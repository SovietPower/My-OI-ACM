#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=206,M=15000,INF=0x3f3f3f3f;

int n,m,src,des,A[N],B[N],C[N][N],dis[N],pre[N];
int Enum,H[N],nxt[M<<1],fr[M<<1],to[M<<1],cost[M<<1],cap[M<<1];
bool inq[N];
std::queue<int> q;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v,int w,int c)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w, cost[Enum]=c;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0, cost[Enum]=-c;
}
bool SPFA()
{
	memset(dis,0x3f,sizeof dis);
	dis[src]=0, q.push(src);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		inq[x]=0;
		for(int i=H[x]; i; i=nxt[i])
			if(cap[i] && dis[to[i]]>dis[x]+cost[i])
			{
				dis[to[i]]=dis[x]+cost[i], pre[to[i]]=i;
				if(!inq[to[i]]) q.push(to[i]),inq[to[i]]=1;
			}
	}
	return dis[des]<INF;
}
int MCMF()
{
	int res=0,mn=INF;
	for(int i=des; i!=src; i=fr[pre[i]])
		mn=std::min(cap[pre[i]],mn);
	for(int i=des; i!=src; i=fr[pre[i]])
		cap[pre[i]]-=mn,cap[pre[i]^1]+=mn,res+=cost[pre[i]]*mn;
	return res;
}

int main()
{
	n=read(),m=read();
	Enum=1, src=0, des=n+m+1;
	for(int i=1; i<=n; ++i) AddEdge(src,i,A[i]=read(),0);
	for(int i=1; i<=m; ++i) AddEdge(i+n,des,B[i]=read(),0);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			AddEdge(i,j+n,INF,C[i][j]=read());
	int rmin=0,rmax=0;
	while(SPFA()) rmin+=MCMF();
	memset(H,0,sizeof H);
	Enum=1;
	for(int i=1; i<=n; ++i) AddEdge(src,i,A[i],0);
	for(int i=1; i<=m; ++i) AddEdge(i+n,des,B[i],0);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			AddEdge(i,j+n,INF,-C[i][j]);
	while(SPFA()) rmax+=MCMF();
	printf("%d\n%d",rmin,-rmax);

	return 0;
}
