/*
容易发现只要满足a[i]!=a[i-2]就合法。那么把奇数偶数位置的分别做，就成了，在-1位置上填1~k的数，使得相邻两个位置不相同的方案数。
DP。发现转移麻烦在a -1 -1 b这种，b前面的-1的方案数比较麻烦。那么就令f[i][0/1]表示当前填到第i个数，和后面第一个非-1的数是否相等的方案数。
转移根据情况乘个k-1或k-2即可。注意一下边界条件。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define mod 998244353
#define gc() getchar()
typedef long long LL;
const int N=2e5+5;

int A[N],f[N][2];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
int Solve(int n,LL k,int b)
{
	LL res=1; int p=1;
	for(int i=1+b,j=1; i<=n; p=i,i+=2)
	{
		if(A[i]==-1)
		{
			if(i<=2)
			{
				for(j=i+2; A[j]==-1; j+=2);
				if(j<=n) f[i][0]=k-1, f[i][1]=1;
				else f[i][0]=k, f[i][1]=0;
			}
			else if(A[i-2]==-1)
			{
				if(j>n) f[i][0]=f[i-2][0]*(k-1)%mod;
				else
				{
					f[i][0]=(f[i-2][0]*(k-2)+f[i-2][1]*(k-1))%mod;
					f[i][1]=f[i-2][0];
				}
			}
		}
		else
		{
			if(i>2&&A[i-2]==-1) res=res*f[i-2][0]%mod;
			for(j=i+2; A[j]==-1; j+=2);
			if(j>n||A[j]==A[i]) f[i+2][0]=k-1, f[i+2][1]=0;
			else f[i+2][0]=k-2, f[i+2][1]=1;
		}
	}
	if(A[p]==-1) res=res*f[p][0]%mod;
	return res;
}

int main()
{
	int n=read(),k=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i+2<=n; ++i) if(A[i]==A[i+2] && A[i]!=-1) return puts("0"),0;
	printf("%I64d\n",1ll*Solve(n,k,0)*Solve(n,k,1)%mod);

	return 0;
}
