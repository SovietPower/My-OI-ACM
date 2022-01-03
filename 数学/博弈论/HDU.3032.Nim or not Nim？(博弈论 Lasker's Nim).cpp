/*
$Description$
有多堆石子, 每次可以将任意一堆拿走任意个或者将这一堆分成非空的两堆, 拿走最后一颗石子的人胜利。问谁会获得胜利。
$Solution$
Lasker's Nim游戏 
这个问题可以用SG函数来解决。
首先，操作(1)和Nim游戏没什么区别，对于一个石子数为k的点来说，后继可以为0…k-1。
而操作(2)实际上是把一个游戏分成了两个游戏，这两个游戏的和为两个子游戏的SG函数值的异或。
而求某一个点的SG函数要利用它的后继，它的后继就应该为 当前局面能产生的所有单一游戏，以及当前局面所有能分成的多个单一游戏 的游戏的和。
比如，状态3的后继为0,1,2,(1^2=3)，其SG值为4 
通过打表可以得到结论： 
if(x%4 == 0) sg(x)=x-1;
if(x%4 == 1||2) sg(x)=x;
if(x%4 == 3) sg(x)=x+1;
*/
#include <cstdio>
#include <cctype>
#define gc() getchar()

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int SG(int x)
{
	if(!(x%4)) return x-1;
	else if(x%4==3) return x+1;
	return x;
}

int main()
{
	int t,n,res; scanf("%d",&t);
	while(t--)
	{
		n=read(), res=0;
		while(n--) res^=SG(read());
		puts(res?"Alice":"Bob");
	}
	return 0;
}
