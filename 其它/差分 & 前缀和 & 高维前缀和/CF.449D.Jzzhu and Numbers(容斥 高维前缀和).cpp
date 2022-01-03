/*
62ms	35500KB
$Description$
给定$n$个正整数$a_i$。求有多少个子序列$a_{i_1},a_{i_2},...,a_{i_k}$，满足$a_{i_1},a_{i_2},...,a_{i_k}$ $and$起来为$0$。
$n\leq10^6,\quad 0\leq a_i\leq10^6$。
$Solution$
这个数据范围。。考虑按位容斥：
令$g_x$表示$x$的二进制表示中$1$的个数，$f_x$表示有多少个$a_i$满足$a_i\&x=x$。
想要让选出来的子序列最终$and$和为$x$，那么只能从这$f_x$个数中选。
所以$Ans=\sum_{x=0}^{lim}(-1)^{g_x}(2^{f_x}-1)$。
那么如何求$f_x$？
$a_i\&x=x$，即$x$是$a_i$的子集，所以对$f_x$枚举超集更新即可。复杂度$O(2^nn)$。
注意因为写法问题数组要开两倍。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define mod 1000000007
#define lb(x) (x&-x)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
typedef long long LL;
const int N=3e6+5;

int bit[N],pw[N],f[N];
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
	int n=read(),lim=0;
	for(int t,i=1; i<=n; ++i) ++f[t=read()],lim=std::max(lim,t);
	pw[0]=1;
	for(int i=1; i<=n; ++i) pw[i]=pw[i-1]<<1, pw[i]>=mod&&(pw[i]-=mod);
	for(int i=0; 1<<i<=lim; ++i)
		for(int s=0; s<=lim; ++s)
			if(!(s>>i&1)) Add(f[s],f[s|(1<<i)]);
	LL ans=0;
	for(int i=1; i<=lim; ++i) bit[i]=bit[i^lb(i)]^1;
	for(int i=0; i<=lim; ++i) ans+=bit[i]?mod-pw[f[i]]+1:pw[f[i]]-1;
	printf("%I64d\n",ans%mod);

	return 0;
}
