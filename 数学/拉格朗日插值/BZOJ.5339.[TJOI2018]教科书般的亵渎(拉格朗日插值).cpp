/*
824kb	36ms
�����һ��˵����
$k$�η����$k$�ǹ̶��ģ�Ҳ���������Ҫ���������£�ÿ�β���ı䣻
��ĳ�������������������²���Ʒ֡�

���ѷ��ֵ�ǰ����������ǿո���+1����$m+1$��
���ײ���д�ɣ�$\sum_{i=1}^ni^{m+1}-\sum_{i=1}^mA_i^{m+1}$��ע���ʱ��$A_i$��ʣ�µĿո񣨾��忴��������µı������ְɣ���
��������������$\sum_{i=1}^ni^{m+1}$����Ȼ���ݺ��кܶ����󷨡�
����д��ֵ������
$\sum_{i=1}^ni^{m}$��һ����$n$Ϊ�Ա�����$m+1$�ζ���ʽ�����Ǵ���$m+2$����Ϳ������������ղ�ֵ�����$f(n)$�ˡ�
������$x$ֵ�������Ϳ�����ǰ׺������׺���ͽ׳˽��������ղ�ֵ�Ż���$O(n)$���㵥�㺯��ֵ����������棩��
���Ӷ�$O(Tm^2)$��

дһ���������ղ�ֵ��ʽ�Ӽ�ʵ�֣�
$$f(x)=\sum_{i=0}^ny_i\prod_{j\neq i}\frac{x-x_i}{x_i-x_j}$$

��$x_i$ȡ$i$ʱ��
$$f(x)=\sum_{i=0}^ny_i\prod_{j\neq i}\frac{x-i}{i-j}$$

����$x$��Ԥ����ǰ׺������׺����$pre_j=\prod_{i=0}^jx-x_i,\;suf_j=\prod_{i=j}^nx-x_i$��
���ѷ�������ʽ�ӵķ��Ӿ���ǰ׺���˺�׺������ĸ�������׳���ˣ�ע����з������⣩�����Ծ��ǣ�
$$f(x)=\sum_{i=0}^ny_i\frac{pre_{i-1}\times suf_{i+1}}{i!\times(n-i)!}$$

�Ϳ���$O(n)$����$f(x)$�ˡ�
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
int F(const int x,const int m)//��_{i=1}^x i^m �Ա���Ϊx��m+1�ζ���ʽ ��x����ȡֵ 
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
		for(int i=1; i<=m; ++i) A[i]%=mod;//sort����ȡģ��

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
