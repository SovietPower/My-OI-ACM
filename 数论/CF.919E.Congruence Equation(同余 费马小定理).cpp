/*
608ms	1828KB
$Description$
给定a,b,x,p，求[1,x]中满足n*a^n ≡b (mod p) 的n的个数。1<=a,b<p, p<=1e6+3, x<=10^{12}.
$Solution$
边界很大，p比较小且为质数，考虑左边这个式子有没有循环节。
由费马小定理 a^{p-1} ≡a^0 ≡1(mod p)，a^n的循环节(一定)为p-1；n%p 的循环节(一定)为p 
所以 n*a^n 一定有长为p(p-1)的循环节 
设n=k(p-1)+y，那么n*a^n ≡[k(p-1)+y]*a^{k(p-1)+y} ≡[k(p-1)+y]*a^y (mod p)
于是原来式子可以化成求n满足 k(p-1)+y ≡y-k ≡b*a^{-y} (mod p)
那么 k ≡y-b*a^{-y} (mod p)(那么满足条件的最小的k就是右式的值)
此时1<=y<p，于是我们可以枚举y得到一个k，然后就有了一个n=k(p-1)+y。
因为循环节长度是p(p-1)，所以只需要算在上界内还有多少个p(p-1)即可 
*/
#include <cstdio>
typedef long long LL;

LL a,b,p,x;

LL FP(LL x,int k)
{
	LL t=1;
	for(; k; k>>=1,x=x*x%p)
		if(k&1) t=t*x%p;
	return t;
}
LL inv(LL x){
	return FP(x,p-2);
}

int main()
{
	scanf("%I64d%I64d%I64d%I64d",&a,&b,&p,&x);
	LL res=0,P=p*(p-1);
	for(int y=1; y<p; ++y)
	{
		LL k=(y-b*inv(FP(a,y))%p+p)%p;
		LL n=(p-1)*k+y;//注意这步不要取模 
		if(n<=x) res+=(x-n)/P+1;
	}
	printf("%I64d",res);

	return 0;
}
