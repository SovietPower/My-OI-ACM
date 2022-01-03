/*
题目看似要求$$\sum_{k=1}^n\sum_{a=1}^k\sum_{b=1}^k[k\mid a\times b]$$
实际我们可以求$$\sum_{k=1}^n\sum_a\sum_b\sum_c[a\times b\times c=k]$$
再实际就是求$$\sum_a\sum_b\sum_c[a\times b\times c\leq k]$$
也就是$a\times b\times c\leq k$的有序三元组个数。。
那么我们枚举$a\leq b\leq c$，统计它有多少个，最后再乘排列数。
这样$a$只需枚举到$\sqrt[3]n$，$b$需要枚举到$\sqrt{\frac na}$。
$a=b=c$时排列数只有$1$，有两个数相等时排列数只有$3$，其它的就乘$3!=6$。
*/
#include <cmath>
#include <cstdio>
#define mod 2333
typedef long long LL;

int main()
{
	LL n; scanf("%lld",&n);
	int ans=0;
	for(int a=1; 1ll*a*a*a<=n; ++a)
	{
		ans=(ans+1+3*(n/a/a-a))%mod;
		LL t=n/a;
		for(int b=a+1,l=sqrt(t); b<=l; ++b)
			ans=(ans+3/*每个枚举的b,c都可以等于b*/+6*(t/b-b))%mod;
	}
	printf("%d\n",ans%mod);

	return 0;
}
