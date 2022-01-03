/*
$Description$
两人轮流走，每次可以从盒子(容量给定)中取出任意堆石子加入Nim游戏，或是拿走任意一堆中正整数个石子。无法操作的人输。10组数据。
$Solution$
考虑简化当前局面 
1.若先手从盒子中拿出异或和为0的几堆石子，即建立了一个先手必败(第一步由后手来走)的Nim游戏，先手一定可以最后把这些石子取完 
但是先手不会给后手机会添加异或和为0的石子 或是 最后新建一个异或和为0的Nim，会取尽量多的异或和为0的石子堆 
所以后手只能添加异或和不为0的石子加入游戏，此时游戏异或和不为0，先手可以将异或和变为0，于是后手必败 
2.若先手无法从盒子中拿出异或和为0的石子，则建立了一个先手必胜的Nim游戏 
(1)后手可以取这堆石子将其异或和变为0，先手如果取 后手会先取完，没什么意义；先手如果不取，加入几堆异或和仍不0的石子，现在异或和也仍不为0，也没什么意义 
(2)后手如果不取这堆石子，可能将游戏异或和变为0，又到了(1)；若其异或和不为0，则也又建立了一个先手必胜的游戏 
但是后手一定可以让先手后开始进行Nim游戏，即后手一定可以先开始这个先手必胜的游戏。所以后手必胜。
找序列中是否存在异或和为0的子序列，可以DFS，也可以高斯消元。不过n<=14.
*/
#include <cstdio>
#include <cctype>
#define gc() getchar()
const int N=17;

int n,A[N],vic;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void DFS(int x,int sum,bool sel)//至少选一个元素 
{
	if(vic) return;
	if(x>n) {if(!sum&&sel) vic=1; return;}
	DFS(x+1,sum^A[x],1), DFS(x+1,sum,sel);
}

int main()
{
	int t=10;
	while(t--)
	{
		n=read(), vic=0;
		for(int i=1; i<=n; ++i) A[i]=read();
		DFS(1,0,0);
		puts(vic?"NO":"YES");//数据错了 输出是反的 
	}
	return 0;
}
