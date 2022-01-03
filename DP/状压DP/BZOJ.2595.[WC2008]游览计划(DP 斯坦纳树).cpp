/*
2080kb	148ms
$Description$
一张$n\times m$的网格，网格有权值，表示选该点的花费，求使所有$k$个权为0的点连通的最小花费。连通指存在所有点都被选的路径使其连通。输出方案。$n,m,K\leq 10$。
$Solution$
f[i][s]表示以i为根节点，当前关键点的连通状态为s(每个点是否已与i连通)时的最优解。i是枚举得到的根节点，有了根节点就容易DP了。
那么i为根节点时，其状态s的更新为 $f[i][s]=min{f[i][s']+f[i][\complement_{s}s']-cost[i]},s'\in s$（枚举子集s'后，显然只需要s'的补集。减cost[i]是因为两种状态都包含，cost[i]算重了）
如果我们想合并入当前连通块一个新的非关键点v并以v为根，那么 $f[v][s]=min{f[k][s]+cost[v]},k,v相邻$
第一个更新可以按顺序，第二个更新没有明显顺序，但是如果固定状态s，很像SPFA，可类似转移。
输出方案，可以每次转移记录转移前的点与状态s，因为可能是转移点也可能是用子集更新。最后随便找一个关键点开始DFS即可。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define En(i,j) (i*m+j)//Encode
#define De(w) mp(w/m,w%m)//Decode
#define mp std::make_pair
#define pr std::pair<int,int>
const int N=102,INF=1e9,to[5]={1,0,-1,0,1};

int n,m,cost[N],f[(1<<10)+1][N];//换下了顺序 注意!
pr pre[(1<<10)+1][N];
bool inq[N],vis[N];
std::queue<int> q;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void SPFA(int *f,pr *pre,int s)
{
	while(!q.empty())
	{
		int now=q.front();
		q.pop(), inq[now]=0;
		for(int x=now/m,y=now%m,xn,yn,nxt,i=0; i<4; ++i)
			if((xn=x+to[i])>=0&&xn<n&&(yn=y+to[i+1])>=0&&yn<m && f[nxt=En(xn,yn)]>f[now]+cost[nxt])
			{
				f[nxt]=f[now]+cost[nxt], pre[nxt]=mp(now,s);
				if(!inq[nxt]) inq[nxt]=1, q.push(nxt);
			}
	}
}
void DFS(int p,int s)
{
	if(!pre[s][p].second) return;//pre.second即 无转移了 
	vis[p]=1;
	if(pre[s][p].first==p) DFS(p,s^pre[s][p].second);
	DFS(pre[s][p].first,pre[s][p].second);
}

int main()
{
	n=read(), m=read(); int K=0, rt=0;
	memset(f,0x3f,sizeof f);
	for(int tot=0,i=0; i<n; ++i)
		for(int j=0; j<m; ++j,++tot)
		{
			cost[tot]=read();
			if(!cost[tot]) f[1<<(K++)][tot]=0, rt=tot;
		}
	for(int s=1; s<(1<<K); ++s)
	{
		for(int i=0; i<n*m; ++i)
		{
			for(int sub=(s-1)&s; sub; sub=(sub-1)&s)
				if(f[s][i]>f[sub][i]+f[sub^s][i]-cost[i])
					f[s][i]=f[sub][i]+f[sub^s][i]-cost[i], pre[s][i]=mp(i,sub);
			if(f[s][i]<INF) q.push(i), inq[i]=1;//多起点，inq[]还是不能省啊 
		}
		SPFA(f[s],pre[s],s);
	}
	printf("%d\n",f[(1<<K)-1][rt]);
	DFS(rt,(1<<K)-1);
	for(int i=0,tot=0; i<n; ++i,putchar('\n'))
		for(int j=0; j<m; ++j,++tot)
			if(!cost[tot]) putchar('x');
			else putchar(vis[tot]?'o':'_');

	return 0;
}
