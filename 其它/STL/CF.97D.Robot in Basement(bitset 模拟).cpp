/*
934ms	0KB
考虑怎么暴力，就是先在所有非障碍格子上全放上机器人，然后枚举每一步，枚举每个机器人移动这一步，直到所有机器人都在出口位置。复杂度是$O(nmk)$的。
怎么优化呢，注意到每次移动都是所有机器人一起向同一个方向移动，而我们只关心每个位置上是否有机器人。
可以用`bitset`优化每次移动。把格子编好号后，向上移动就是整体右移$m$位，向左走就是整体右移一位...
还有个问题是，机器人不能往障碍上走。我们可以先把能走的机器人走过去，然后把会撞墙的机器人补回来。
复杂度$O(\frac{nmk}{w})$。
*/
#include <cstdio>
#include <bitset>
#include <cstring>
const int N=153;

std::bitset<N*N> can,ban,now;

int main()
{
	static char s[100005];
	int n,m,K,pos=0; scanf("%d%d%d",&n,&m,&K);
	for(int i=1,now=0; i<=n; ++i)
	{
		scanf("%s",s+1);
		for(int j=1; j<=m; ++j,++now)
		{
			s[j]=='#'?ban[now]=1:can[now]=1;
			if(s[j]=='E') pos=now;
		}
	}
	if(can.count()==1&&can[pos]==1) return putchar('0'),0;
	now=can; scanf("%s",s+1);
	for(int i=1,l=K; i<=l; ++i)
	{
		switch(s[i])
		{
			case 'U': now=(now>>m&can)|(now&(ban<<m)); break;
			case 'D': now=(now<<m&can)|(now&(ban>>m)); break;
			case 'L': now=(now>>1&can)|(now&(ban<<1)); break;
			case 'R': now=(now<<1&can)|(now&(ban>>1)); break;
		}
		if(now.count()==1&&now[pos]==1) return printf("%d\n",i),0;
	}
	puts("-1");

	return 0;
}
