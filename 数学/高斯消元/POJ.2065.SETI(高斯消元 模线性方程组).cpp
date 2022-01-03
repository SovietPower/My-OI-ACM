/*
模意义下的高斯消元，在初等行变换时把k=tar/Anow改为k=tag*inv(Anow) 
最后求解回带时把除法用乘逆元替代即可 
也可用扩展欧几里得求出一个最小的ans[i] 
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
#define mod p
typedef long long LL;
const int N=100;

namespace Gauss
{
	int p,n,A[N][N],ans[N];
	char s[N];
	int FP(LL x,int k)
	{
		LL t=1;
		for(;k;k>>=1, x=x*x%p)
			if(k&1) t=t*x%p;
		return t;
	}
	inline int inv(int x) {return FP(x,p-2);}
	void Init()
	{
		scanf("%d%s",&p,s);
		n=strlen(s);
		for(int i=0; i<n; ++i)
		{
			A[i][0]=1;
			for(int j=1; j<n; ++j)
				A[i][j]=(i+1)*A[i][j-1]%p;
			A[i][n]= s[i]=='*'?0:s[i]-'a'+1;
		}
	}
	void Solve()
	{
		Init();
		for(int j=0; j<n; ++j)
		{
			int mxrow=j;
			for(int i=j+1; i<n; ++i)
				if(A[i][j]>A[mxrow][j]) mxrow=i;
			if(mxrow!=j) std::swap(A[mxrow],A[j]);
			for(int i=j+1; i<n; ++i)
				if(A[i][j])
				{
					int t=A[i][j]*inv(A[j][j])%mod;
					for(int k=j; k<=n; ++k)
						A[i][k]=((A[i][k]-t*A[j][k]%mod)%mod+mod)%mod;
				}
		}
		for(int i=n-1; ~i; --i)
		{
			for(int j=i+1; j<n; ++j)
				A[i][n]=((A[i][n]-A[i][j]*ans[j]%mod)+mod)%mod;
			ans[i]=A[i][n]*inv(A[i][i])%mod;
		}
		for(int i=0; i<n-1; ++i) printf("%d ",ans[i]);
		printf("%d\n",ans[n-1]);
	}
}

int main()
{
	int t; scanf("%d",&t);
	while(t--) Gauss::Solve();
	return 0;
}/*
3
31 aaa
37 abc
29 hello*earth
*/
