/*
31ms	0KB
Good Sequence�ǿ���ƴ�ӵİɡ����ǿ��ǵ���$O(n^2)$dp��
ö��Ҫ����i�����������j(i<j��A[i]>0)��A[i]��֪ i��������о���֪������C(j-i-1,A[i]+1-1)�ֹ���i�ķ���(������Ҫ������)��
i������һ��Ҳ���ԣ�Ҫ�����Լ����ɵ�C(n-i,A[i])�֡�������f[n+1]=1��jö�ٵ�n+1��
C()����Ԥ����׳˺ͽ׳���Ԫ�����󣬿���ʡ��$n^2$����ʱ��û��Ϳռ��Ż��ˡ���
*/
#include <cstdio>
#include <cctype>
#define gc() getchar()
#define mod (998244353)
typedef long long LL;
const int N=1005;

int n,A[N],f[N],sum[N],inv[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline int FP(LL x,int k)
{
	LL t=1;
	for(; k; k>>=1, x=x*x%mod)
		if(k&1) t=t*x%mod;
	return t;
}
inline int C(int n,int m){
	return 1ll*sum[n]*inv[m]%mod*inv[n-m]%mod;
}

int main()
{
	n=read(), inv[0]=sum[0]=1;
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<=n; ++i) sum[i]=1ll*sum[i-1]*i%mod, inv[i]=1ll*inv[i-1]*FP(i,mod-2)%mod;
	f[n+1]=1;
	for(int i=n; i; --i)
	{
		if(A[i]<=0) continue;
		LL tmp=0;
		for(int j=i+1+A[i]; j<=n+1; ++j) tmp+=1ll*C(j-i-1,A[i])*f[j]%mod;
		f[i]=(int)(tmp%mod);
	}
	LL ans=0;
	for(int i=1; i<=n; ++i) ans+=f[i];
	printf("%d\n",(int)(ans%mod));

	return 0;
}
