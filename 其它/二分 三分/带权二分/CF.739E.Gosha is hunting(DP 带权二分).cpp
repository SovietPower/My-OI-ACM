/*
46ms    0KB
$Description$
有$n$只精灵，两种精灵球（高级和低级），每种球能捕捉到第$i$只精灵的概率已知。求用$A$个低级球和$B$个高级球能捕捉到精灵数的最大期望。
$n\leq10^5$。
$Solution$
设$f[i][a][b]$表示前$i$只用了$a$个低级球，$b$个高级球的最大期望。转移时四种情况显然。复杂度$\mathcal O(nAB)$。
随着某种球可使用数的增多，f应是凸函数，即增长越来越慢。而且两种球都满足这个性质。
于是可以wqs二分套wqs二分了。。
没有个数限制的话，取个$\max$，记一下个数就可以了。复杂度$\mathcal O(nlog^2n)$。

误差$\leq 10^{-4}$，因为最后要$*A/B$，所以$eps$应是$10^{-8}$...？

~~最后必须取$r$感觉不太懂。。~~
**[Update] 19.2.11**
二分的时候只要保证恰好取到$k$个就可以了，斜率具体是多少无所谓。而本题$r$才是正确的位置...
应该是这么理解吧...

**总结：对于有着次数/段数之类的限制，可以使用带权二分来消掉这一限制，从而可以进行简单的快速DP。**
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define eps (1e-12)
const int N=2003;

int n,A,B,na[N],nb[N];
double pa[N],pb[N],Ans;

void Solve(double ca,double cb)
{
	na[0]=nb[0]=0;
	double las=0, now;
	for(int i=1; i<=n; ++i, las=now)
	{
		now=las, na[i]=na[i-1], nb[i]=nb[i-1];
		if(las+pa[i]-ca>now) now=las+pa[i]-ca, na[i]=na[i-1]+1;
		if(las+pb[i]-cb>now) now=las+pb[i]-cb, nb[i]=nb[i-1]+1, na[i]=na[i-1];
		if(las+pa[i]+pb[i]-pa[i]*pb[i]-ca-cb>now)//1-(1-pa)(1-pb)
			now=las+pa[i]+pb[i]-pa[i]*pb[i]-ca-cb, na[i]=na[i-1]+1, nb[i]=nb[i-1]+1;
	}
	Ans=now;
}

int main()
{
	scanf("%d%d%d",&n,&A,&B);
	for(int i=1; i<=n; ++i) scanf("%lf",&pa[i]);
	for(int i=1; i<=n; ++i) scanf("%lf",&pb[i]);
	double l1=0,r1=1,mid1,l2,r2,mid2;//每个球0/1的权值就可以了啊 
	while(r1>=l1+eps)
	{
		mid1=(l1+r1)*0.5;
		l2=0, r2=1;
		while(r2>=l2+eps)
		{
			if(Solve(mid1,mid2=(l2+r2)*0.5),nb[n]>B) l2=mid2;
			else r2=mid2;
		}
		if(Solve(mid1,r2),na[n]>A) l1=mid1;//最优可行的是r2？反正不是l2。。
		else r1=mid1;
	}
	Solve(r1,r2);//最后Check一遍r。。
	printf("%.5lf",Ans+A*r1+B*r2);

	return 0;
}
