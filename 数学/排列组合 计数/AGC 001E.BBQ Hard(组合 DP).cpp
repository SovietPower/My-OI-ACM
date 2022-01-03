/*
127ms	64384KB
$Description$
给定长为$n$的两个数组$a,b$，求$$\sum_{i=1}^n\sum_{j=i+1}^n\binom{a_i+a_j+b_i+b_j}{a_i+a_j}\ mod\ 10^9+7$$
n<=2e5,ai,bi<=2000。
$Solution$
考虑$\binom{n+m}{n}$的组合意义：在网格图上从$(0,0)$走到$(n,m)$的方案数(NE lattice paths)。也等于从$(x,y)$走到$(x+n,y+m)$的方案数。
考虑$\binom{a_i+a_j+b_i+b_j}{a_i+a_j}$的组合意义：从$(0,0)$走到$(a_i+a_j+b_i+b_j)$的方案数，从$(-a_i,-b_i)$走到$(a_j,b_j)$的方案数。
考虑计算从任意$(-a_i,-b_i)$走到任意$(a_j,b_j)$的方案数。从某个点走到另一个点的方案数可以递推得到。从某些点走到某个点的方案数同样可以递推。
算完后减去每个点自己到自己的方案数，再把答案除以$2$就行了。
复杂度$O((2\max(a_i,b_i))^2)$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define mod 1000000007
#define Mod(x) x>=mod&&(x-=mod)
typedef long long LL;
const int N=2e5+5,M=4005,D=2001;

int A[N],B[N],f[M][M],fac[N],ifac[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%mod)
		if(k&1) t=1ll*t*x%mod;
	return t;
}
#define C(n,m) 1ll*fac[n]*ifac[m]%mod*ifac[(n)-(m)]%mod

int main()
{
	int n=read(),mx=0;
	for(int i=1,x,y; i<=n; ++i)
	{
		A[i]=x=read(), B[i]=y=read(), ++f[D-x][D-y];//(-x+D,-y+D)
		mx=std::max(mx,std::max(x,y));
	}
	int lim=D+mx;
	for(int i=D-mx; i<=lim; ++i)
		for(int j=D-mx; j<=lim; ++j)
			f[i][j]+=f[i-1][j]+f[i][j-1], Mod(f[i][j]);//a little bigger

	LL ans=0;
	for(int i=1; i<=n; ++i) ans+=f[D+A[i]][D+B[i]];
	ans%=mod;

	lim=mx<<2, fac[0]=fac[1]=1;
	for(int i=2; i<=lim; ++i) fac[i]=1ll*fac[i-1]*i%mod;
	ifac[lim]=FP(fac[lim],mod-2);
	for(int i=lim-1; ~i; --i) ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
	for(int i=1; i<=n; ++i) ans-=C(A[i]*2+B[i]*2,A[i]*2);

	ans%=mod, ans*=FP(2,mod-2);
	printf("%lld\n",(ans%mod+mod)%mod);

	return 0;
}
