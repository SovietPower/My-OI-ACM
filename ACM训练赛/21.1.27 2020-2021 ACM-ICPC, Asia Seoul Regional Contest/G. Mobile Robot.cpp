/*
514ms	15700KB
$Description$
����$n$�������˼���λ��$p_i$����һ����$d$������Ҫ��ÿ����������һ����λ��$p'_i$ʹ�û����˴�$1$��$n$����λ��Ϊ����Ϊ$d$�ĵȲ����У�����С��$\max_{i=1}^n|p_i-p'_i|$��
$n\leq10^6$��
$Solution$
��ʵ�Ƚ�����˼��ֻҪ��һ��λ��$x$ȷ��������λ�ü�$x\pm(i-1)d$�����Ծ���ʹ$\max|p_i-x\pm(i-1)d|=\max|(p_i\pm(i-1)d)-x|=\max|A_i-x|$��С��$x$��ȡ����Ȼ$\max A_i-\min A_i$����$2$��Ϊ�𰸡�
ע��������ʹֻ�ǳ���$2$������һλС��Ҳ���о�������������$X.5$������Ҫ�ֶ����$X.5$��
���г���$5$�Ǹ�`int`�ͱ������Ҫ��`%d`����������û���⣬�������ɵ�������е����⣩
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
	printf("%lld.%lld\n",ans/2,ans%2?5ll:0ll);//%.1f���У� �������ʱҪ��֤��longlong����
	

	return 0;
}
