/*
4ms	2304KB
$Description$
数轴上有一个人，从$0$出发到$E$，速度为$1$。数轴上还有$n$只熊，每只熊会在经过后的$T$时刻后产生一个金币。给定$E,T$以及$n$个熊的坐标$p_i$，求收集完所有金币并到达$E$的最短时间。
$n\leq10^5,\quad E,T\leq10^9$。
$Solution$
令$f_i$表示当前$1\sim i$只熊的金币已经收集完，且现在在$p_i$处的最短时间。
每次一定是路过一段的熊，然后回去吃完金币再回到$i$。
那么有：$$f_i=\min\{f_j+p_i-p_j+\max\{T,\ 2(p_i-p_{j+1})\}\}$$
其实$p_i-p_j$这一部分是必走的（就是从$0$到$E$），不需要考虑，可以最后直接加个$E$。所以$$f_i=\min\{f_j+\max\{T,\ 2(p_i-p_{j+1})\}\}$$
尝试对这个$\max$分类讨论一下。
假如我们维护最接近原点且满足$T>2(p_i-p_{j+1})$的位置$j$，那么方程就是$f_i=\min\{f_j+T\}$。
而对于不要的那些满足$T\leq2(p_i-p_{j+1})$的$j$，$f_i=\min\{f_j+2p_i-2p_{j+1}\}$，只要记录这些$j$的$f_j-2p_{j+1}$的最小值就可以了。
复杂度$O(n)$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 1000000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int p[N];
LL f[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read(),E=read(),T=read();
	for(int i=1; i<=n; ++i) p[i]=read();
	LL mn=1e16;
	for(int i=1,j=0; i<=n; ++i)
	{
		while(T<=2*(p[i]-p[j+1])) mn=std::min(mn,f[j]-2*p[j+1]), ++j;
		if(j!=i) f[i]=std::min(f[j]+T,mn+2*p[i]);
		else f[i]=mn+2*p[i];
	}
	printf("%lld\n",f[n]+E);

	return 0;
}
