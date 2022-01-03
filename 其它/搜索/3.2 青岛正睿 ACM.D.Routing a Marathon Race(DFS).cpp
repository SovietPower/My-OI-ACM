/*
1ms 2704kb
$Description$
给定一张$n$个点$m$条边的无向图，每个点有一个权值。求一条从$1$到$n$的路径，使得代价最小，输出最小代价。
一条路径的代价定义为，路径上所有点以及和这些点相邻的所有点的权值和。
$n\leq40,\ m\leq\frac{n(n-1)}{2}$。
$Solution$
容易发现，如果选择从$u$走到$v$，那么一定不会再回到$u$的其它相邻节点（不如直接走过去）。
这样从点$u$爆搜的话，每次移动都会删掉$dgr_u$个点。
那么复杂度是：$T(n)=c\times T(n-c)$，最差情况下是$c=3$，复杂度约是$3^{\frac n3}$。
注意边数是$N\times N$啊不除$2$！！！（mdzz）
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=45,M=N*N;

int n,Ans,Enum,H[N],nxt[M],to[M],A[N],ban[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS(int x,int cost)
{
	if(x==n)
	{
		for(int i=H[x]; i; i=nxt[i]) !ban[to[i]]&&(cost+=A[to[i]]);//!
		Ans=std::min(Ans,cost);
		return;
	}
	for(int i=H[x]; i; i=nxt[i]) !ban[to[i]]&&(cost+=A[to[i]]), ++ban[to[i]];
	for(int i=H[x]; i; i=nxt[i]) if(ban[to[i]]==1) DFS(to[i],cost);
	for(int i=H[x]; i; i=nxt[i]) --ban[to[i]];
}

int main()
{
	int n=read(),m=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<=m; ++i) AE(read(),read());
	::n=n, Ans=2e9, ban[1]=1, DFS(1,A[1]), printf("%d\n",Ans);

	return 0;
}
