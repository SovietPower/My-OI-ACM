#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define Turn(i,j) (m*(i-1)+j)//²»ÊÇn(i-1)+j!
const int N=605,M=N<<1,INF=0x3f3f3f3f,Mod=2e5;

int n,m,src,des,Enum,H[N],nxt[M<<1],fr[M<<1],to[M<<1],cap[M<<1],cost[M<<1];
int q[Mod+3],dis[N],pre[N];
bool inq[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v,int w,int c)
{
	to[++Enum]=v, fr[Enum]=u, cap[Enum]=w, cost[Enum]=c, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, fr[Enum]=v, cap[Enum]=0, cost[Enum]=-c, nxt[Enum]=H[v], H[v]=Enum;
}
bool BFS()
{
	memset(dis,0x3f,sizeof dis);
	dis[src]=0, q[0]=src;
	int h=0,t=1;
	while(h!=t)
	{
		int x=q[h++]; inq[x]=0;
		if(h>=Mod) h-=Mod;
		for(int i=H[x]; i; i=nxt[i])
			if(cap[i] && dis[to[i]]>dis[x]+cost[i])
			{
				dis[to[i]]=dis[x]+cost[i], pre[to[i]]=i;
				if(!inq[to[i]]) q[t++]=to[i], inq[to[i]]=1, t>=Mod?t-=Mod:0;
			}
	}
	return dis[des]<INF;
}
int MCMF()
{
	int res=0,delta=INF;
	for(int i=des; i!=src; i=fr[pre[i]])
		delta=std::min(delta,cap[pre[i]]);
	for(int i=des; i!=src; i=fr[pre[i]])
		cap[pre[i]]-=delta, cap[pre[i]^1]+=delta, res+=delta*cost[pre[i]];//!
	return res;
}

int main()
{
	Enum=1;
	int a=read(),b=read();n=read()+1,m=read()+1;
	src=0, des=n*m+1;
	int v,x,y;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<m; ++j)
			v=read(), AddEdge(Turn(i,j),Turn(i,j+1),1,-v), AddEdge(Turn(i,j),Turn(i,j+1),INF,0);
	for(int j=1; j<=m; ++j)
		for(int i=1; i<n; ++i)
			v=read(), AddEdge(Turn(i,j),Turn(i+1,j),1,-v), AddEdge(Turn(i,j),Turn(i+1,j),INF,0);
	for(int i=1; i<=a; ++i)
		v=read(),x=read()+1,y=read()+1, AddEdge(src,Turn(x,y),v,0);
	for(int i=1; i<=b; ++i)
		v=read(),x=read()+1,y=read()+1, AddEdge(Turn(x,y),des,v,0);
	int res=0;
	while(BFS()) res+=MCMF();
	printf("%d",-res);

	return 0;
}
