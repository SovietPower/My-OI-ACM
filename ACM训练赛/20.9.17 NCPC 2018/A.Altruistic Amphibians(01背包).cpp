/*
218ms	392400KB
$Description$
有$n$只青蛙要过宽度为$d$的河，每只青蛙有重量$w$、高度$h$、跳跃距离$l$。
若干只青蛙可以叠罗汉，但要保证每只青蛙$i$上面的所有青蛙重量和小于$w_i$。此时若青蛙$i$下面青蛙高度和$\sum h+l_i>d$则$i$可以跳过河。
只要满足条件每只青蛙可以任意次堆叠。求最多有多少只青蛙能过河。
$Solution$
英语题面读漏条件就很难受...要注意重量和是严格小于$w_i$，且青蛙总重要$\leq 1e8$。
因为青蛙可以任意次叠罗汉，所以单独的一只青蛙$i$可以为总重$< w_i$的青蛙提供$h_i$的贡献，且只会重的去贡献轻的，
每只青蛙可以选择贡献或不贡献，所以就是一个01背包了。。。
青蛙从重到轻排序，$f[i]$表示可承重为$i$时的最大高度，青蛙$k$的影响为：$f[i]=max(f[i], f[i+w_k]+h_k)$。
注意$k$能更新的$i$范围只有$1~w_k-1$，所以总复杂度只有$O(n+\sum w_i)$。
至于统计答案，只要$f[w_k]+l_k>d$青蛙$k$就一定有办法过了。。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5,M=1e8+3;

int f[M];
struct Frog
{
	int l,w,h;
	bool operator <(const Frog &x)const
	{
		return w>x.w;
	}
}A[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	int n=read(),D=read(),s=0;
	for(int i=1; i<=n; ++i) A[i]=(Frog){read(),read(),read()}, s+=A[i].w;
	std::sort(A+1,A+1+n);
	int ans=0;
	for(int i=1; i<=n; ++i)
	{
		int w=A[i].w, h=A[i].h;
		if(A[i].l+f[w]>D) ++ans;
		for(int j=1; j<w && j+w<=s; ++j) f[j]=std::max(f[j],f[j+w]+h);
	}
	printf("%d\n",ans);

	return 0;
}
