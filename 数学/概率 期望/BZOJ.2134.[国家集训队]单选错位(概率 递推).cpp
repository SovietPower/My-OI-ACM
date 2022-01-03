/*
820kb	836ms
如题目中的公式，我们只要把做对每个题的概率加起来就可以了(乘个1就是期望)。
做对第i道题的概率 
$$P_i=\frac{1}{max(a_{i-1},a_i)}$$ 
原式是 $P_i=\frac{min(a_{i-1},a_i)}{a_{i-1}\times a_i}$，化简后得到上式。
例：假设第i-1道有3个选项，第i道有5个选项，暴力一点，那么做对就是从3个中选1个和从5个中选1个相同的概率， 
概率为 $\frac{1}{3}\times\frac{1}{5}+\frac{1}{3}\times\frac{1}{5}+\frac{1}{3}\times\frac{1}{5}=\frac{min(3,5)}{3\times 5}$ 
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
