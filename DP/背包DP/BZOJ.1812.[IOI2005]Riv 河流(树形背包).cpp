/*
868kb	36ms
这个数据范围。。考虑暴力一些把各种信息都记下来。不妨直接令$f[i][j][k][0/1]$表示当前为点$i$，离$i$最近的建了伐木场的$i$的祖先为$j$，$i$及$i$子树一共建了$k$个伐木场。$0/1$表示点$i$是否建了伐木场。
发现对于$i$的子树里的点$v$，$v$建没建伐木场无所谓，需要的是它建了多少。所以DP完$i$后，$i$只保留$f[i]...[0/1]$中较小的一个作为点$i$的答案即可。
转移就是背包，暴力些即可。复杂度$O(n^2k^2)$。
既然都这么暴力地记录祖先了，不妨转移$f[i]$的时候直接DFS一遍子树（强制$i$选）。即令$f[i][j]$表示$i$子树共用$j$个伐木场的最小代价。这样虽然复杂度还是$O(n^2k^2)$，但只需要二维的DP数组。
另外DP完当前点$i$后，是保留强制选$i$的DP值（不选$i$的也没法求啊）；从其它点转移的时候，就无所谓取不取了。
为了方便，可以令$f$表示最大贡献（与到根节点相比少花多少代价）啊。
感觉还是有点迷...
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=105,INF=2e9;

int K,w[N],dep[N],sz[N],H[N],nxt[N],f[N][55],g[N][55];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v)
{
	nxt[v]=H[u], H[u]=v;
}
void DP(int x,int dep_anc)
{
	f[x][0]=dep_anc*w[x];
	for(int v=H[x]; v; v=nxt[v])
	{
		DP(v,dep_anc);
		for(int i=std::min(sz[x],K); ~i; --i)
			for(int j=0; j<=std::min(sz[v],i); ++j)
				f[x][i]=std::max(f[x][i],f[x][i-j]+f[v][j]);
	}
	for(int i=1; i<=K; ++i) f[x][i]=std::max(f[x][i],g[x][i]);//g[x][0]=0 (meaningless)
}
void DFS(int x)
{
	sz[x]=1;
	for(int v=H[x]; v; v=nxt[v]) dep[v]+=dep[x], DFS(v), sz[x]+=sz[v];
	memset(f,0,sizeof f);
	for(int v=H[x]; v; v=nxt[v])
	{
		DP(v,dep[x]);
		for(int i=std::min(sz[x],K); ~i; --i)
			for(int j=0; j<=std::min(sz[v],i); ++j)
				g[x][i]=std::max(g[x][i],g[x][i-j]+f[v][j]);
	}
	if(x) for(int i=K,v=dep[x]*w[x]; i; --i) g[x][i]=g[x][i-1]+v;//在此之前未算入x（当然0本身不用算入）
//	g[x][0]=0;
}

int main()
{
	int n=read(); K=read();
	for(int i=1; i<=n; ++i) w[i]=read(),AE(read(),i),dep[i]=read();
	DFS(0);
	int ans=0,tmp=0;
	for(int i=0; i<=K; ++i) tmp=std::max(tmp,g[0][i]);
	for(int i=1; i<=n; ++i) ans+=dep[i]*w[i];
	printf("%d\n",ans-tmp);

	return 0;
}
