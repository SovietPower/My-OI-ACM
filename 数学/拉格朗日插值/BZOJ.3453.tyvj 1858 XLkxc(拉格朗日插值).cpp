/*
824kb	28ms
题意即求
$$\sum_{i=0}^n\sum_{j=1}^{a+id}\sum_{x=1}^jx^k$$

我们知道最后一个$\sum$是自然数幂和，设$f(n)=\sum_{x=1}^nx^k$，这是一个$k+1$次多项式，可以插值求出。
令$g(n)=\sum_{i=1}^nf(i)$，(打表)差分可知这是一个$k+2$次多项式。
同样令$h(n)=\sum_{i=0}^ng(a+id)$，同样差分可知这是一个$k+3$次多项式。
所以用拉格朗日插值我们代入$k+4$个值就可以求出$h(n)$了。
也就是先求$k+3$个$f(x)$的值，再求出$k+3$个$g(x)$的值，然后对$g$插值求$k+4$个$g(a+xd)$，前缀和一下就有了$h$的$k+4$个值，然后再插一次就得到$h(n)$了。（嵌套好鬼畜...）

注意$f,g,h$都是个前缀和...
注意这题两倍的模数会爆int。可以用`unsigned int`。

从这题可以看出：
1. 多一个$\sum$一般会使多项式次数+1。
2. 插值可以嵌套，且复杂度不变，仍是$O(k^2)$。
*/
#include <cstdio>
#include <algorithm>
#define mod 1234567891
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
typedef long long LL;
typedef unsigned int uint;
const int N=130;

uint g[N],h[N],ifac[N];

inline uint FP(uint x,uint k)
{
	uint t=1;
	for(; k; k>>=1,x=1ll*x*x%mod)
		if(k&1) t=1ll*t*x%mod;
	return t;
}
uint Lagrange(uint *y,const int m,uint x)
{
	static uint pre[N],suf[N];
	pre[0]=x, suf[m+1]=1;
	for(int i=1; i<m; ++i) pre[i]=1ll*pre[i-1]*(x+mod-i)%mod;
	for(int i=m; i; --i) suf[i]=1ll*suf[i+1]*(x+mod-i)%mod;
	LL ans=0;
	for(int i=0,up,down; i<=m; ++i)
	{
		if(i) up=1ll*pre[i-1]*suf[i+1]%mod*y[i]%mod;
		else up=1ll*suf[i+1]*y[i]%mod;
		down=(m-i)&1?mod-1ll*ifac[i]*ifac[m-i]%mod:1ll*ifac[i]*ifac[m-i]%mod;
		ans+=1ll*up*down%mod;
	}
	return ans%mod;
}

int main()
{
	ifac[N-1]=1119688141;//是129!的逆元不是129的!!!今天错了两次这个真是醉了=-= 
	for(int i=N-1; i; --i) ifac[i-1]=1ll*ifac[i]*i%mod;

	int T,K; uint a,n,d; g[0]=0;
	for(scanf("%d",&T); T--; )
	{
		scanf("%d%u%u%u",&K,&a,&n,&d);
		for(int i=1; i<=K+2; ++i) g[i]=g[i-1]+FP(i,K), Mod(g[i]); //f = \sum i^k
		for(int i=1; i<=K+2; ++i) Add(g[i],g[i-1]); //g = \sum f(i)
		h[0]=Lagrange(g,K+2,a);
		for(int i=1; i<=K+3; ++i) Add(a,d), h[i]=h[i-1]+Lagrange(g,K+2,a), Mod(h[i]);
		printf("%d\n",(int)Lagrange(h,K+3,n));
	}
	return 0;
}
