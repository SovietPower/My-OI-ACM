/*
最大权闭合子图：有一个有向图，每个点有点权，有的为正有的为负。对于任意一条有向边(i,j)，选择了点i就必须选择点j 
结论：对每个正权点i，由s向i连一条容量为w[i]的边；对于每个负权点j，由j向t连一条流量为abs(w[j])的边 
对于原图的边，保留，容量为INF。 
最大权 = 正权和 - 最大流 
证明：将最大流理解为最小割，那么割去的边一定不会是INF的边 
选择一个正权点即不割掉其与s的边，选择一个负权点即割掉其与t的边 
如果选择了一个正权点i，不选负权点j(i,j有边)，即不割掉s到i的边，同时不割掉j到t的边，s和t连通，不符合最小割定义 
如果不选正权点i，选择负权点j，即割掉s到i的边，同时割掉j到t的边，s和t不连通。但是不割掉j到t的边也能保证s和t连通，不满足割量最小 
(这样能保证选了的正点对应的负点都被选择，同时获得的权值最多(丢掉的权值最少))
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=205,M=102*102*2,INF=0x3f3f3f3f;

int n,m,src,des,cost[N],H[N],cur[N],Enum,to[M],cap[M],nxt[M],q[N],lev[N];

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar())
		if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum] = v;
	nxt[Enum] = H[u];
	cap[Enum] = w;
	H[u] = Enum;
}

bool BFS()
{
	for(int i=src;i<=des;++i) cur[i]=H[i], lev[i]=0;
	int h=0,t=1,x;
	q[0]=src, lev[src]=1;
	while(h<t)
	{
		x=q[h++];
		for(int i=H[x];i;i=nxt[i])
			if(cap[i] && !lev[to[i]])
			{
				lev[to[i]]=lev[x]+1, q[t++]=to[i];
				if(to[i]==des) return 1;
			}
	}
	return 0;
}
int Dinic(int u,int flow)
{
	if(u==des) return flow;
	int used=0;
	for(int &i=cur[u];i;i=nxt[i])
		if(cap[i] && lev[to[i]]==lev[u]+1)
		{
			int delta=Dinic(to[i],min(flow-used,cap[i]));
			if(delta)
			{
				cap[i]-=delta, cap[i^1]+=delta, used+=delta;
//				printf("%d %d %d\n",u,delta,used);
				if(used==flow) return flow;
			}
		}
	lev[u]=0;
	return used;
}

int main()
{
	n=read(),m=read();
	src=0, des=n+m+1, Enum=1;
	int tot=0;
	for(int u,v,i=1;i<=n;++i)
	{
		v=read(),u=read(), tot+=v;
		AddEdge(0,i,v), AddEdge(i,0,0);
		while(u) AddEdge(i,u+n,INF),AddEdge(u+n,i,0), u=read();
	}
	for(int i=1;i<=m;++i) cost[i]=read();
	for(int i=n+1;i<des;++i) AddEdge(i,des,cost[i-n]), AddEdge(des,i,0);
	int res=0;
	while(BFS())
		res+=Dinic(src,INF);
	printf("%d",tot-res);

	return 0;
}
