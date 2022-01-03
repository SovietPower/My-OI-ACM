//11072kb	6148ms
//https://www.cnblogs.com/SovietPower/p/9641460.html
/*
$Description$
抛出$Y$个点数在$0,...,X-1$的骰子，求点数总和在$[A,B]$的概率。
$X\leq 20,\ Y\leq 2\times 10^5$。
$Solution$
### 正态分布
[正态分布](https://baike.baidu.com/item/%E6%AD%A3%E6%80%81%E5%88%86%E5%B8%83/829892?fr=aladdin#3)是随机变量$X$的一种概率分布形式。它用一个期望$\mu$和方差$\sigma^2$就可以描述，记为$N(\mu,\sigma^2)$。
若随机变量$X$服从一个数学期望为$\mu$、方差为$\sigma^2$的正态分布，记作$X\sim N(\mu,\sigma^2)$，读作$X$服从$N(\mu,\sigma^2)$。
当$\mu=0,\sigma=1$时的正态分布称为标准正态分布。

### 概率密度函数
[概率密度函数](https://baike.baidu.com/item/%E6%A6%82%E7%8E%87%E5%AF%86%E5%BA%A6%E5%87%BD%E6%95%B0)用来描述连续型随机变量的分布情况。随机变量的取值落在某个区域内的概率，为概率密度函数在该区域的积分。（或者就是$f(x)$在该区域内与$x$轴围成的图形面积）
若随机变量$X\sim N(\mu,\sigma^2)$，则其概率密度函数为
$$f(x)=\frac{1}{\sqrt{2\pi}\sigma}e^{-\frac{(x-\mu)^2}{2\sigma}}$$
$e^x$可以使用$exp()$函数计算。只要证明了一个变量服从正态分布，就可以直接对概率密度函数的这一区间进行积分了。

### 中心极限定理
[中心极限定理](https://baike.baidu.com/item/%E4%B8%AD%E5%BF%83%E6%9E%81%E9%99%90%E5%AE%9A%E7%90%86/829451?fr=aladdin)：当样本量$n$逐渐趋于无穷大时，$n$个抽样样本的均值的频数逐渐趋于正态分布（无论总体是什么分布）。
该定理说明，设随机变量$X_1,X_2,\ldots,X_n$独立同分布，它们的期望为$\mu$、方差为$\sigma^2$，当$n$足够大时（OI:满足精确度需求时），随机变量
$$Y_n=\frac{\sum_{i=1}^nX_i-n\mu}{\sqrt n\sigma}$$
近似地服从标准正态分布$N(0,1)$。

$Y_n$服从正态分布，求出其范围后就可以直接对正态分布的概率密度函数求积分了。
对于本题有
$$\mu=\frac{n-1}{2}，\sigma^2=\frac{\sum_{i=1}^n(i-\mu)^2}{n}=\frac{n^2-1}{12}\\ \sum_{i=1}^nX_i\in[A,B]\\ Y_n\in[\frac{A-n\mu}{\sqrt n\sigma},\frac{B-n\mu}{\sqrt n\sigma}$$
然后对$Y_n$的值域辛普森积分（$\int_l^rf(x)d_x=\frac{(r-l)(f(l)+f(r)+4f(mid))}{6}$）。

但是当$n=1$时也不能认为$n$足够大。所以当数据较小时要用另一种做法。比较显然的是构造生成函数，然后求其$Y$次幂。
这里构造出生成函数后，用FFT将多项式转化为点值表示，可以直接对点值快速幂，再FFT回去。

积分要求$[0,r]-[0,l]$的，直接求$[l,r]$只有80分。。（精度吗）
积分时的$l,r$大小关系并无影响。
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define eps 1e-7
const int N=(1<<19)+5;
const double PI=acos(-1),K=1.0/sqrt(2*PI);

int rev[N];
struct Com//plex
{
	double x,y;
	Com() {}
	Com(double x,double y):x(x),y(y) {}
	Com operator +(const Com &a) {return Com(x+a.x, y+a.y);}
	Com operator -(const Com &a) {return Com(x-a.x, y-a.y);}
	Com operator *(const Com &a) {return Com(x*a.x-y*a.y, x*a.y+y*a.x);}
}A[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
Com FP(Com x,int k)//可以直接点值快速幂 
{
	Com t(1,0);
	for(; k; k>>=1,x=x*x)
		if(k&1) t=t*x;
	return t;
}
void FFT(Com *a,int lim,int opt)
{
	for(int i=1; i<lim; ++i) if(i<rev[i]) std::swap(a[i],a[rev[i]]);
	for(int i=2; i<=lim; i<<=1)
	{
		int mid=i>>1;
		Com Wn(cos(PI/mid),opt*sin(PI/mid)),t;
		for(int j=0; j<lim; j+=i)
		{
			Com w(1,0);
			for(int k=0; k<mid; ++k,w=w*Wn)
				a[j+k+mid]=a[j+k]-(t=a[j+k+mid]*w),
				a[j+k]=a[j+k]+t;
		}
	}
	if(opt==-1) for(int i=0; i<lim; ++i) a[i].x/=lim;
}
inline double F(double x)
{
	return K*exp(-x*x*0.5);
}
inline double Simpson(double l,double r)
{
	return (r-l)*(F(l)+F(r)+4*F((l+r)*0.5))/6.0;
}
double Int(double l,double r,double Eps,double ans)
{
	double m=(l+r)*0.5,lans=Simpson(l,m),rans=Simpson(m,r);
	if(fabs(lans+rans-ans)<Eps) return lans+rans;
	return Int(l,m,Eps*0.5,lans)+Int(m,r,Eps*0.5,rans);
}

int main()
{
	for(int T=read(),X,Y,lim; T--; )
	{
		X=read(),Y=read(),lim=X*Y;
		int len=0;
		while(1<<len<=lim) ++len; lim=1<<len;
		if(lim<N)
		{
			--len;
			for(int i=0; i<lim; ++i) A[i]=Com(0,0),rev[i]=(rev[i>>1]>>1)|((i&1)<<len);
			double xx=1.0/X,ans;
			for(int i=0; i<X; ++i) A[i].x=xx;
			FFT(A,lim,1);
			for(int i=0; i<lim; ++i) A[i]=FP(A[i],Y);
			FFT(A,lim,-1);
			for(int i=1,l,r; i<=10; ++i)
			{
				l=read(),r=read(),ans=0;
				for(int j=l; j<=r; ++j) ans+=A[j].x;
				printf("%.7lf\n",ans);
			}
		}
		else
		{
			double l,r,mu=1.0*(X-1)/2,sigma=1.0*(X*X-1)/12/*\sigma^2*/,a=mu*Y,b=sqrt(sigma*Y);
			for(int i=1; i<=10; ++i)
				l=1.0*(read()-a)/b, r=1.0*(read()-a)/b,
				printf("%.7lf\n",Int(0,r,eps,Simpson(0,r))-Int(0,l,eps,Simpson(0,l)));
//				printf("%.7lf\n",Int(l,r,eps,Simpson(l,r)));//WA
		}
	}
	return 0;
}
