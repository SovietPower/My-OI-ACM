/*
31ms	0KB
$Description$
����$n,b$����$b$������$n!$��ĩβ��ĸ�����
$n\leq10^{18},\ b\leq10^{12}$��
$Solution$
�������⡣������Ҳ��һ�����ѵ����⡣��
���$d=10$��������$n!$�ж��ٸ�$2$��$5$������$c_2,c_5$������$\min\{c_2,c_5\}$��������⡣
���$d\neq10$��ͬ����$d$�������ֽ⣬��$d=\prod_{i=1}^kp_i^{a_i},\ a_i\neq0$���������$n!$���ж��ٸ�$p_i$����Ϊ$c_i$���𰸾���$\min_{i=1}^k\{c_i\}$��
��$n!$��������$p$�ĸ����Ĺ�ʽ��$$f(n)=\left\lfloor\frac{n}{p}\right\rfloor +\left\lfloor\frac{n}{p^2}\right\rfloor +\left\lfloor\frac{n}{p^3}\right\rfloor +\cdots$$
ʵ��д��ʱ��$n$ÿ�γ���$p$���ɣ�����Ҫ��ĸ���ϳ�$p$���ᱬ`long long`������
*/
#include <set>
#include <map>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=1e6+5;

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
LL Calc(LL x,LL y)
{
	LL res=0;
	for(; x; x/=y) res+=x/y;
	return res;
}

int main()
{
	static LL P[N];
	static int tm[N];
	LL n=read(),b=read();
//1
	LL ans=1ll<<60;
	for(int i=2; 1ll*i*i<=b; ++i)
		if(!(b%i))
		{
			LL cnt=1; b/=i;
			while(!(b%i)) b/=i, ++cnt;
			ans=std::min(ans,Calc(n,i)/cnt);
		}
	if(b!=1) ans=std::min(ans,Calc(n,b));
	printf("%I64d\n",ans);
	return 0;
//2
	int t=0;
	for(int i=2; 1ll*i*i<=b; ++i)
		if(!(b%i))
		{
			P[++t]=i, b/=i, tm[t]=1;
			while(!(b%i)) b/=i, ++tm[t];
		}
	if(b!=1) P[++t]=b, tm[t]=1;
	ans=1ll<<60;
	for(int i=1; i<=t; ++i)
	{
		LL cnt=0;
//		for(LL x=P[i]; x<=n&&x>0; x*=P[i]) cnt+=n/x;//��ôд����ֱ�ӱ�longlong����������������= =
		for(LL x=n; x; x/=P[i]) cnt+=x/P[i];
		ans=std::min(ans,cnt/tm[i]);
	}
	printf("%I64d\n",ans);

	return 0;
}
