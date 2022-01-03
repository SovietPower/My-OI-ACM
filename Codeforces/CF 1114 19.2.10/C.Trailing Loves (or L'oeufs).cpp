/*
31ms	0KB
$Description$
给定$n,b$，求$b$进制下$n!$的末尾零的个数。
$n\leq10^{18},\ b\leq10^{12}$。
$Solution$
经典问题。。所以也是一道能搜到的题。。
如果$d=10$，就是求$n!$有多少个$2$和$5$的因子$c_2,c_5$，答案是$\min\{c_2,c_5\}$，不难理解。
如果$d\neq10$，同样对$d$质因数分解，令$d=\prod_{i=1}^kp_i^{a_i},\ a_i\neq0$，依次求出$n!$中有多少个$p_i$，记为$c_i$，答案就是$\min_{i=1}^k\{c_i\}$。
求$n!$中质因子$p$的个数的公式：$$f(n)=\left\lfloor\frac{n}{p}\right\rfloor +\left\lfloor\frac{n}{p^2}\right\rfloor +\left\lfloor\frac{n}{p^3}\right\rfloor +\cdots$$
实际写的时候$n$每次除以$p$即可，不需要分母不断乘$p$，会爆`long long`。。。
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
//		for(LL x=P[i]; x<=n&&x>0; x*=P[i]) cnt+=n/x;//这么写可能直接爆longlong爆成正数啊。。。= =
		for(LL x=n; x; x/=P[i]) cnt+=x/P[i];
		ans=std::min(ans,cnt/tm[i]);
	}
	printf("%I64d\n",ans);

	return 0;
}
