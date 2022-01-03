/*
127ms	64384KB
$Description$
������Ϊ$n$����������$a,b$����$$\sum_{i=1}^n\sum_{j=i+1}^n\binom{a_i+a_j+b_i+b_j}{a_i+a_j}\ mod\ 10^9+7$$
n<=2e5,ai,bi<=2000��
$Solution$
����$\binom{n+m}{n}$��������壺������ͼ�ϴ�$(0,0)$�ߵ�$(n,m)$�ķ�����(NE lattice paths)��Ҳ���ڴ�$(x,y)$�ߵ�$(x+n,y+m)$�ķ�������
����$\binom{a_i+a_j+b_i+b_j}{a_i+a_j}$��������壺��$(0,0)$�ߵ�$(a_i+a_j+b_i+b_j)$�ķ���������$(-a_i,-b_i)$�ߵ�$(a_j,b_j)$�ķ�������
���Ǽ��������$(-a_i,-b_i)$�ߵ�����$(a_j,b_j)$�ķ���������ĳ�����ߵ���һ����ķ��������Ե��Ƶõ�����ĳЩ���ߵ�ĳ����ķ�����ͬ�����Ե��ơ�
������ȥÿ�����Լ����Լ��ķ��������ٰѴ𰸳���$2$�����ˡ�
���Ӷ�$O((2\max(a_i,b_i))^2)$��
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
