/*
31ms	6700KB
$Description$
给定$n$个数。你可以选择一段区间将它们都加上或减去任意一个数。求最终序列中最多能有多少个数等于给定的$C$。
$n\leq5\times10^5$。
$Solution$
先记一个表示$C$的个数的前缀和$sum_i$。
选择修改的区间$[l,r]$一定满足$A_l=A_r$且都是由$A_l$变成$C$。所以我们枚举右端点，对每种权值单独考虑。
那么$A_r$要么是由前面某个等于$A_r$的数转移过来，要么$l$直接等于$r$。
所以记$mx_{a_i}$为之前$a_i$这个数的最大贡献，那么$$mx_{a_i}=\max\{\ mx_{a_i}+1,\ \ sum_{i-1}+1\}$$
$Ans=\max\{mx_{a_i}+sum_n-sum_i\}$。for一遍就行啦。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=5e5+5;

int A[N],sum[N],mx[N];
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
	const int n=read(),C=read();
	for(int i=1; i<=n; ++i) sum[i]=sum[i-1]+((A[i]=read())==C);
	int ans=0; const int sn=sum[n];
	for(int i=1; i<=n; ++i)
		mx[A[i]]=std::max(mx[A[i]],sum[i-1])+1, ans=std::max(ans,mx[A[i]]+sn-sum[i]);
	printf("%d\n",ans);

	return 0;
}
