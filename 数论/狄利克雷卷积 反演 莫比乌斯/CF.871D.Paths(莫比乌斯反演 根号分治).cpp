/*
296ms	161300KB
$Description$
给定$n$，表示有一张$n$个点的无向图，两个点$x,y$之间有权值为$1$的边当且仅当$\gcd(x,y)\neq1$。求$1\sim n$任意两点之间的最短路长度的和是多少。两个点不连通最短路长度为$0$。
$n\leq10^7$。
$Solution$
具体看[这里](https://www.cnblogs.com/bestFy/p/10423989.html)吧，前面也挺重要的我~~不抄了~~就简单记一下了。
先分类讨论一下，然后记$mn_x$为$x$的最小质因子，主要的问题在于求：$$\sum_{x,y}[\gcd(x,y)=1][mn_x\times mn_y\leq n]$$

反演一下（当然下面这个式子求出来要除以$2$）：$$\begin{aligned}上式&=\sum_{d=1}^n\mu(d)\sum_{d\mid x}\sum_{d\mid y}[mn_x\times mn_y\leq n]\\&=\sum_{x=1}^n\sum_{y=1}^n[mn_x\times mn_y\leq n]+\sum_{d=2}^n\mu(d)\sum_{d|x}\sum_{d|y}[mn_x\times mn_y\leq n]\end{aligned}$$

前面部分可以直接拿个桶然后前缀和一下。对于后面的部分，我们考虑：
1. $d\leq\sqrt n$时，因为$d\mid x$，所以有$mn_x\leq mn_d$，即一定有$mn_x\times mn_y\leq n$。那么合法方案数是$\lfloor\frac nd\rfloor^2$。
2. $d>\sqrt n$时，设$x=k_1d,y=k_2d$，那么有$k_1,k_2\leq\sqrt n$。$k_1,k_2\neq1$时，$k_1\times k_2\leq n$显然合法。
$k$有一个是$1$时，假设是$k_2$，$mn_x\times mn_y$就是$k_1d=x$，显然也是$\leq n$。
$k_1=k_2=1$时，若$d$不是质数，那么$d$一定存在一个因子$\leq\sqrt n$，那么也有$mn_x\times mn_y=mn_d^2\leq n$。
所以当且仅当$k_1=k_2=1$且$d$为质数时，$(x,y)$不合法。那么合法方案数就是$\lfloor\frac nd\rfloor^2$-1。

那么枚举$d$就可以求出答案啦。
*/
#include <cmath>
#include <cstdio>
#include <algorithm>
typedef long long LL;
const int N=1e7+5;

int P[N>>3],phi[N],mu[N],mn[N],cnt[N];

void Init(const int n)
{
	phi[1]=mu[1]=1;
	for(int i=2,cnt=0; i<=n; ++i)
	{
		if(!mn[i]) P[++cnt]=mn[i]=i, phi[i]=i-1, mu[i]=-1;
		for(int j=1,v; j<=cnt&&(v=i*P[j])<=n; ++j)
		{
			mn[v]=P[j];
			if(i%P[j]) phi[v]=phi[i]*(P[j]-1), mu[v]=-mu[i];
			else {phi[v]=phi[i]*P[j], mu[v]=0; break;}
		}
	}
}

int main()
{
	int n; scanf("%d",&n); Init(n);
	LL ans=0,t2=0,t3=0,tot=0;
	for(int i=2,half=n>>1; i<=n; ++i) if(mn[i]!=i||i<=half) ++tot, t2+=i-1-phi[i], ++cnt[mn[i]];
	tot=tot*(tot-1)>>1;//总合法对数 
	for(int i=2; i<=n; ++i) cnt[i]+=cnt[i-1];
	for(int i=2,half=n>>1; i<=n; ++i) if(mn[i]!=i||i<=half) t3+=cnt[n/mn[i]];
	for(int d=2,m=sqrt(n); d<=n; ++d)
	{
		LL tmp=1ll*(n/d)*(n/d);
		if(d>m&&mn[d]==d) --tmp;
		t3+=mu[d]*tmp;
	}
	t3>>=1, ans+=t2+(t3<<1)+(tot-t2-t3)*3;
	printf("%I64d\n",ans);

	return 0;
}
