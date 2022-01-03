/*
824kb	28ms
���⼴��
$$\sum_{i=0}^n\sum_{j=1}^{a+id}\sum_{x=1}^jx^k$$

����֪�����һ��$\sum$����Ȼ���ݺͣ���$f(n)=\sum_{x=1}^nx^k$������һ��$k+1$�ζ���ʽ�����Բ�ֵ�����
��$g(n)=\sum_{i=1}^nf(i)$��(���)��ֿ�֪����һ��$k+2$�ζ���ʽ��
ͬ����$h(n)=\sum_{i=0}^ng(a+id)$��ͬ����ֿ�֪����һ��$k+3$�ζ���ʽ��
�������������ղ�ֵ���Ǵ���$k+4$��ֵ�Ϳ������$h(n)$�ˡ�
Ҳ��������$k+3$��$f(x)$��ֵ�������$k+3$��$g(x)$��ֵ��Ȼ���$g$��ֵ��$k+4$��$g(a+xd)$��ǰ׺��һ�¾�����$h$��$k+4$��ֵ��Ȼ���ٲ�һ�ξ͵õ�$h(n)$�ˡ���Ƕ�׺ù���...��

ע��$f,g,h$���Ǹ�ǰ׺��...
ע������������ģ���ᱬint��������`unsigned int`��

��������Կ�����
1. ��һ��$\sum$һ���ʹ����ʽ����+1��
2. ��ֵ����Ƕ�ף��Ҹ��ӶȲ��䣬����$O(k^2)$��
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
	ifac[N-1]=1119688141;//��129!����Ԫ����129��!!!����������������������=-= 
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
