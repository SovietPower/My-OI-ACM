/*
233ms	2600KB
$Description$
给定长为$n$的序列$A_i$和一个整数$K$。把它划分成若干段，满足每段中恰好出现过一次的数的个数$\leq K$。求方案数。
$K\leq n\leq10^5$。
$Solution$
设$f[i]$表示前$i$个数的答案，$g[j]$表示$j\sim i$恰好出现过一次的数的个数。有$$f[i]=\sum_{j\leq i,\ g[j]\leq K}f[j-1]$$

记$las_i$为$A_i$上次出现的位置下标。每次$i$移动时，$g[j]$的变化就是，$[las_i+1,i]$区间$+1$，$[las_{las_i}+1,las_i]$区间$-1$。
也就是要动态修改$g[j]$，求$g[j]\leq K$的$f[j-1]$的和。

数据结构什么的不好搞。考虑直接分块。
一种最简单的想法是，块内`sort`后维护前缀和，查询的时候二分。复杂度$O(n\sqrt n\log(\sqrt n))$（注意确实是$\log(\sqrt n)$），但过不去。

设$s[i][j]$表示第$i$块中，$g[k]\leq j$的$f[k]$的和，$tag[i]$表示第$i$块的整体修改标记。
考虑区间修改。对于整块直接打标记。对于零散部分，因为只是$+1$，容易发现对于第$i$块，只有$s[i][g[j]]$的值改变了，且只是少掉了$f[j-1]$（$j$是影响到的下标，显然可以暴力枚举）。那么可以暴力更新$s[i]$。
对于整块的查询，假设是第$i$块，需要满足$j+tag[i]\leq k$，即$j\leq k-tag[i]$，那么$s[i][k-tag[i]]$就是答案了。
那么这样就可以啦。

其实还可以优化。
把每个修改拆成前缀修改，即：$[1,i]$区间$+1$，$[1,las_i]$区间$-2$，$[1,las_{las_i}]$区间$+1$。
这样有什么好处呢。设$i$所在的块为$p$。那么对$p$块零散部分暴力修改，对$1\sim p-1$块统一打上标记$tag$。
可以发现这样$s[i][j]$的第二维是$O(\sqrt n)$级别的（只有同块内的会影响它，其它值都打到$tag$上了）！也就是空间只需要$O(n)$就够了。
而且如果我们把询问也拆成前缀的形式（其实本来就是前缀），那$tag$完全不需要直接打到$1\sim p-1$上，只需要在$p$上打就可以了。查询的时候维护一个$tag$的后缀和即可。
这样设块大小为$B$，修改复杂度就只有$O(B)$，查询复杂度还是$O(B+\frac nB)$，但是某些修改比较多查询比较少的题目就可以调整$B$的大小解决啦。
虽然在这题复杂度依旧是$O(n\sqrt n)$，但是常数不知道优秀到了哪里去。

中间过程（包括查询啊=-=）$s$的第二维可能是负的，但绝对值在$\sqrt n$内。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define B 150
#define mod 998244353
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
#define gc() getchar()
typedef long long LL;
const int N=1e5+5,M=N/B+3;

int bel[N],f[N],g[N],tag[M],s[M][B+3<<1];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
void Update(int p,int v)
{
	int *s=::s[bel[p]];
	for(int i=B; i<=B<<1; ++i) Add(s[i],v);
}
void Modify(int p,int v)
{
	int bel=::bel[p],*s=::s[bel];
	tag[bel]+=v;
	for(int i=bel*B+1; i<=p; ++i)
	{
		if(v==1) Add(s[g[i]+B],mod-f[i-1]);
		else Add(s[g[i]-1+B],f[i-1]), Add(s[g[i]-2+B],f[i-1]);
		g[i]+=v;
	}
}
int Query(int p,int K)
{
	int bel=::bel[p],sum=tag[bel]; LL res=0;
	for(int i=bel*B+1; i<=p; ++i) g[i]<=K&&(res+=f[i-1]);
	while(bel--)
	{
//		assert(sum>=0);
//		if(sum<=K) res+=s[bel][std::min(B<<1,K-sum+B)];//WA:sum may be >K
		if(std::abs(sum-K)<=B) res+=s[bel][K-sum+B];
		else if(sum<K) res+=s[bel][B<<1];
		sum+=tag[bel];
	}
	return res%mod;
}

int main()
{
	static int las[N],pre[N];
	int n=read(),K=read();
	for(int i=1; i<=n; ++i) bel[i]=(i-1)/B;
	f[0]=1;
	for(int i=1; i<=n; ++i)
	{
		int a=read(); las[i]=pre[a], pre[a]=i;
		Update(i,f[i-1]), Modify(i,1);
		if(las[i])
		{
			Modify(las[i],-2);
			if(las[las[i]]) Modify(las[las[i]],1);
		}
		f[i]=Query(i,K);
	}
	printf("%d\n",f[n]);

	return 0;
}
