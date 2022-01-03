/*
$Description$
有1个吸血鬼和n-1个人，每天有且只会有两个人/吸血鬼相遇，如果是人与吸血鬼相遇，那个人会有p的概率变成吸血鬼；否则什么也不发生。求n个都变成吸血鬼的期望天数。
$Solution$
我还是写一下吧。。期望题一般倒着递推。
设$f[i]$为当前有$i$个吸血鬼，要变成$n$个吸血鬼的期望天数。那么$f[n]=0$，答案即$f[1]$.
一天要么变一个要么不变，很好想到：
$$f[i]=p_i(f_{i+1}+1)+(1-p_i)(f_i+1)$$
$$p_i*f[i]=p_i*f[i+1]+1$$
$$f[i]=\frac{1}{p_i}+f[i+1]$$
而$$p_i=\frac{C(i,1)*C(n-i,1)}{C(n,2)}*p$$ 
那么$$f[i]=\frac{n*(n-1)}{2*i*(n-i)*p}+f[i+1]$$ 
*/
#include <cstdio>

int main()
{
	int T; scanf("%d",&T);
	long long n; double p,res;
	while(T--)
	{
		scanf("%lld%lf",&n,&p), res=0;
		for(int i=n-1; i>=1; --i)
			res += 1.0*(n*(n-1))/(2.0*i*(n-i)*p);
		printf("%.3lf\n",res);
	}
	return 0;
}
