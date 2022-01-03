/*
9208kb	7720ms
枚举每一位。在这一位上与之后得到$1$的就是全$1$子矩形个数。或之后得到$1$的就是总举行个数减去全$0$子矩形个数。
单调栈算一下就好啦。
维护一个单调递增的栈。如果在右下角统计贡献，每次遇到往上延伸长度$l\leq sk[top]$时，会把$sk[top]$的一部分截断。用个变量$sum$维护前面所有柱子当前的延伸距离即可。
算惹我不说惹 看代码叭= =
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define mod 1000000007
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1005;

int A[N][N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
int Calc(const int n,const int bit,const int equ)
{
	static int sk[N],sz[N],mx[N][N];
	LL ans=0; sk[0]=-1;
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=n; ++j) mx[i][j]=((A[i][j]>>bit&1)==equ)?mx[i-1][j]+1:0;
		LL sum=0;
		for(int j=1,top=0; j<=n; ++j)
		{
			int tot=0;
			while(sk[top]>=mx[i][j]) sum-=sk[top]*sz[top], tot+=sz[top--];
			sk[++top]=mx[i][j], sz[top]=tot+1;
			sum+=sk[top]*sz[top], ans+=sum;
		}
	}
	return ans%mod;
}

int main()
{
	const int n=read(); int mx=0;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j) mx=std::max(mx,A[i][j]=read());
	LL ans1=0,ans2=0,tmp=(1ll*n*(n+1)*n*(n+1)>>2)%mod;
	for(int i=0; 1ll<<i<=mx; ++i) ans1+=(1ll<<i)*Calc(n,i,1)%mod;//1ll<<i<=mx!
	for(int i=0; 1ll<<i<=mx; ++i) ans2+=(1ll<<i)*(tmp+mod-Calc(n,i,0))%mod;
	printf("%lld %lld\n",ans1%mod,ans2%mod);

	return 0;
}
