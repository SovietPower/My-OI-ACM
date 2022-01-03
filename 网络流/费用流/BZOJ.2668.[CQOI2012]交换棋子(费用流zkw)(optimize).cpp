/*
1148kb	16ms
首先黑白棋子的交换等价于黑棋子在白格子图上移动，都到达指定位置。~~在这假设我们知道这题用网络流做。~~
那么黑棋到指定位置就是一条路径，考虑怎么用流模拟出这条路径。
我们发现除了路径的起点和终点的格子消耗次数为1，路径上其它点的格子交换次数为2。
可以想到把每个点拆成in和out，但这样无法体现出，作为起点/终点与路径中其它点的次数消耗差别。
于是拆成三个点，in,x,out，x代表原点，设点x流量为lim，in,out平分流量，边容量为lim/2。
直接lim/2对么？注意每个点只会作为起点或终点一次。若x最初白最后黑，那么会作为终点一次而不作为起点，则连边(in->x,(lim+1)/2),(x->out,lim/2)；若是黑到白，出会比入多一次；若该点不需要变则流量都是lim/2。
花费就在in->x与x->out上设1就行了。
对于起始图中的黑点i，连边(S->x(i),1)；对于最终图中的黑点i，连边(x(i)->T,1)。（(u->v,w)表示u->v的单向边，容量为w）
对于相邻点i,j，连边(out(i),in(j),INF)。
为什么要拆三个点呢，因为对于可能是起点或终点的点我们无法区分初始流量。
但是如果它是起点或终点，则一定要作为起点或终点走一次，把流量给它就是了；否则是不会有1的流量的。
如果该点是起点或终点，则$in->out$流量为(lim+1)/2，否则流量为lim/2。这样就可以只拆两个点了。
源点汇点都与in连就行。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=805,M=N*22,INF=0x3f3f3f3f;

int n,m,S,T,id[25][25][2],Enum,H[N],cur[N],nxt[M],to[M],cap[M],cost[M],dis[N],Cost;
bool vis[N];
std::queue<int> q;
char st[25][25],ed[25][25];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
#define AE(u,v,w,c) to[++Enum]=v,nxt[Enum]=H[u],H[u]=Enum,cap[Enum]=w,cost[Enum]=c,to[++Enum]=u,nxt[Enum]=H[v],H[v]=Enum,cap[Enum]=0,cost[Enum]=-c
bool SPFA()
{
	memset(vis,0,sizeof vis);
	memset(dis,0x3f,sizeof dis);
	dis[S]=0, q.push(S);
	while(!q.empty())
	{
		int x=q.front();
		q.pop(), vis[x]=0;
		for(int v,i=H[x]; i; i=nxt[i])
			if(cap[i] && dis[v=to[i]]>dis[x]+cost[i])
				dis[v]=dis[x]+cost[i], !vis[v]&&(q.push(v),vis[v]=1);
	}
	return dis[T]<INF;
}
int DFS(int x,int f)
{
	if(x==T) return f;
	vis[x]=1;
	for(int &i=cur[x],v,tmp; i; i=nxt[i])
		if(cap[i] && !vis[v=to[i]] && dis[v]==dis[x]+cost[i])
			if(tmp=DFS(v,std::min(cap[i],f)))
				return cap[i]-=tmp,cap[i^1]+=tmp,Cost+=tmp*cost[i],tmp;
	return 0;
}
int MCMF()
{
	int res=0;
	while(SPFA())
	{
		for(int i=S; i<=T; ++i) cur[i]=H[i];
		while(int tmp=DFS(S,INF)) res+=tmp;
	}
	return res;
}

int main()
{
	n=read(),m=read(),Enum=1,S=0,T=n*m*2+1;
	for(int i=1; i<=n; ++i) scanf("%s",st[i]+1);
	for(int i=1; i<=n; ++i) scanf("%s",ed[i]+1);
	int tot=0;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			id[i][j][0]=++tot,id[i][j][1]=++tot;
	int tot1=0, tot2=0;
	for(int i=1; i<=n; ++i)
	{
		char c=gc();
		for(; !isdigit(c); c=gc());
		for(int j=1; j<=m; ++j, c=gc())
		{
			const char s=st[i][j],t=ed[i][j];
			const int in=id[i][j][0],out=id[i][j][1],lim=c-'0';
			if(s=='1') AE(S,in,1,0), ++tot1;
			if(t=='1') AE(in,T,1,0), ++tot2;
			if(s!=t) AE(in,out,lim+1>>1,1);
			else AE(in,out,lim>>1,1);
			if(i<n) AE(out,id[i+1][j][0],INF,0), AE(id[i+1][j][1],in,INF,0);//同色的当然也可以连边(想啥呢→_→)
			if(i<n&&j<m) AE(out,id[i+1][j+1][0],INF,0), AE(id[i+1][j+1][1],in,INF,0);
			if(i<n&&j>1) AE(out,id[i+1][j-1][0],INF,0), AE(id[i+1][j-1][1],in,INF,0);
			if(j<m) AE(out,id[i][j+1][0],INF,0), AE(id[i][j+1][1],in,INF,0);
		}
	}
	printf("%d\n",(tot1==tot2&&MCMF()==tot1)?(Cost):-1);

	return 0;
}
