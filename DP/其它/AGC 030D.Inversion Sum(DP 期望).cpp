/*
310ms	35456KB
$Description$
给定长为$n$的序列$A_i$和$q$次操作$(x,y)$。对于每次操作$(x,y)$，可以选择交换$A_x,A_y$两个数，也可以选择不进行操作。求所有$2^q$种情况中，逆序对个数之和。
$n,q\leq3000$。
$Solution$
不去直接求和，我们求$q$次操作后逆序对的期望个数。这样乘上$2^q$就是答案。
可以令$f[t][i][j]$表示，$t$次操作后，$A_i<A_j$的概率。
$f[0][i][j]$可以由初始序列得到，然后可以从$f[t-1][i][j]$转移到$f[t][i][j]$，但这样好像是$O(n^2q)$的？
对于每次操作$(x,y)$，只会影响$i$或$j$等于$x$或$y$时的$f[t][i][j]$，其它的都不会变。所以只需要修改这$O(n)$个值就可以了。（比如$f[i][x]$即$a_i<a_x$的概率，现在$\frac12$会变成$a_i<a_y$的概率，即$f[i][x]=\frac{f[i][x]+f[i][y]}{2}$，$f[i][y]$同理）
复杂度$O(n^2+qn)$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define mod 1000000007
#define inv2 500000004ll
typedef long long LL;
const int N=3005;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%mod)
		if(k&1) t=1ll*t*x%mod;
	return t;
}

int main()
{
	static int A[N],f[N][N];
	const int n=read(),q=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j) f[i][j]=A[i]<A[j];
	for(int i=1; i<=q; ++i)
	{
		int x=read(),y=read();
		f[x][y]=f[y][x]=inv2*(f[x][y]+f[y][x])%mod;
		for(int j=1; j<=n; ++j)
			if(j!=x && j!=y)
				f[j][x]=f[j][y]=inv2*(f[j][x]+f[j][y])%mod,
				f[x][j]=f[y][j]=inv2*(f[x][j]+f[y][j])%mod;
	}
	LL ans=0;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<i; ++j) ans+=f[i][j];
	printf("%lld\n",ans%mod*FP(2,q)%mod);

	return 0;
}
