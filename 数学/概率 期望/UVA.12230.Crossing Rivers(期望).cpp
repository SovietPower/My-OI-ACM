/*
到达一条河时，船在河中的位置是随机的，所以船到达岸边需要的时间在 0~2l/v 均匀分布，所以船到岸的期望为 (0+2l/v)/2 
过河需要 l/v 的时间，所以过一条河总的期望为 (0+2l/v)/2 + l/v = 2l/v
陆地上的速度是确定的，可以直接先计算出来 
期望是线性的，每条河期望相加即为过河的总期望 
*/
#include<cstdio>
using namespace std;

int main()
{
	int n,d,p,l,v,cas=0;
	while(~scanf("%d%d",&n,&d)&&(n||d))
	{
		double ev=1.0*d;
		for(int i=1;i<=n;++i)
		{
			scanf("%d%d%d",&p,&l,&v);
			ev = ev - l + 2.0*l/v;
			//陆地上速度为1，d即为没有河时的期望时间。有一条河先减掉河占掉陆地的那部分期望，再加上河的期望 
		}
		printf("Case %d: %.3lf\n\n",++cas,ev);
	}

	return 0;
}
