/*
��Ŀ����Ҫ��$$\sum_{k=1}^n\sum_{a=1}^k\sum_{b=1}^k[k\mid a\times b]$$
ʵ�����ǿ�����$$\sum_{k=1}^n\sum_a\sum_b\sum_c[a\times b\times c=k]$$
��ʵ�ʾ�����$$\sum_a\sum_b\sum_c[a\times b\times c\leq k]$$
Ҳ����$a\times b\times c\leq k$��������Ԫ���������
��ô����ö��$a\leq b\leq c$��ͳ�����ж��ٸ�������ٳ���������
����$a$ֻ��ö�ٵ�$\sqrt[3]n$��$b$��Ҫö�ٵ�$\sqrt{\frac na}$��
$a=b=c$ʱ������ֻ��$1$�������������ʱ������ֻ��$3$�������ľͳ�$3!=6$��
*/
#include <cmath>
#include <cstdio>
#define mod 2333
typedef long long LL;

int main()
{
	LL n; scanf("%lld",&n);
	int ans=0;
	for(int a=1; 1ll*a*a*a<=n; ++a)
	{
		ans=(ans+1+3*(n/a/a-a))%mod;
		LL t=n/a;
		for(int b=a+1,l=sqrt(t); b<=l; ++b)
			ans=(ans+3/*ÿ��ö�ٵ�b,c�����Ե���b*/+6*(t/b-b))%mod;
	}
	printf("%d\n",ans%mod);

	return 0;
}
