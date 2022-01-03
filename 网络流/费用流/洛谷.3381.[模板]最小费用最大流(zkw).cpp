//1314ms	2.66MB
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 350000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=5005,M=1e5+5,INF=0x3f3f3f3f;

int n,m,src,des,Enum,cur[N],H[N],nxt[M],to[M],cap[M],cost[M],dis[N];
long long Cost;
bool vis[N];
std::queue<int> q;
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int c,int w,int v,int u)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w, cost[Enum]=c;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0, cost[Enum]=-c;
}
bool SPFA()
{
	memset(vis,0,sizeof vis);
	memset(dis,0x3f,sizeof dis);
	dis[src]=0, q.push(src);
	while(!q.empty())
	{
		int x=q.front();
		q.pop(), vis[x]=0;
		for(int i=H[x],v; i; i=nxt[i])
			if(cap[i] && dis[v=to[i]]>dis[x]+cost[i])
				dis[v]=dis[x]+cost[i], !vis[v]&&(q.push(v),vis[v]=1);
	}
	return dis[des]<INF;
}
int DFS(int x,int f)
{
	if(x==des) return f;
	vis[x]=1;
	for(int &i=cur[x],tmp; i; i=nxt[i])
		if(!vis[to[i]] && cap[i] && dis[to[i]]==dis[x]+cost[i])
			if(tmp=DFS(to[i],std::min(f,cap[i])))
				return cap[i]-=tmp,cap[i^1]+=tmp,Cost+=1ll*tmp*cost[i],tmp;
	return 0;
}
void MCMF()
{
	long long flow=0,tmp;
	while(SPFA())
	{
		for(int i=1; i<=n; ++i) cur[i]=H[i];
		while(tmp=DFS(src,INF)) flow+=tmp;
	}
	printf("%lld %lld\n",flow,Cost);
}

int main()
{
	Enum=1,n=read(),m=read(),src=read(),des=read();
	for(int i=1; i<=m; ++i) AddEdge(read(),read(),read(),read());
	MCMF();
	return 0;
}
