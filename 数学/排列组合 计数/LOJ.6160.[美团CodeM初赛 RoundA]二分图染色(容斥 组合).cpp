/*
3127ms	117372K
$Description$
求在$2n$个点的完全二分图（两边各有$n$个点）上确定两组匹配，使得两个匹配没有交集的方案数。
$n\leq10^7$。

$Solution$
不考虑限制，令$f_i$表示在$2i$个点的二分图上任意确定一组匹配的方案数，确定两组匹配的方案数就是$f_n^2$。
对于限制，考虑容斥，枚举令多少个匹配强制相同，即$Ans=\sum\limits_{i=0}^n(-1)^ii!(C_n^i)^2f_{n-i}^2$。

对于$f_n$，一个显然的求法是$f_n=\sum_{i=0}^ni!(C_n^i)^2$。但这样总复杂度就是$O(n^2)$了。
打个表可以找出规律：$f_n=2nf_{n-1}-(n-1)^2f_{n-2}$。
考虑如何由$n-1$推到$n$。不考虑限制，第$n$对点有$2n-1$种和其它点匹配的方案，再加上不选这对点方案数就是$2nf_{n-1}$。
假设第$n$对点中连出的匹配和$(i,j)$相同，那么有$(n-1)^2$种可能，每种可能的方案数都是$f_{n-2}$。所以减掉$(n-1)^2f_{n-2}$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define mod 1000000007
#define gc() getchar()
typedef long long LL;
const int N=1e7+5;

int f[N],fac[N],ifac[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%mod)
		if(k&1) t=1ll*t*x%mod;
	return t;
}

int main()
{
	int n=read(); fac[0]=1;
	for(int i=1; i<=n; ++i) fac[i]=1ll*fac[i-1]*i%mod;
	ifac[n]=FP(fac[n],mod-2);
	for(int i=n; i; --i) ifac[i-1]=1ll*ifac[i]*i%mod;
	f[0]=1, f[1]=2;
	for(int i=2; i<=n; ++i) f[i]=(2ll*i*f[i-1]-1ll*(i-1)*(i-1)%mod*f[i-2])%mod;

	LL ans=0,tmp=1ll*fac[n]*fac[n]%mod;
	#define v (tmp*ifac[n-i]%mod*ifac[n-i]%mod*ifac[i]%mod*f[n-i]%mod*f[n-i]%mod)
	for(int i=0; i<=n; ++i) ans+=i&1?-v:v;
	printf("%lld\n",(ans%mod+mod)%mod);

	return 0;
}
