/*
### $Description$
��һ��$n$�������ȫͼ����$0$��$n-1$��ţ�ÿ����$i,j$��ı�ȨΪ$i\oplus j$��������С��������Ȩ֮�͡�
### $Solution$
Ϊ���㣬���µ��$0$��$n$��š�
ÿ����$x$Ӧ��$x\oplus lowbit(x)$��������ȨΪ$lowbit(x)$��$lowbit(x)$���$0$����������һ���ܹ������������Դ�Ϊ$\sum_{i=1}^nlb(i)$��
�����Ż���ע�⵽$lb(i)$һ����ĳ��2���ݣ�������$f(i)$��ʾ$1\leq x\leq n$������$lb(x)=i$��$x$�ĸ��������Ϊ$\sum_{i=1}^nf(i)\times i\ (f(i)>0)=\sum_{i=0}^{\lfloor\log n\rfloor}f(2^i)\times 2^i$
$f(i)$��Ȼ��������λDP�㣬����̫�鷳�ˡ���
һЩ����$lb(i)=x$���������Ǽ��������$2x$������$x=(100)_2$����$i=100,1100,10100...$(���$1000$)������$f(x)=\lfloor\frac{n-x}{2x}\rfloor+1\ (1\leq x\leq n,x=2^y)$��
����DP�������ó���...�Ȳ����ˡ�
*/
#include <cstdio>

int main()
{
	long long n,res=0;
	scanf("%I64d",&n); --n;
	for(long long x=1; x<=n; x<<=1)
		res+=x*((n-x)/(x<<1)+1);
	printf("%I64d\n",res);

	return 0;
}
