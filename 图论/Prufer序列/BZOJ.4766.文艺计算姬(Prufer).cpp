/*
820kb	0ms
$Description$
给定两边点数分别为$n,m$共有$n\times m$条边的完全二分图，求其生成树个数模$p$。
$n,m,p\leq 10^{18}$。
$Solution$
这是完全二分图，那么在构造Prufer序列时，最后会剩下两个点，两点的边是连接两个集合的，这两个点自然分属两个集合 
那么集合A被删了m-1次，每次从n个点中选；B被删了n-1次，每次都可以从m个点中选。so ans = n^{m-1}*m^{n-1} 
答案可以根据相对顺序直接构造 
*/
#include <cstdio>
typedef long long LL;
LL n,m,p;

LL Mult(LL a,LL b)
{
	LL tmp=a*b-(LL)((long double)a/p*b+1e-8)*p;
	return tmp<0?tmp+p:tmp;
}
LL FP(LL x,LL k)
{
	LL t=1;
	for(; k; k>>=1,x=Mult(x,x))
		if(k&1) t=Mult(t,x);
	return t;
}

int main()
{
	scanf("%lld%lld%lld",&n,&m,&p);
	printf("%lld",Mult(FP(n,m-1),FP(m,n-1)));
	return 0;
}
