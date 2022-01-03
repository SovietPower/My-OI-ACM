/*
27192kb	820ms
真的题意不明啊。。
$Description$
你有k次选择的机会，每次将从n种物品中随机一件给你，你可以选择选或不选。选择它会获得这种物品的价值；选择一件物品前需要先选择某些种物品每种至少一件。
物品价值可能有负。问在最优策略下期望得分。
$Solution$
并不像期望DP。。(这题倒推也不是因为像期望DP那样)
最优解我以为还要贪心，其实只需要在枚举过程中取个max。。
数据范围显然可以用f[i][s]表示当前是第i次，选择过的物品的集合为s时的最大期望得分。
枚举次数i，枚举当前集合状态s，再枚举出现的物品：若能选，在选与不选间取max；不能选直接转移(加上)。每个物品的概率都是1/n，之后再除以n就是状态的期望得分。
这样只能从有转移到无或有。
如果正推的话，在枚举当前状态时，会得到的状态可能是各种各样的，不好算(必须要算出概率，小到存不下？)；而且最终状态集合需要枚举？(我也没写过，应该会特别麻烦。。见xxy博客)
(别人是说可能从无效到有效。。方式不同吧 我想的其实和倒推差不了多少)
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()

int K,n,need[17],val[17];
double f[103][(1<<15)+3];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	K=read(),n=read();
	for(int v,i=0; i<n; ++i)
		for(val[i]=read(),v=read(); v; v=read())
			need[i]|=(1<<v-1);
	int lim=1<<n;
	for(int i=K; i; --i)
		for(int j=0; j<lim; ++j)
		{
			for(int k=0; k<n; ++k)
				if((j&need[k])==need[k])
					f[i][j]+=std::max(f[i+1][j],f[i+1][j|(1<<k)]+val[k]);
				else f[i][j]+=f[i+1][j];
			f[i][j]/=n;
		}
	printf("%.6lf",f[1][0]);

	return 0;
}
