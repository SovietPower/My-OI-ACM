/*
820kb	836ms
����Ŀ�еĹ�ʽ������ֻҪ������ÿ����ĸ��ʼ������Ϳ�����(�˸�1��������)��
���Ե�i����ĸ��� 
$$P_i=\frac{1}{max(a_{i-1},a_i)}$$ 
ԭʽ�� $P_i=\frac{min(a_{i-1},a_i)}{a_{i-1}\times a_i}$�������õ���ʽ��
���������i-1����3��ѡ���i����5��ѡ�����һ�㣬��ô���Ծ��Ǵ�3����ѡ1���ʹ�5����ѡ1����ͬ�ĸ��ʣ� 
����Ϊ $\frac{1}{3}\times\frac{1}{5}+\frac{1}{3}\times\frac{1}{5}+\frac{1}{3}\times\frac{1}{5}=\frac{min(3,5)}{3\times 5}$ 
*/
#include <cstdio>
#include <algorithm>
#define mod (100000001)

int n,A,B,C,a_1;

int main()
{
	scanf("%d%d%d%d%d",&n,&A,&B,&C,&a_1);
	double res=0;
	int pre=a_1, a_pre=a_1%C+1, now, a_now;
	for(int i=2; i<=n; ++i)
	{
		now=(1ll*pre*A+B)%mod, a_now=now%C+1;
		res+=1.0/std::max(a_pre,a_now);
		pre=now, a_pre=a_now;
	}
	res+=1.0/std::max(a_1%C+1,a_now);
	printf("%.3lf",res);

	return 0;
}
