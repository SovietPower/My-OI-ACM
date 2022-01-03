/*
824kb	36ms
题意的一点说明：
$k$次方这个$k$是固定的，也就是最初需要多少张亵渎，每次不会改变；
因某个怪物死亡引发的亵渎不会计分。

不难发现当前所需的张数是空格数+1，即$m+1$。
贡献不妨写成：$\sum_{i=1}^ni^{m+1}-\sum_{i=1}^mA_i^{m+1}$。注意此时的$A_i$是剩下的空格（具体看代码最底下的暴力部分吧）。
所以问题在于求$\sum_{i=1}^ni^{m+1}$。自然数幂和有很多种求法。
这里写插值做法：
$\sum_{i=1}^ni^{m}$是一个以$n$为自变量的$m+1$次多项式，我们代入$m+2$个点就可以用拉格朗日插值求出来$f(n)$了。
代入点的$x$值连续，就可以用前缀积、后缀积和阶乘将拉格朗日插值优化到$O(n)$计算单点函数值（具体见下面）。
复杂度$O(Tm^2)$。

写一下拉格朗日插值的式子及实现：
$$f(x)=\sum_{i=0}^ny_i\prod_{j\neq i}\frac{x-x_i}{x_i-x_j}$$

当$x_i$取$i$时：
$$f(x)=\sum_{i=0}^ny_i\prod_{j\neq i}\frac{x-i}{i-j}$$

对于$x$，预处理前缀积、后缀积：$pre_j=\prod_{i=0}^jx-x_i,\;suf_j=\prod_{i=j}^nx-x_i$。
不难发现上面式子的分子就是前缀积乘后缀积，分母是两个阶乘相乘（注意会有符号问题）。所以就是：
$$f(x)=\sum_{i=0}^ny_i\frac{pre_{i-1}\times suf_{i+1}}{i!\times(n-i)!}$$

就可以$O(n)$计算$f(x)$了。
*/
#include <cstdio>
#include <algorithm>
#define mod 1000000007
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
#define Add2(x,y) (x+y>=mod?x+y-mod:x+y)
typedef long long LL;
const int N=55;

int ifac[N],y[N];
LL A[N];

inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%mod)
		if(k&1) t=1ll*t*x%mod;
	return t;
}
int F(const int x,const int m)//∑_{i=1}^x i^m 自变量为x的m+1次多项式 在x处的取值 
{
	static int pre[N],suf[N];
	const int lim=m+1;
	pre[0]=x, suf[lim+1]=1;//, Mod(suf[lim]);
	for(int i=1; i<=m; ++i) pre[i]=1ll*pre[i-1]*(x+mod-i)%mod;
	for(int i=lim; i; --i) suf[i]=1ll*suf[i+1]*(x+mod-i)%mod;
	LL ans=0;
	for(int i=0,up,down; i<=lim; ++i)
	{
		if(i) up=1ll*pre[i-1]*suf[i+1]%mod*y[i]%mod;
		else up=1ll*suf[i+1]*y[i]%mod;
		down=(lim-i)&1?mod-1ll*ifac[i]*ifac[lim-i]%mod:1ll*ifac[i]*ifac[lim-i]%mod;
		ans+=1ll*up*down%mod;
	}
	return ans%mod;
}

int main()
{
	ifac[N-1]=956708188;
	for(int i=N-1; i; --i) ifac[i-1]=1ll*ifac[i]*i%mod;

	int T;
	for(scanf("%d",&T); T--; )
	{
		LL n; int m; scanf("%lld%d",&n,&m), n%=mod;
		for(int i=1; i<=m; ++i) scanf("%lld",&A[i]);
		std::sort(A+1,A+1+m);
		for(int i=1; i<=m; ++i) A[i]%=mod;//sort后再取模！

		LL ans=0; ++m, y[0]=0;
		for(int i=1; i<=m+1; ++i) y[i]=y[i-1]+FP(i,m), Mod(y[i]);
		for(int t=0; t<m; ++t)
		{
			ans+=F(Add2(n,mod-A[t]),m);// for(int i=1; i<=n; ++i) ans+=FP(i,m);
			for(int i=t; i<m; ++i) ans-=FP(Add2(A[i],mod-A[t]),m);
		}
		printf("%lld\n",(ans%mod+mod)%mod);
	}
	return 0;
}
//BruteForce:
//		++m;
//		for(int t=1; t<=m; ++t)
//		{
//			for(int i=1; i<=n; ++i) ans+=FP(i,m);
//			for(int i=t; i<m; ++i) ans-=FP(A[i],m);
//			for(int i=t+1; i<m; ++i) A[i]-=A[t];
//			n-=A[t];
//		}
