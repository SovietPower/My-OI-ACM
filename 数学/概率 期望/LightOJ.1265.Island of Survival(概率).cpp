/*
题意：岛上有t只老虎，1个人，d只鹿。每天随机有两个动物见面 
1.老虎和老虎碰面，两只老虎就会同归于尽；
2.老虎和人碰面或者和鹿碰面，老虎都会吃掉对方；
3.人和鹿碰面，人可以选择吃或者不吃该鹿；
4.鹿和鹿碰面，相安无事；
求最后人活下来的最大期望概率。 

思路：人要活下来，一定是所有的老虎都死亡，而老虎只能和老虎两两同归于尽。 
所以如果老虎数量为奇数，那鹿总有一天会被吃完，人一定不能存活；
如果老虎数量为偶数，则考虑老虎同归于尽的概率即可。 
因为鹿不会对人和老虎的数量产生任何影响，只有老虎对人存活产生影响；老虎唯一死亡的方式就是两只老虎碰面。 
所以可以忽略鹿。在无限时间里，只要有老虎，鹿是一定被吃光的。
计算：不考虑鹿，总的可能数是C[t+1,2],即老虎和人中选2个；
从t个老虎中选择两个的总数是C[t,2]。所以每次两只老虎同归于尽的概率是 C[t,2]/C[t+1,2] = (t-1)/(t+1)
答案就是所有概率相乘。(老虎的数量是一直在改变的)

从题目出发对问题进行简化。 
*/
#include<cstdio>
#include<cctype>
using namespace std;

inline int read()
{
	int now=0;register char c=getchar();
	for(;!isdigit(c);c=getchar());
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now;
}

int main()
{
	int ts=read(),ks=0,t,d;
	double ans;
	while(ts--)
	{
		t=read(),d=read();
		if(t&1)
		{
			printf("Case %d: 0\n",++ks);
			continue;
		}
		ans=1.0;
		while(t)
		{
			ans*=1.0*(t-1)/(t+1);
			t-=2;
		}
		printf("Case %d: %.7lf\n",++ks,ans);
	}

	return 0;
}
