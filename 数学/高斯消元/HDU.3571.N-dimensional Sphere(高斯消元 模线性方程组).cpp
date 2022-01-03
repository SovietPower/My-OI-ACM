/*
$Description$
在n维空间中给定n+1个点，求一个点使得这个点到所有点的距离都为R(R不给出)。点的任一坐标|xi|<=1e17.
$Solution$
根据题意可以列出n+1个二元n次方程，相邻的方程相减可以把二次项和R全部约掉，得到n个一元n次方程。
但需要注意这题数据量较大，最大的可能解范围为1e17，如果利用大数(高精...) 乘法的复杂度会很高
可以采用同余的方法，所有运算需要模一个足够大的素数(>1e17)，可以用Miller_Rabin生成一个。。还有快速乘就不说了。
这样利用同余方程可以求出一个最小的非负解。
由于这题数据会有负数，而同余求出的是非负数，为消除这种情况，需对所有数值加上一个偏移量1e17，最后的解再减去偏移量。
 */
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=55;
const LL mod=200000000000000003ll;
const LL offset=1e17;

LL A[N][N],B[N];

inline LL read()
{
	LL now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline LL Mult(LL a,LL b)
{
	LL tmp=a*b-(LL)((long double)a/mod*b+1e-8)*mod;
	return tmp<0?tmp+mod:tmp;
}
//#define Add(x,y) ((x)+=(y),(x)>=mod?(x)-=mod:0)
//inline LL Mult(LL a,LL b)
//{
//	LL t=0;
//	for(;b;b>>=1,Add(a,a))
//		if(b&1) Add(t,a);
//	return t;
//}
namespace Gauss
{
	int n;
	LL f[N][N],ans[N];
	LL Exgcd(LL a,LL b,LL &x,LL &y)
	{
		if(!b) x=1,y=0;
		else Exgcd(b,a%b,y,x),y-=a/b*x;
	}
	LL Inv(LL a)
	{
		LL x,y; Exgcd(a,mod,x,y);
		return (x%mod+mod)%mod;
	}
	void Init()
	{
		for(int i=0; i<n; ++i)
		{
			for(int j=0; j<n; ++j)
				f[i][j]=((A[i+1][j]-A[i][j]<<1)%mod+mod)%mod;
			f[i][n]=((B[i+1]-B[i])%mod+mod)%mod;
		}
	}
	void Solve()
	{
		for(int j=0; j<n; ++j)
		{
			int mxrow=j;
			for(int i=j+1; i<n; ++i)
				if(f[i][j]>f[mxrow][j]) mxrow=i;
			if(mxrow!=j) std::swap(f[mxrow],f[j]);
			LL inv=Inv(f[j][j]);
			for(int i=j+1; i<n; ++i)
				if(f[i][j])
				{
					LL t=Mult(f[i][j],inv);
					f[i][j]=0;
					for(int k=j+1; k<=n; ++k)
						f[i][k]=((f[i][k]-Mult(t,f[j][k]))%mod+mod)%mod;
				}
		}
		for(int i=n-1; ~i; --i)
		{
			for(int j=i+1; j<n; ++j)
				f[i][n]=(f[i][n]-Mult(ans[j],f[i][j]))%mod;
			(f[i][n]+=mod)%=mod;
			ans[i]=Mult(f[i][n],Inv(f[i][i]));
		}
		for(int i=0; i<n-1; ++i) printf("%lld ",ans[i]-offset);
		printf("%lld\n",ans[n-1]-offset);
//		for(int i=0; i<n-1; ++i) printf("%I64d ",ans[i]-offset);
//		printf("%I64d\n",ans[n-1]-offset);

	}
}

int main()
{
	int t=read(),n;
	for(int kase=1; kase<=t; ++kase)
	{
		memset(B,0,sizeof B);
		Gauss::n=n=read();
		for(int i=0; i<=n; ++i)
			for(int j=0; j<n; ++j)
				A[i][j]=read()+offset,
				B[i]+=Mult(A[i][j],A[i][j]), B[i]>=mod?B[i]-=mod:0;
		printf("Case %d:\n",kase);
		Gauss::Init(), Gauss::Solve();
	}
	return 0;
}
