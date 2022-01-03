/*
101ms	97920KB
$Description$
给定一棵$n$个点的树。将这$n$个点两两配对，并对每一对点的最短路径染色。求有多少种配对方案使得所有边都至少被染色一次。
$n\leq5000$。
$Solution$
考虑容斥。令边集$E$的子集$S\in E$，$f(S)$表示使得$S$中所有边都不被染色的配对方案数（其余边任意），则$Ans=\sum_{S\in E}(-1)^{|S|}f(S)$。
如果确定边集$S$，我们可以求$f(S)$。设$S$将树分成了大小分别为$a_1,a_2,...,a_{|S|+1}$的连通块，则每一连通块内的点可以任意配对，$f(S)=\prod_{i=1}^{|S|+1}g(a_i)$。
$g(n)$即$n$个点两两任意配对的方案数，$g(n)=[2\mid n](n-1)\times(n-3)\times...\times3\times1=[2\mid n](n-1)!!$（双阶乘）。
考虑DP求所有$f(S)$。$f[i][j]$表示当前为$i$的子树，连通块大小为$j$的方案数。转移就是树上背包。
最后有$f[i][0]=\sum_{j=1}^{sz[i]}-1\times f[i][j]\times g(j)$。$-1$即边集$S$多了一条边，乘一个容斥系数。
复杂度$O(n^2)$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define mod 1000000007
#define Mod(x) x>=mod&&(x-=mod)
typedef long long LL;
const int N=5005;

int Enum,H[N],nxt[N<<1],to[N<<1],f[N][N],sz[N],g[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS(int x,int fa)
{
	static int tmp[N];

	sz[x]=1;
	int *fx=f[x]; fx[1]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa)
		{
			DFS(v,x);
			for(int j=0,sv=sz[v]; j<=sz[x]; ++j)
				for(int k=0; k<=sv; ++k)
					tmp[j+k]+=1ll*fx[j]*f[v][k]%mod, Mod(tmp[j+k]);
			for(int j=0,l=sz[x]+sz[v]; j<=l; ++j)
				fx[j]=tmp[j], tmp[j]=0;
			sz[x]+=sz[v];
		}
	LL t=0;
	for(int i=1; i<=sz[x]; ++i) t+=mod-1ll*fx[i]*g[i]%mod;
	fx[0]=t%mod;
}

int main()
{
	int n=read();
	for(int i=1; i<n; ++i) AE(read(),read());
	g[0]=1;
	for(int i=2; i<=n; i+=2) g[i]=1ll*g[i-2]*(i-1)%mod;
	DFS(1,1), printf("%d\n",mod-f[1][0]);

	return 0;
}
