/*
31ms	3800KB
Good Sequence是可以拼接的吧。于是考虑倒着$O(n^2)$dp。
枚举要接在i后面的子序列j(i<j，A[i]>0)。A[i]已知 i这个子序列就已知，且有C(j-i-1,A[i]+1-1)种构成i的方案(并不需要它连续)。
i单独成一个也可以，要加上自己构成的C(n-i,A[i])种。可以令f[n+1]=1，j枚举到n+1。
*/
#include <cstdio>
#include <cctype>
#define gc() getchar()
#define mod (998244353)
typedef long long LL;
const int N=1005;

int n,C[N][N],A[N],f[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
void Init()
{
	for(int i=1; i<=n; ++i)
	{
		C[i][0]=C[i][i]=1;
		for(int j=1; j<i; ++j)
			C[i][j]=C[i-1][j]+C[i-1][j-1], (C[i][j]>=mod)&&(C[i][j]-=mod);
	}
}

int main()
{
	n=read(), Init();
	for(int i=1; i<=n; ++i) A[i]=read();
	f[n+1]=1;
	for(int i=n; i; --i)
	{
		if(A[i]<=0) continue;
		LL tmp=0;
		for(int j=i+1+A[i]; j<=n+1; ++j) tmp+=1ll*C[j-i-1][A[i]]*f[j]%mod;
		f[i]=(int)(tmp%mod);
	}
	LL ans=0;
	for(int i=1; i<=n; ++i) ans+=f[i];
	printf("%d\n",(int)(ans%mod));

	return 0;
}
