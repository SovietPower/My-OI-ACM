/*
904kb	48ms
$Description$
有一个$n\times m$的矩阵，初始时每个位置权值为$0$。可执行两种操作：1. 使某行所有位置加1或减1。2. 使某列所有位置加1或减1。
给定$k$个限制$(x,y,c)$，表示$(x,y)$位置操作完后价值需为$c$，求是否能在若干次操作后，矩阵满足所有条件。
$n,m,k\leq 1000$。
$Solution$
记$r_i$为第$i$行整体加了多少的权值，$c_i$为第$i$列整体加了多少权值，那么限制$(i,j),k$就是$r_i+c_j=k$。~~我竟然还想网络流。~~
这就是差分约束裸题了。$r_i+c_j=k\Rightarrow r_i-(-c_j)\leq k\ \&\&\ -c_j-r_i\leq -k$。
~~注意形式是$x_j-x_i\leq w$=v=~~
建边跑最短路判负环即可。
去洛谷复习以前的板子（不会写DFS=-=），发现DFS判负环被卡掉了？~~太棒啦不用背DFS的代码惹。~~
乖乖写BFS。
**带权并查集：**
发现这题和[BZOJ1202](https://lydsy.com/JudgeOnline/problem.php?id=1202)是一模一样的= =。因为全是相等关系，其实是十分特殊的差分约束，可以用带权并查集做。
记$fa[x]$表示$x$所在集合的根节点，$dis[x]$表示$x$到$fa[x]$的实际距离。
所谓距离是指：对于$r+c=k$，变成$r-(-c)=k$，即$r$比$-c$大$k$，就在$r\to -c$之间连距离为$k$的边，同时令$fa[r]=-c$。
这样对于一个限制$r,c,k$，如果$r,c$不在同一集合就合并（令较大的数的祖先是较小的数）。在并查集$Find$过程中顺便维护一下$dis$（具体见代码好惹，注意变量赋值顺序）。
如果$r,c$在同一集合，就根据$dis$差判一下它俩的距离是否等于$k$。

就算$k$可能是负的这么做也没什么问题。（废话=v=）
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=2005;

int Enum,H[N],nxt[N],to[N],len[N],dis[N],dgr[N];
bool vis[N],inq[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline void AE(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
}
bool SPFA(int s,int n)//怎么都直接拿n做总点数的=-= 强迫症表示不行 
{
	std::queue<int> q;
	q.push(s), dis[s]=0;
	while(!q.empty())
	{
		int x=q.front(); q.pop();
		inq[x]=0;
		for(int i=H[x],v; i; i=nxt[i])
			if(dis[v=to[i]]>dis[x]+len[i])
			{
				if(++dgr[v]>n) return 1;
				dis[v]=dis[x]+len[i], !inq[v]&&(q.push(v),inq[v]=1);
			}
	}
	return 0;
}

int main()
{
	for(int Ts=read(); Ts--; )
	{
		int n=read(),m=read(),tot=n+m,cnt=0;
		Enum=0, memset(H,0,tot+1<<2), memset(vis,0,tot+1);
		for(int u,v,w,K=read(); K--; )
		{
			u=read(),v=read()+n,w=read();
			AE(v,u,w), AE(u,v,-w);
			if(!vis[u]) vis[u]=1, ++cnt;
			if(!vis[v]) vis[v]=1, ++cnt;
		}
		memset(dis,0x7f,tot+1<<2), memset(dgr,0,tot+1<<2), memset(inq,0,tot+1);
		bool fg=1;
		for(int i=1; i<=tot; ++i)
			if(vis[i]&&dis[i]==dis[0]&&SPFA(i,cnt)) {fg=0; break;}
		puts(fg?"Yes":"No");
	}

	return 0;
}
