/*
1308kb	2148ms
题意即求第$k$个无平方因子数。
> 无平方因子数(Square-Free Number)，即分解之后所有质因数的次数都为1的数

可以想到莫比乌斯函数，假设$n$是答案，那么有$$k=n-\sum_{i=1}^n(1-|\mu(i)|)$$
（从这里能看出$x$的上界，后面的$\sum$肯定是$<\frac{n}{2}$的，所以$n\leq 2*k$）
二分一个$n$，求$[1,n]$中有多少个无平方因子数。
既然带着个平方就都开方。根据容斥，对于$[1,\sqrt{n}]$中的质数，答案为$$[1,n]中0个质数平方倍数的个数-1个质数平方倍数的个数+2个质数平方倍数的个数-\ldots$$
即对于奇数个质数平方贡献为负，偶数个贡献为正；若存在某个质因子的次数$>1$，那么对答案没有影响(如$pi^2*pj^2$在计算$pi*pj$时统计了个数)。这也符合莫比乌斯函数的特点。那么答案可以写为：$$\sum_{i=1}^{\lfloor\sqrt{n}\rfloor}\mu(i)*\lfloor\frac{n}{i^2}\rfloor$$
$r$最大是$2e9$，所以$l+r$可能爆int！
*/
#include <cmath>
#include <cstdio>
const int N=5e4;//50000不行？

int cnt,P[10005],mu[N+3],pw[N+3];
bool Not_P[N+3];

void Init()
{
	mu[1]=1;
	for(int i=2; i<N; ++i)
	{
		if(!Not_P[i]) P[++cnt]=i,mu[i]=-1;
		for(int j=1; j<=cnt&&i*P[j]<N; ++j)
		{
			Not_P[i*P[j]]=1;
			if(i%P[j]) mu[i*P[j]]=-mu[i];
			else {mu[i*P[j]]=0; break;}
		}
	}
	for(int i=1; i<N; ++i) pw[i]=i*i;
}
bool Check(long long n,int K)
{
	int res=0;//res=n
	for(int i=1,lim=sqrt(n); i<=lim; ++i)
		if(mu[i]/*这个?*/) res+=mu[i]*(n/pw[i]);
	return res>=K;
}

int main()
{
	Init();
	int T,K; scanf("%d",&T);
	long long l,r,mid;//!
	while(T--)
	{
		scanf("%d",&K), l=1, r=K<<1;
		while(l<r)
			if(Check(mid=(l+r)>>1,K)) r=mid;
			else l=mid+1;
		printf("%lld\n",l);
	}
	return 0;
}
