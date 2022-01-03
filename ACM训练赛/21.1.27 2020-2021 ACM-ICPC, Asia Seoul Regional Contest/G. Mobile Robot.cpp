/*
514ms	15700KB
$Description$
给定$n$个机器人及其位置$p_i$，和一个数$d$，你需要给每个机器人找一个新位置$p'_i$使得机器人从$1$到$n$所在位置为公差为$d$的等差数列，求最小的$\max_{i=1}^n|p_i-p'_i|$。
$n\leq10^6$。
$Solution$
其实比较有意思。只要第一个位置$x$确定，其它位置即$x\pm(i-1)d$，所以就是使$\max|p_i-x\pm(i-1)d|=\max|(p_i\pm(i-1)d)-x|=\max|A_i-x|$最小。$x$任取，显然$\max A_i-\min A_i$除以$2$即为答案。
注意整数即使只是除以$2$，保留一位小数也会有精度误差。。（不是$X.5$）所以要手动输出$X.5$。
还有常数$5$是个`int`型变量输出要用`%d`。。（运算没问题，编译器旧点输出会有点问题）
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=1e6+5;
const LL INF=1e17;

LL p[N];

inline LL read()
{
	LL now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	int n=read(); LL d=read(),A;
	for(int i=1; i<=n; ++i) p[i]=read();

	LL mn=INF,mx=-INF;
	for(int i=1; i<=n; ++i) A=p[i]-(i-1)*d, mn=std::min(mn,A), mx=std::max(mx,A);
	LL ans=mx-mn;

	mn=INF,mx=-INF;
	for(int i=1; i<=n; ++i) A=p[i]+(i-1)*d, mn=std::min(mn,A), mx=std::max(mx,A);
	ans=std::min(ans,mx-mn);
	printf("%lld.%lld\n",ans/2,ans%2?5ll:0ll);//%.1f不行！ 常数输出时要保证是longlong。。
	

	return 0;
}
