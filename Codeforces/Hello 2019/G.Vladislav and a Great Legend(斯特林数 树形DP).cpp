/*
467ms	90200KB
$Description$
给定一棵$n$个点的树和正整数$k$，定义$f(s)$表示使点集$s$中的点连通所需的最少边数。求$\sum_{s\neq\varnothing}f(s)^k$。
$n\leq10^5,\ k\leq200$。

$Solution$
依旧套路，把$f(s)^k$用第二类斯特林数（$m^n=\sum_{k=0}^mC_m^kS(n,k)k!$）展开：
$$\begin{aligned}Ans&=\sum_{s\neq\varnothing}\sum_{i=0}^kC_{f(s)}^iS(k,i)i!\\&=\sum_{i=0}^kS(k,i)i!\sum_{s\neq\varnothing}C_{f(s)}^i\end{aligned}$$

后面的$\sum_{s\neq\varnothing}C_{f(s)}^i$实际就是任选$i$条边，对应多少个点集。考虑树DP去算。
令$f[i][j]$表示选中的所有点的$LCA$为$i$时，从这些生成树中选了$j$条边对应的点集有多少个（生成树包括$i\to fa[i]$这条边，因为不在这个时候计算这条边好像不好做...表示不会）。
每个点初始化$f[x][0]=2$（可以在也可以不在点集中）。合并子树的时候就是树形背包，$f'[x][i+j]=\sum_{v=son[x]}f[x][i]*f[v][j]$。
合并完子树的贡献后，再算上$x\to fa[x]$这条边的贡献（可能出现在边集中），即$f[x][i]$+=$f[x][i-1]$。
此时会有不合法的情况：$x$子树外没有选点，但选了$x\to fa[x]$这条边。
减去合并完子树后时的$f$的贡献就行了，即$Ans_i$-=$f[x][i-1]$。
还有要注意$f[x][0]$是包括空集这一种情况的（不选任何点），但是又不能直接去掉（直接--$f[x][0]$），组合的时候可能用到。
所以在用$f[x][0]$更新其它值时注意把这种情况去掉：$Ans_1$再加上这个$1$，用$x\to fa[x]$的边更新后的$f[x][1]$要减掉这个$1$。

还可以把$i!$乘进去，就成了[维护下降幂](https://blog.csdn.net/Dream_Lolita/article/details/86428795)。。不想看了。。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define mod 1000000007
#define gc() getchar()
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
typedef long long LL;
const int N=1e5+5;

int K,Enum,H[N],nxt[N<<1],to[N<<1],f[N][203],Ans[N];

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
void DFS(int x,int fa)
{
	static int sz[N],g[N];
	f[x][0]=2, sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa)
		{
			DFS(v,x);
			for(int a=0,l=std::min(sz[x]-1,K); a<=l; ++a)
				for(int b=0; b<=sz[v]&&a+b<=K; ++b)//注意这里不是到sz[v]-1（还有v->fa[v]这条边）
					Add(g[a+b],1ll*f[x][a]*f[v][b]%mod);
			sz[x]+=sz[v];
			for(int j=0,l=std::min(sz[x]-1,K); j<=l; ++j) f[x][j]=g[j], g[j]=0;
		}
	if(x!=1)
	{
		for(int i=1,l=std::min(sz[x],K); i<=l; ++i) Add(Ans[i],mod-f[x][i-1]);//注意这里也不是sz[x]-1。。（不写这个取min更保险一些）
		++Ans[1];
	}
	else for(int i=0,l=std::min(sz[1]-1,K); i<=K; ++i) Add(Ans[i],f[1][i]);
	for(int i=std::min(sz[x],K); i; --i) Add(f[x][i],f[x][i-1]);
	Add(f[x][1],mod-1);
}

int main()
{
	static int S[203][203];
	const int n=read(),K=read(); ::K=K;
	for(int i=1; i<n; ++i) AE(read(),read());
	DFS(1,1);
	S[0][0]=1;
	for(int i=1; i<=K; ++i)
		for(int j=1; j<=i; ++j) S[i][j]=S[i-1][j-1]+1ll*S[i-1][j]*j%mod, Mod(S[i][j]);
	LL ans=0;
	for(int i=0,fac=1; i<=K; ++i) ans+=1ll*S[K][i]*fac%mod*Ans[i]%mod, fac=1ll*fac*(i+1)%mod;
	printf("%I64d\n",ans%mod);

	return 0;
}
