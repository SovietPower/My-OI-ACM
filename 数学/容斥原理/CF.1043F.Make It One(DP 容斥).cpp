/*
78ms	4500KB
$Description$
给定$n$个数$A_i$，求最少选出多少个数，使得它们的$\gcd$为$1$。
$n,A_i\leq3\times10^5$。
$Solution$
首先如果有解，答案不会超过$7$（$7$个质数的乘积就会大于$300000$）（但是$6$个不会！所以答案可能是$7$的啊=-=zz如我）。
所以令$f[i][j]$表示选了$i$个数，使得它们$\gcd=j$的**方案数**。因为DP不好算考虑直接计数。
记$cnt_i$表示含有因子$i$的数的个数。
那么$f[i][j]=C_{cnt_j}^i-\sum_{j\mid k,k\neq j}f[i][k]$。
判一下是否有$f[i][1]>0$即可。
复杂度$O(7n\log n)$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define mod 1000000009
#define C(n,m) (n<m?0:1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod)
#define gc() getchar()
typedef long long LL;
const int N=3e5+5;

int f[N],cnt[N],fac[N],ifac[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%mod) k&1&&(t=1ll*t*x%mod);
	return t;
}

int main()
{
	int n=read(),mx=0;
	for(int i=1,a; i<=n; ++i) mx=std::max(mx,a=read()), ++cnt[a];
	if(cnt[1]) return puts("1"),0;

	fac[0]=fac[1]=1;
	for(int i=2; i<=n; ++i) fac[i]=1ll*i*fac[i-1]%mod;
	ifac[n]=FP(fac[n],mod-2);
	for(int i=n; i; --i) ifac[i-1]=1ll*i*ifac[i]%mod;

	cnt[1]=n;
	for(int i=2; i<=mx; ++i)
		for(int j=i<<1; j<=mx; j+=i) cnt[i]+=cnt[j];
	for(int i=2; i<=7; ++i)
	{
		for(int j=mx; j; --j)
		{
			LL tmp=C(cnt[j],i);
			for(int k=j<<1; k<=mx; k+=j) tmp-=f[k];
			f[j]=(tmp%mod+mod)%mod;
		}
		if(f[1]) return printf("%d\n",i),0;
	}
	puts("-1");

	return 0;
}
