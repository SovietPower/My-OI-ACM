/*
62ms	101900KB
$Description$
给定$n,r,s$，表示有$n$个人，设每个人的得分是非负整数$a_i$，已知第一个人的得分$a_1\geq r$，所有人的得分之和$\sum a_i=s$。得分最高的一个人获胜；若有多个人得分最高，则随机一个人获胜。
求在所有可能情况下，第一个人获胜的概率。
$n\leq100,\ 0\leq r\leq s\leq5000$。

$Solution$
范围不是很大，先考虑枚举第一个人的得分$x$。
然后枚举有$i$个人的得分和第一个人相同。这里计算的时候不妨算上第一个人。
现在我们已知有$i$个人得分为$x$，要求剩下$n-i$个人的分数和$\sum a_j\leq s-i\times x$，且$a_j<x$。
如果没有上界限制，就是经典的组合问题（方程非负整数解数）。
对于上界的限制，考虑容斥，枚举有多少人分数达到$x$。即$$\sum_{j=0}^{n-i}(-1)^jC_{n-i}^jf(n-i,s-(i+j)\times x)$$

其中$f(n,m)$是$\sum_{i=1}^na_i=m$的非负整数解数，即$C_{n+m-1}^{m}$。
总起来答案就是$$\sum_{x=r}^s\sum_{i=1}^n\frac{C_{n-1}^{i-1}}{i}\sum_{j=0}^{n-i}(-1)^jC_{n-i}^jC_{n-i+s-(i+j)x-1}^{n-i-1}$$

最后再除个总方案数$f(n,s-r)$。
复杂度$O(n^2s)$。
*/
#include <cstdio>
#include <algorithm>
#define mod 998244353
#define Mod(x) x>=mod&&(x-=mod)
typedef long long LL;
const int N=5107;

int inv[105],C[N][N];

inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%mod)
		if(k&1) t=1ll*t*x%mod;
	return t;
}
inline void Init(int n,int s)
{
	C[0][0]=1;
	for(int i=1; i<=s; ++i)
	{
		C[i][0]=C[i][i]=1;
		for(int j=1; j<i; ++j) C[i][j]=C[i-1][j-1]+C[i-1][j], Mod(C[i][j]);
	}
	inv[1]=1;
	for(int i=2; i<=n; ++i) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
}

int main()
{
	int n,s,r; scanf("%d%d%d",&n,&s,&r);
	Init(n,n+s);
	LL ans=0;
	for(int x=r; x<=s; ++x)
		for(int i=1; i<=n; ++i)
		{
			if(i==n)
			{
				ans+=(x*n==s)*inv[n];
				continue;
			}
			if(i*x+(n-i)*(x-1)<s||i*x>s) continue;//可有的剪枝，算出来一定是0.
			LL tmp=0;
			for(int j=0; j<=n-i&&(i+j)*x<=s; ++j)
			{
				#define v 1ll*C[n-i][j]*C[n-i-1+s-(i+j)*x][n-i-1]%mod
				tmp+=j&1?mod-v:v;
			}
			ans+=tmp%mod*C[n-1][i-1]%mod*inv[i]%mod;
		}
	printf("%I64d\n",ans%mod*FP(C[n+s-r-1][n-1],mod-2)%mod);

	return 0;
}
