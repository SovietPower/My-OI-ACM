/*
$Description$
每个点有费用si与价值pi，要求选一些带根的连通块，总大小为k，使得(∑pi)/(∑si)最大	 
$Solution$
01分数规划，然后dp，设f[i][j]表示i子树选j个的最大权值和，直接暴力背包转移即可 
在枚举子节点选的数量时，假设x有1.2.3.4四个子节点，复杂度为1*sz[1]+sz[1]*sz[2]+(sz[1]+sz[2])*sz[3]+(sz[1]+sz[2]+sz[3])*sz[4] 
相当于每对点在LCA处有贡献，共会有n^2个LCA，所以这部分复杂度为O(n^2)
总O(n^2*log ans)
注: 很多初始值不要是0，因为会有较大负数。比如说 必须规定f[0][1]为-INF 
eps为什么需要1e-5。。<1e-4结束不行吗(也许是这并不是精确答案？~~卡时大法好~~) 
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=2505;
const double eps=1e-5,INF=1e10;

int n,m,Enum,H[N],nxt[N],to[N],sz[N];
double cost[N],p[N],val[N],f[N][N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
void DFS(int x)
{
	int mn=(x>0); sz[x]=mn;
	for(int i=2; i<=m; ++i) f[x][i]=-INF;
	f[x][1]=val[x];
	for(int v,i=H[x]; i; i=nxt[i])
	{
		DFS(v=to[i]);
		for(int j=sz[x]; j>=mn; --j)//倒序 //更新上限就是当前已有sz与子节点sz之和 
			for(int k=1; k<=sz[v]; ++k)
				f[x][j+k]=std::max(f[x][j+k],f[x][j]+f[v][k]);
		sz[x]+=sz[v];
	}
}
double Solve(double x)
{
	for(int i=1; i<=n; ++i) val[i]=p[i]-x*cost[i];
//	memset(f,0xc2,sizeof f), f[0][0]=0;//too slow
	DFS(0);
	return f[0][m]>=0;
}

int main()
{
	m=read(), n=read();
	for(int i=1; i<=n; ++i)
		cost[i]=read(),p[i]=read(),AddEdge(read(),i);
	double l=0.0,r=1e4,mid; val[0]=-INF;//f[0][1]
	while(r-l>eps)
	{
		if(Solve(mid=(l+r)/2.0)) l=mid;
		else r=mid;
	}
	printf("%.3lf",mid);

	return 0;
}
