/*
2292kb	416ms
$Description$
给定一张部分边方向已确定的竞赛图。你需要给剩下的边确定方向，使得图中的三元环数量最多。
$n\leq100$。
$Solution$
这种选择之间有影响，而且$n$很小的题考虑网络流啊。

最理想的情况能得到的三元环个数是$C_n^3$个。我们考虑怎样会使三元环个数减少。
如果三个点之间不成三元环，那么一定是某个点入度为$2$，某个点出度为$2$，另一个点入度出度都为$1$。
不妨只考虑入度。如果一个点入度为$2$，那么会减少$1$个三元环；如果入度为$3$，那么会减少$C_3^2=3$个三元环（设连向该点$A$的三个点为$B,C,D$，$A,B,C$、$A,B,D$、$A,C,D$之间都形不成三元环）...
也就是设一个点的入度为$dgr$，会减少$C_{dgr}^2$个三元环。那么答案就是$C_n^3-\sum_{i=1}^nC_{dgr_i}^2$。
而度数每次改变$1$，减少的三元环个数是$C_{dgr}^2-C_{dgr-1}^2=dgr-1$。

然后就可以考虑给每个点分配度数了。对每条边新建一个点$x$，由源点向$x$连容量$1$、费用$0$的边，$x$向边的两端点分别连容量为$1$、费用为$0$的边。
对于原图的$n$个点，每个点向汇点分别连容量为$1$，费用为$0,1,2,3...$的边。
跑费用流，$C_n^3-cost$就是答案了。

实现上，对于确定的边并不需要建出来，把答案先减掉$\frac{dgr_i(dgr_i-1)}{2}$；然后枚举$i$连向汇点的边时，费用从$dgr_i$开始枚举就可以了。（优化很明显）
数组`memset(A,...,某个确定大小)`，注意`A[]`是`int`还是`bool`！`bool`是一字节！

另外有种[随机化+迭代]的做法，跑得很快。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=105+105*52,M=4*105*105*2;

int src,des,Cost,Enum,cur[N],H[N],nxt[M],fr[M],to[M],cap[M],cost[M],dis[N];
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v,int w,int c)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w, cost[Enum]=c;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0, cost[Enum]=-c;
}
bool SPFA()
{
	static bool inq[N];
	static std::queue<int> q;
	memset(dis,0x3f,des+1<<2);
	dis[0]=0, q.push(0);
	while(!q.empty())
	{
		int x=q.front(); q.pop();
		inq[x]=0;
		for(int i=H[x],v; i; i=nxt[i])
			if(cap[i] && dis[v=to[i]]>dis[x]+cost[i])
				dis[v]=dis[x]+cost[i], !inq[v]&&(q.push(v),inq[v]=1);
	}
	return dis[des]<0x3f3f3f3f;
}
int DFS(int x)
{
	if(x==des) return 1;
	vis[x]=1;
	for(int &i=cur[x]; i; i=nxt[i])
		if(!vis[to[i]] && cap[i] && dis[to[i]]==dis[x]+cost[i] && DFS(to[i]))
			return --cap[i],++cap[i^1],Cost+=cost[i],1;
	return 0;
}
int MCMF()
{
	while(SPFA())
	{
		memcpy(cur,H,des+1<<2), memset(vis,0,des+1);//bool是1字节！！！
		while(DFS(0));
	}
	return Cost;
}

int main()
{
	static int dgr[105],id[N],tag[N],Ans[105][105];
	const int n=read(); Enum=1, src=0, des=(n*n+n)/2+1;
	if(n<3) return putchar('0'),0;
	for(int i=1,tot=n; i<=n; ++i)
	{
		for(int j=1; j<=i; ++j) read();
		for(int j=i+1; j<=n; ++j)
			switch(AE(0,++tot,1,0),read())
			{
				case 0: tag[tot]=1, ++dgr[j]; break;
				case 1: tag[tot]=2, ++dgr[i]; break;
				case 2: AE(tot,i,1,0), id[tot]=Enum, AE(tot,j,1,0); break;//->i: i wins
			}
	}
	int ans=n*(n-1)*(n-2)/6;
	for(int i=1; i<=n; ++i)
	{
		ans-=dgr[i]*(dgr[i]-1)/2;
		for(int j=dgr[i]; j<n-1; ++j) AE(i,des,1,j);
	}
	printf("%d\n",ans-MCMF());
	for(int i=1,tot=n; i<=n; ++i)
		for(int j=i+1; j<=n; ++j)
			if(tag[++tot]) Ans[i][j]=tag[tot]-1;
			else Ans[i][j]=cap[id[tot]]?1:0;
	for(int i=1; i<=n; ++i,putchar('\n'))
	{
		for(int j=1; j<i; ++j) printf("%d ",Ans[j][i]^1);
		for(int j=i; j<=n; ++j) printf("%d ",Ans[i][j]);
	}

	return 0;
}
