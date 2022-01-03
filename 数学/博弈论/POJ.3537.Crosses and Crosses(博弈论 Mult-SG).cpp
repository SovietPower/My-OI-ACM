/*
1692K 266MS
$Description$
有一个一行n列的棋子，每个人每次往上放一个棋子，将三个棋子连在一起的人赢。问是否有必胜策略。
$Solution$
首先一个人若在i处放棋子，那么另一个人就不能在i-2,i-1,i+1,i+2处放石子，这样会使对方赢。
那么可以看做：在i处放棋子后，另一个人不能选择i-2,i-1,i+1,i+2处放石子，不能放的人输。
可以联想到Nim游戏，一个人取一个石子，另一个人可取石子-2；同时是产生两个局面 
即1*n的棋盘上 在i处放棋子，会将游戏划分成s(i-3)+s(n-i-2)两个游戏 
那这就是Mult-SG游戏，用SG函数解决。
记忆化，O(n^2).

Muti-SG游戏: 
Def: 在符合拓扑原则的前提下，一个单一游戏的后继可以为多个单一游戏。其余规则与SG游戏相同。
对于一个单一游戏，不同方法可能会将其划分为多个单一游戏。每一方法对应的多个单一游戏的(异或)和即可表示这种方法的NP状态。
而这个单一游戏的SG值为其所有方法的SG值的mex 
*/
#include <cstdio>
#include <cstring>
const int N=2002;

int n,sg[N];

int Get_SG(int x)
{
	if(x<0) return 0;
	if(~sg[x]) return sg[x];
	bool vis[N];
	memset(vis,0,sizeof vis);
	for(int i=1; i<=x; ++i)//放所有位置都是子局面 
		vis[Get_SG(i-3)^Get_SG(x-i-2)]=1;//x为偶数时会有重 不过记忆化 无妨 
	for(int i=0; ; ++i)
		if(!vis[i]) return sg[x]=i;
}

int main()
{
	while(~scanf("%d",&n))
		memset(sg,0xff,sizeof sg), puts(Get_SG(n)?"1":"2");
	return 0;
}
