//1107ms	7700KB
//https://www.cnblogs.com/SovietPower/p/9338517.html
#include <cstdio>
#include <algorithm>
#define mod (998244353)
typedef long long LL;
const int N=1e6+7;

int C[N],inv[N];

inline LL FP(LL x,int k)
{
	LL t=1;
	for(; k; k>>=1,x=x*x%mod)
		if(k&1) t=t*x%mod;
	return t;
}

int main()
{
	int n; scanf("%d",&n);
	LL ans1=0; C[0]=inv[1]=1;
	for(int i=1; i<=n; ++i)
	{
		if(i>1) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
		C[i]=1ll*(n-i+1)*C[i-1]%mod*inv[i]%mod;
		if(i&1) ans1+=1ll*C[i]*FP(3,(1ll*n*(n-i)+i)%(mod-1))%mod;//a^{\varphi(p)}=1(\mod p)
		else ans1-=1ll*C[i]*FP(3,(1ll*n*(n-i)+i)%(mod-1))%mod;
	}
	ans1=2ll*ans1%mod;
	LL ans2=0;
	for(int i=0,pw3=1; i<n; ++i)
	{
		if(i&1) ans2+=1ll*C[i]*(FP(1+mod-pw3,n)-FP(mod-pw3,n))%mod;
		else ans2-=1ll*C[i]*(FP(1+mod-pw3,n)-FP(mod-pw3,n))%mod;
		pw3=3ll*pw3%mod;
	}
	printf("%I64d\n",((ans1+3ll*ans2)%mod+mod)%mod);

	return 0;
}
