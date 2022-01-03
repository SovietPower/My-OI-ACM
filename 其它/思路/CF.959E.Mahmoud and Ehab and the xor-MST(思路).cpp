/*
### $Description$
有一张$n$个点的完全图，从$0$到$n-1$标号，每两点$i,j$间的边权为$i\oplus j$。求其最小生成树边权之和。
### $Solution$
为方便，以下点从$0$到$n$编号。
每个点$x$应和$x\oplus lowbit(x)$相连，边权为$lowbit(x)$（$lowbit(x)$会和$0$相连，所以一定能构成树），所以答案为$\sum_{i=1}^nlb(i)$。
继续优化。注意到$lb(i)$一定是某个2次幂，所以令$f(i)$表示$1\leq x\leq n$且满足$lb(x)=i$的$x$的个数，则答案为$\sum_{i=1}^nf(i)\times i\ (f(i)>0)=\sum_{i=0}^{\lfloor\log n\rfloor}f(2^i)\times 2^i$
$f(i)$显然可以用数位DP算，但是太麻烦了。。
一些满足$lb(i)=x$的数，它们间隔至少是$2x$。比如$x=(100)_2$，则$i=100,1100,10100...$(相差$1000$)。所以$f(x)=\lfloor\frac{n-x}{2x}\rfloor+1\ (1\leq x\leq n,x=2^y)$。
还有DP做法，好长啊...先不看了。
*/
#include <cstdio>

int main()
{
	long long n,res=0;
	scanf("%I64d",&n); --n;
	for(long long x=1; x<=n; x<<=1)
		res+=x*((n-x)/(x<<1)+1);
	printf("%I64d\n",res);

	return 0;
}
