#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
#define mod 998244353
#define Mod(x) x>=mod&&(x-=mod)
typedef long long LL;
const int N=1e5+3;

int A[N],f[N][202][2],pre[N],suf[N];

inline LL read()
{
	LL now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	if(A[1]!=-1) f[1][A[1]][0]=1;
	else for(int i=1; i<=200; ++i) f[1][i][0]=1;
	for(int i=2; i<=n; ++i)
	{
		for(int j=1; j<=200; ++j)
		{
			LL tmp=(LL)pre[j-1]+f[i-1][j][0]+f[i-1][j][1];
			pre[j]=(tmp%mod);
		}
		for(int j=200; j; --j)
			suf[j]=suf[j+1]+f[i-1][j][1], Mod(suf[j]);
		if(A[i]!=-1)
			f[i][A[i]][0]=pre[A[i]-1], f[i][A[i]][1]=suf[A[i]+1]+f[i-1][A[i]][0], Mod(f[i][A[i]][1]), f[i][A[i]][1]+=f[i-1][A[i]][1], Mod(f[i][A[i]][1]);
		else
		{
			for(int j=1; j<=200; ++j)
				f[i][j][0]=pre[j-1], f[i][j][1]=suf[j+1]+f[i-1][j][0], Mod(f[i][j][1]), f[i][j][1]+=f[i-1][j][1], Mod(f[i][j][1]);
		}
	}
	LL ans=0;
	for(int i=1; i<=200; ++i) ans+=f[n][i][1];
	printf("%I64d\n",ans%mod);

	return 0;
}
