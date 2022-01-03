/*
912kb	592ms
$Description$
有$n$个人，$m$门课，每个人在每门课的得分是一个$[1,u_i ]$之间的整数。
你知道自己在每门课的排名$r_i$，即有$r_i-1$个人得分高于你，$n-r_i$个人得分不高于你（不含自己）。
求你恰好碾压k个人的方案数，a碾压b的含义为a每门课的得分都不低于b的得分。
$n,m\leq 100,u_i \leq 10^{9}$。
$Solution$
求方案数，考虑DP...
$f[i][j]$表示到第$i$门课，还有$j$人会被碾压的方案数。
那么$$f[i][j]=\sum_{k=j}^{n-1}f[i-1][k]\times C_k^{k-j}\times C_{n-1-k}^{R_i-1-(k-j)}\times g[i]$$

就是先从$k$人中选出$k-j$在$i$这门课比B神得分高，然后再从剩下$n-1-k$个人中选$R_i-1-(k-j)$个比B神得分高的。
对于排名限制，$g[i]$表示对$i$这门课分配得分使得有$R_i-1$个人得分比B神高的方案数。直接枚举一下B神得分：$$g[i]=\sum_{j=1}^{U_i}j^{n-R_i}(U_i-j)^{R_i-1}$$

不难看出这是一个关于$U_i$的$n$次的多项式。拉格朗日插值算一下就好了。（不对为啥是$n$次的不是$n-1$次的啊QAQ求路过dalao解答QAQ）

复杂度$O(n^3\log n)$。
因为求$g$在某点的值的时候要$n$次快速幂。。看了半天题解也没看懂怎么优化掉这个。但是有更好的做法：[here](http://www.cnblogs.com/wangyurzee7/p/5479494.html) or [here](https://blog.csdn.net/aarongzk/article/details/51760818)，是$n^3$的。
不管了反正这个$\log$也不大。
用容斥做也可以，瓶颈也是在于求$g$。。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define mod 1000000007
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
typedef long long LL;
const int N=105;

int ifac[N],y[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%mod)
		if(k&1) t=1ll*t*x%mod;
	return t;
}
int Lagrange(int *y,const int n,const int x)
{
	static int pre[N],suf[N];
	pre[0]=x, suf[n+1]=1;
	for(int i=n; i; --i) suf[i]=1ll*suf[i+1]*(x+mod-i)%mod;
	for(int i=1; i<n; ++i) pre[i]=1ll*pre[i-1]*(x+mod-i)%mod;
	LL ans=0;
	for(int i=0,up,down; i<=n; ++i)
	{
		if(i) up=1ll*pre[i-1]*suf[i+1]%mod*y[i]%mod;
		else up=1ll*suf[i+1]*y[i]%mod;
		down=(n-i)&1?mod-1ll*ifac[i]*ifac[n-i]%mod:1ll*ifac[i]*ifac[n-i]%mod;
		ans+=1ll*up*down%mod;
	}
	return ans%mod;
}

int main()
{
	static int C[N][N],f[N][N],U[N],R[N];

	int n=read(),m=read(),K=read(),fac=1;
	for(int i=2; i<=n; ++i) fac=1ll*fac*i%mod;
	ifac[n]=FP(fac,mod-2);
	for(int i=n; i; --i) ifac[i-1]=1ll*ifac[i]*i%mod;
	C[0][0]=1;//!
	for(int i=1; i<=n; ++i)
	{
		C[i][0]=C[i][i]=1;
		for(int j=1; j<i; ++j) C[i][j]=C[i-1][j-1]+C[i-1][j], Mod(C[i][j]);
	}
	for(int i=1; i<=m; ++i) U[i]=read();
	for(int i=1; i<=m; ++i) R[i]=read();

	f[0][n-1]=1;
	for(int i=1; i<=m; ++i)
	{
		int Ri=R[i];
		for(int x=1; x<=n; ++x)
		{
			LL tmp=0;
			for(int j=1; j<=x; ++j) tmp+=1ll*FP(j,n-Ri)*FP(x-j,Ri-1)%mod;//这里j要枚举到x，因为0^0=1！...
			y[x]=tmp%mod;
		}
		int g=Lagrange(y,n,U[i]);
		for(int j=K; Ri+j<=n; ++j)
		{
			LL tmp=0;
			for(int k=j; k<n; ++k)
				if(k-j<Ri) tmp+=1ll*f[i-1][k]*C[k][j]%mod*C[n-1-k][Ri-1-k+j]%mod;
				else break;
			f[i][j]=tmp%mod*g%mod;
		}
	}
	printf("%d\n",f[m][K]);

	return 0;
}
