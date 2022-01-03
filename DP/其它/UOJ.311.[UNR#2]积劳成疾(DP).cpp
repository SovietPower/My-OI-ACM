/*
1447ms	2052kb
序列中的每个位置是等价的。直接令$f[i][j]$表示，$i$个数的序列，最大值不超过$j$的所有序列每个长为$k$的子区间最大值的乘积的和。
由$j-1$转移到$j$时，考虑枚举第一个$j$出现在哪里。设最左边的$j$在$p$位置，那么会对左端点在$[\max(1,p-k+1),\ \min(p,i-k+1)]$的每个$k$区间造成$w[j]$的贡献，也就是$w[j]^{len}$。$p$左边没出现过$j$，贡献是$f[p-1][j-1]$；$p$右边还可能出现$j$，贡献是$f[i-p][j]$。
所以有$f[i][j]=f[i][j-1]+\sum_{p=1}^{i}f[p-1][j-1]*w[j]^{len}*f[i-p][j]$。
注意初始化的问题，$f[i][j]\ (i<k)$的初值是$j^i$，即序列个数。（这样$i\geq k$的时候是会考虑序列所有构成的）
复杂度$O(n^3)$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define mod 998244353
#define gc() getchar()
typedef long long LL;
const int N=505;
const LL LIM=1ll<<61;

int pw[N][N],f[N][N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%mod) k&1&&(t=1ll*x*t%mod);
	return t;
}

int main()
{
	const int n=read(),K=read();
	for(int i=1; i<=n; ++i)
	{
		int w=read(); pw[i][0]=1;
		for(int j=1,wn=w; j<=n; ++j,w=1ll*w*wn%mod) pw[i][j]=w;
	}
	for(int i=0; i<=n; ++i) f[0][i]=1;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			if(i<K) f[i][j]=FP(j,i);
			else
			{
				LL tmp=f[i][j-1];
				for(int p=1; p<=i; ++p)
					tmp+=1ll*f[p-1][j-1]*f[i-p][j]%mod*pw[j][std::min(p,i-K+1)-std::max(1,p-K+1)+1], tmp>=LIM&&(tmp%=mod);
				f[i][j]=tmp%mod;
			}
	printf("%d\n",f[n][n]);

	return 0;
}
