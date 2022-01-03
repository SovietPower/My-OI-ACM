/*
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define mod 1000000007
#define inv(x) FP(x,mod-2)
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

int A[N],B[N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline int FP(int x,int k)
{
	LL res=1;
	for(; k; k>>=1,x=1ll*x*x%mod)
		k&1&&(res=res*x%mod);
	return res;
}

int main()
{
	int n,x;
	while(~scanf("%d%d",&n,&x))
	{
		for(int i=1; i<=n; ++i) A[i]=read();
		for(int i=1; i<=n; ++i) B[i]=read();
		LL res=x;
		for(int i=1; i<=n; ++i) res+=1ll*A[i]*B[i]%mod;
		res%=mod;
		for(int i=2; i<=n; ++i) res=res*x%mod;
		printf("%lld\n",res);
	}

	return 0;
}
