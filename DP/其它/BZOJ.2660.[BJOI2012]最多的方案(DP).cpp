//https://www.cnblogs.com/SovietPower/p/9667017.html
/*
题意：给一个正整数n，它可以写成一些斐波那契数的和的形式。如果我们要求不同的方案中不能有相同的斐波那契数，那么对一个n最多可以写出多少种方案？

首先我们知道：
![1](https://img2018.cnblogs.com/blog/1143196/201809/1143196-20180918082650984-1726981287.png)
也很好理解。如果相邻两项出现在斐波那契表示法中，那它们显然可以合并。
所以我们能得到$n$的斐波那契表示，记$pos[i]$为$n$的斐波那契表示法中，第$i$项在原斐波那契的下标，那么：$n=\sum_{i=1}^{cnt}F[pos[i]]$。
如果方案中不直接存在$F[pos[i]]$（把$F[pos[i]]$分解），那它只能由$<pos[i]$的项构成。于是我们考虑递推。
$f[i][1/0]$表示当前考虑到$pos[i]$，是/否分解$F[pos[i]]$，且满足$F[pos[1]]\sim F[pos[i]]$都被组成，的方案数。

如果不分解$F[pos[i]]$，那么有$$f[i][0]=f[i-1][0]+f[i-1][1]$$，且$F[pos[i+1]]$只能由$[pos[i]+1,pos[i+1]]$之间的项得到。

如果分解$F[pos[i]]$，则$F[pos[i+1]]$可以由$[pos[i],pos[i+1]]$之间的项得到，而且若分解$F_i=F_{i-1}+F_{i-2}$，下一次只能分解$F_{i-2}=F_{i-3}+F_{i-4}$，再下一次只能分解$F_{i-4}=\ldots\ldots$。于是我们可以得到在区间$[l,r-1]$中分解$F_r$的方案数为$\frac{r-l}{2}$。
于是可以得到：$$f[i][1]=f[i-1][0]\times\frac{pos_i-pos_{i-1}-1}{2}+f[i-1][1]\times\frac{pos_i-pos_{i-1}}{2}$$

初始值就是$f[1][0]=1,f[1][1]=\frac{pos_i-1}{2}$。

另外直接map记搜也能跑得飞快（甚至比递推快smg。。）
*/
#include <cstdio>
#include <algorithm>
typedef long long LL;
const int N=100;

int p[N],f[N][2];
LL n,F[N];

int main()
{
	scanf("%lld",&n);
	F[1]=1, F[2]=2; int t,cnt=0;
	for(t=3; (F[t]=F[t-1]+F[t-2])<=n; ++t);
	for(int i=t; i; --i)
		if(n>=F[i]) n-=F[i], p[++cnt]=i;
	std::reverse(p+1,p+1+cnt);

	f[1][0]=1, f[1][1]=p[1]-1>>1;
	for(int i=2; i<=cnt; ++i)
		f[i][0]=f[i-1][0]+f[i-1][1],
		f[i][1]=f[i-1][0]*(p[i]-p[i-1]-1>>1)+f[i-1][1]*(p[i]-p[i-1]>>1);
	printf("%d\n",f[cnt][0]+f[cnt][1]);

	return 0;
}
