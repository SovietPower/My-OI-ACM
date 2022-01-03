/*
$Description$
给定集合$S=\{a_1,a_2,\ldots,a_n\}$，集合中两点之间有边当且仅当$a_i|a_j$或$a_j|a_i$。
求$S$最大的一个子集$S'$，并满足$S'$中任意两点间都有连边（$S'$中只有1个点也是合法的）。
$n,a_i\leq 10^6$，$a_i$互不相同。
$Solution$
从小到大选（已经排好序），如果选了$a_i$，则下一个数一定是$a_i$的倍数，下下个数一定是下个数和这个数的倍数。。
容易想到DP，每次更新其倍数即可。复杂度$O(n\ln n)$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e6+5;

int n,A[N],f[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(); int mx=0, ans=1;
	for(int i=1; i<=n; ++i) mx=std::max(mx,A[i]=read());
	for(int i=1; i<=n; ++i)
	{
		int a=A[i], v=++f[a];
		ans=std::max(ans,v);
		for(int j=a<<1; j<=mx; j+=a) f[j]=std::max(f[j],v);
	}
	printf("%d\n",ans);

	return 0;
}
