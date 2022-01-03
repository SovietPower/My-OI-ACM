/*
332K 0MS
$Description$
一个1~INF的坐标轴上有n个棋子，给定坐标Pi。棋子只能向左走，不能跨越棋子，且不能越界(<1)。两人每次可以将任意一个可移动的棋子向左移动一个单位。问先/后手会赢或是否无解。
$Solution$
首先考虑相邻两个棋子 
无论一个人怎么移动前边的棋子，后手都能移动后面棋子同样的距离使得这两个棋子间间隔不变 
同时两个棋子局面的终止是两个棋子相邻 
不难想到以这两个棋子间距离为石子数做一个Nim游戏 
那扩展到n个棋子？
**两两配对**，对于每一对看做一个Nim游戏 
当棋子数为奇数时需要将第一个棋子和点1看做一对 
状态是有限的 不会无解 
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()

int A[1005];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int t=read(),n,res,i;
	while(t--)
	{
		n=read();
		for(i=1; i<=n; ++i) A[i]=read();
		std::sort(A+1,A+1+n);
		if(n&1)
			for(res=A[1]-1,i=2; i<=n; i+=2)
				res^=(A[i+1]-A[i]-1);
		else
			for(res=0,i=1; i<=n; i+=2)
				res^=(A[i+1]-A[i]-1);
		puts(res?"Georgia will win":"Bob will win");
	}
	return 0;
}
