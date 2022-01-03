/*
3127ms	117372K
$Description$
����$2n$�������ȫ����ͼ�����߸���$n$���㣩��ȷ������ƥ�䣬ʹ������ƥ��û�н����ķ�������
$n\leq10^7$��

$Solution$
���������ƣ���$f_i$��ʾ��$2i$����Ķ���ͼ������ȷ��һ��ƥ��ķ�������ȷ������ƥ��ķ���������$f_n^2$��
�������ƣ������ݳ⣬ö������ٸ�ƥ��ǿ����ͬ����$Ans=\sum\limits_{i=0}^n(-1)^ii!(C_n^i)^2f_{n-i}^2$��

����$f_n$��һ����Ȼ������$f_n=\sum_{i=0}^ni!(C_n^i)^2$���������ܸ��ӶȾ���$O(n^2)$�ˡ�
���������ҳ����ɣ�$f_n=2nf_{n-1}-(n-1)^2f_{n-2}$��
���������$n-1$�Ƶ�$n$�����������ƣ���$n$�Ե���$2n-1$�ֺ�������ƥ��ķ������ټ��ϲ�ѡ��Ե㷽��������$2nf_{n-1}$��
�����$n$�Ե���������ƥ���$(i,j)$��ͬ����ô��$(n-1)^2$�ֿ��ܣ�ÿ�ֿ��ܵķ���������$f_{n-2}$�����Լ���$(n-1)^2f_{n-2}$��
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
