/*
20ms	256KB
$Description$
给定$n,k$，求 满足对于所有$i$，$|a_i-i|\neq k$的排列的个数。
$2\leq n\leq 2000,\quad 1\leq k\leq n-1$。
$Solution$
容斥。则$Ans=\sum_{i=0}^n(-1)^ig(i)(n-i)!$，其中$g(i)$为至少有$i$个位置满足$|a_i-i|=k$的排列数。
考虑如何计算$g(x)$。每个$i$向$i+k$和$i-k$连边，可以得到一张二分图，$g(x)$就是在这张二分图上选$x$个匹配的方案数。
我们还可以发现，图中的匹配形成了$2k$条互不相交的链，且每条链上的数模$k$相同（也就是模$k$不同的数是互不影响的，所以枚举模数就可以得到所有链了）。
如果只有一条长$l$的链，那么就是对$l-1$个点DP，$f[i][j][0/1]$表示当前第$i$个点，已经选了$j$个匹配，这个点选不选（这个点选要求上一个点没选）。
对于$2k$条链也是一样的，只要在链之间加一个点，并强制它不能选（$f[i][j][1]=0$），就可以把这些链合在一起DP啦。
这样复杂度$O(n^2)$，然而好多dalao用NTT$n\log n$过掉了orz。
*/
#include <cstdio>
#include <algorithm>
#define mod 924844033
typedef long long LL;
const int N=4005;//2n

int ban[N],f[2][N][2],fac[N];

int main()
{
	int n,K,cnt=0; scanf("%d%d",&n,&K);
	for(int i=1; i<=K; ++i)
	{
		ban[++cnt]=1;
		for(int j=i+K; j<=n; j+=K) ban[++cnt]=0;
		ban[++cnt]=1;//就是两条链啊 
		for(int j=i+K; j<=n; j+=K) ban[++cnt]=0;
	}
	int p=0; f[p][0][0]=1;
	for(int i=0; i<cnt; ++i,p^=1)
		for(int j=0; j<=i; ++j)
		{
			f[p^1][j][0]=(f[p][j][0]+f[p][j][1])%mod;
			if(!ban[i+1]) f[p^1][j+1][1]=f[p][j][0];
			f[p][j][0]=f[p][j][1]=0;
		}
	fac[0]=1;
	for(int i=1; i<=n; ++i) fac[i]=1ll*fac[i-1]*i%mod;
	LL ans=0;
	for(int i=0; i<=n; ++i)
		ans+=i&1?mod-1ll*fac[n-i]*(f[p][i][0]+f[p][i][1])%mod:1ll*fac[n-i]*(f[p][i][0]+f[p][i][1])%mod;
	printf("%lld\n",ans%mod);

	return 0;
}
