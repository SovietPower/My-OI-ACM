/*
217ms	0KB
$Description$
给定$n,k$。每次$n$会等概率地变成自己的一个约数（包括$1,n$），求变化$k$次后$n$期望是多少。
$n\leq10^{15},\ k\leq10^4$。
$Solution$
将$n$质因数分解，$n=p_1^{a_1}p_2^{a_2}...p_k^{a_k}$，每次变化后每个质因子的次数$a_i$会随机变成$0\sim a_i$中的一个数，且每个$a_i$的变化是独立的。
所以可以对每个质因子分别计算期望，最后乘起来。
令$f[i][j]$表示$i$次变化后，$a$变成$j$的概率，$f[0][a]=1$。
转移就是$f[i][j]=\sum_{k=j}^a\frac{f[i-1][k]}{k+1}$。
把所有质因数都算一遍，乘起来就好了。
质因子个数、次数都是$\log$级别的（其实乘起来也就$\log$级别？），所以复杂度是$O(k\log^2n)$（其实也就是$O(k\log n)$？），再加上分解质因数$O(\sqrt{n})$。

我竟然把逆元求成阶乘逆元了然后调二十分钟= =我也是醉了。
*/
#include <cstdio>
#include <algorithm>
#define mod 1000000007
#define Mod(x) x>=mod&&(x-=mod)
typedef long long LL;
const int N=52;

int inv[N];

int Solve(int x,int K,int a)
{
	static int sum[N];
	for(int i=0; i<a;++i) sum[i]=0;
	sum[a]=1, sum[a+1]=0;
	for(int i=1; i<=K; ++i)
		for(int j=a; ~j; --j)
			sum[j]=sum[j+1]+1ll*sum[j]*inv[j+1]%mod, Mod(sum[j]);
	LL ans=0;
	for(int i=0,t=1; i<=a; ++i) ans+=1ll*t*sum[i]%mod, t=1ll*t*x%mod;
	return ans%mod;
}

int main()
{
	inv[1]=1;
	for(int i=2; i<N; ++i) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;

	LL n,ans=1; int K; scanf("%I64d%d",&n,&K);
	for(int i=2; 1ll*i*i<=n; ++i)//这个枚举貌似可以优化（每次+=6？）
		if(!(n%i))
		{
			int a=1; n/=i;
			while(!(n%i)) ++a, n/=i;
			ans=ans*Solve(i,K,a)%mod;
		}
	if(n!=1) ans=ans*Solve(n%mod,K,1)%mod;//n可能很大 别忘取模！
	printf("%I64d\n",ans);

	return 0;
}
