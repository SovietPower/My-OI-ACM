/*
16448kb	1008ms
��Ϊ�Ǳ��ʲ�ͬ�����Կ�������С�ֵ��������
�����������ֵΪ$m$����ô�����������������
1. $1\ (1\ 2\ 1\ 2...)\ 2\ (3\ 2\ 3\ 2...)\ 3\ (4\ 3\ 4\ 3...)\ ...\ m$
2. $1\ (1\ 2\ 1\ 2...)\ 2\ (3\ 2\ 3\ 2...)\ 3\ (4\ 3\ 4\ 3...)\ ...\ m\ m-1$
������г���Ϊ$n$����ô���Կ���������$\frac{n-m}{2}$����ͬ���򣬽����ǷŽ�$m-1$�����ӣ���������пյķ���������$C_{n+m-1}^{m-1}$��
������ĸ���ȡ$\lfloor\frac{n-m}{2}\rfloor$���ɣ��ڶ������ȡ$\lfloor\frac{n-m-1}{2}\rfloor$������������һ�����ǰ����ŵ��������еĺ������ǲ�ͬ�ġ�
$n,m$���ǲ�ȷ���ġ���Ϊ$\sum_{i=0}^nC_{i+m-1}^{m-1}=C_{n+m-1}^{m-1}$������ö�����ֵ$m$���Ϳ���$O(m)$�õ�������
Ԥ����$2e6$�Ϳ��԰�������Ҫ$4e6$����Ϊ$\frac{n-m}{2}+m=\frac{n+m}{2}$����
*/
#include <cstdio>
#include <algorithm>
#define mod 1000000007
typedef long long LL;
const int N=2e6+5;

int fac[N],ifac[N];

#define F(n,m) (1ll*fac[(n)+(m)-1]*ifac[n]%mod*ifac[(m)-1]%mod)
inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%mod)
		if(k&1) t=1ll*t*x%mod;
	return t;
}

int main()
{
	int n,m; scanf("%d%d",&n,&m);
	fac[0]=fac[1]=1; int lim=n+m>>1;
	for(int i=2; i<=lim; ++i) fac[i]=1ll*fac[i-1]*i%mod;
	ifac[lim]=FP(fac[lim],mod-2);
	for(int i=lim-1; ~i; --i) ifac[i]=1ll*ifac[i+1]*(i+1)%mod;

	LL ans=n&&m;//m=1������ 
	for(int i=2,l=std::min(n,m); i<=l; ++i)
	{
		ans+=F((n-i)/2,i);
		if(i+1<=n) ans+=F((n-i-1)/2,i);
	}
	printf("%lld\n",ans%mod);

	return 0;
}
//	int i;//ͻȻ�е� 
//	for(i=2; i+3<=lim; i+=4)
//		fac[i]=1ll*fac[i-1]*i%mod,
//		fac[i+1]=1ll*fac[i]*(i+1)%mod,
//		fac[i+2]=1ll*fac[i+1]*(i+2)%mod,
//		fac[i+3]=1ll*fac[i+2]*(i+3)%mod;
//	for(; i<=lim; ++i) fac[i]=1ll*fac[i-1]*i%mod;
//	ifac[lim]=FP(fac[lim],mod-2);
//	for(i=lim-1; i-3>=0; i-=4)
//		ifac[i]=1ll*ifac[i+1]*(i+1)%mod,
//		ifac[i-1]=1ll*ifac[i]*(i)%mod,
//		ifac[i-2]=1ll*ifac[i-1]*(i-1)%mod,
//		ifac[i-3]=1ll*ifac[i-2]*(i-2)%mod;
//	for(; i>=0; --i) ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
