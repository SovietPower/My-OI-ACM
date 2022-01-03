/*
27452kb	5284ms
比较裸的状压DP。
刚开始写麻烦惹...
$f[i][s]$表示考虑了前$i$家商店，所买物品状态为$s$的最小花费。
可以写求一遍一定去$i$商店的$f[i]$（$f[i][s]=f[i-1][s]+dis[i]$），然后再和不去$i$商店的$f[i-1]$取个$\min$。
复杂度是$O(nm2^m)$吗...

可以优化，处理$f[s]$表示在某家商店买$s$集合的物品的最小代价。然后令$g[s]$表示考虑所有商店买$s$集合的最小代价，有$g[s]=\min(f[s],g[s']+f[s\ \text{xor}\ s'])$。
复杂度$O(n2^m+3^m)$。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define lb(x) (x&-x)
#define gc() getchar()
typedef long long LL;
const int N=103,M=16;

int dis[N],cost[N][M+1],f[N][(1<<M)+1],ref[(1<<M)+1];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	int n=read(),m=read(),lim=(1<<m)-1;
	for(int i=0; i<m; ++i) ref[1<<i]=i;
	for(int i=1; i<=n; ++i)
		for(int j=(dis[i]=read(),0); j<m; ++j) cost[i][j]=read();
	memset(f,0x3f,sizeof f), f[0][0]=0;
	for(int i=1; i<=n; ++i)
	{
		for(int s=0; s<=lim; ++s) f[i][s]=f[i-1][s]+dis[i];
		for(int s=0; s<lim; ++s)
		{
			for(int ss=s^lim,j; ss; ss^=lb(ss))
			{
				j=ref[lb(ss)];
				f[i][s|(1<<j)]=std::min(f[i][s|(1<<j)],f[i][s]+cost[i][j]);
			}
		}
		for(int s=0; s<=lim; ++s) f[i][s]=std::min(f[i][s],f[i-1][s]);
	}
	printf("%d\n",f[n][lim]);

	return 0;
}
