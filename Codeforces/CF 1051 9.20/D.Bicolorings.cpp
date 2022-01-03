#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define mod 998244353
typedef long long LL;
const int N=1005;

LL f[N][N<<1][2][2];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	int n=read(),K=read();
	f[1][1][0][0]=f[1][1][1][1]=f[1][2][1][0]=f[1][2][0][1]=1;
	for(int i=2; i<=n; ++i)
	{
		for(int j=1; j<=K; ++j)
		{
			f[i][j][0][0]=(f[i-1][j-1][1][1]+f[i-1][j][0][1]+f[i-1][j][1][0]+f[i-1][j][0][0])%mod;
			f[i][j][1][1]=(f[i-1][j-1][0][0]+f[i-1][j][1][0]+f[i-1][j][0][1]+f[i-1][j][1][1])%mod;
			f[i][j][0][1]=(f[i-1][j-1][1][1]+f[i-1][j-1][0][0]+f[i-1][j][0][1]+(j>=2?f[i-1][j-2][1][0]:0))%mod;
			f[i][j][1][0]=(f[i-1][j-1][0][0]+f[i-1][j-1][1][1]+f[i-1][j][1][0]+(j>=2?f[i-1][j-2][0][1]:0))%mod;
		}
	}
	LL ans=0;
	for(int i=0; i<2; ++i) for(int j=0; j<2; ++j) ans+=f[n][K][i][j];
	printf("%I64d\n",ans%mod);

	return 0;
}
