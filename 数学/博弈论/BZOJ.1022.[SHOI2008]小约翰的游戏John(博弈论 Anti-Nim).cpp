/*
Anti-Nim游戏： 
先手必胜当且仅当： 
1.所有堆的石子数为1，且异或和为0 
2.至少有一堆石子数>1，且异或和不为0 
简要证明：
对于1：若异或和为1，则有奇数堆；异或和为0，则有偶数堆。比较显然。
对于2：(1)对于只有一堆石子数>1的情况(异或和一定不为0)，先手可以操作这堆石子 将场面变为奇数堆个数都为1的石子堆 
(2)对于至少有两堆石子数>1的情况：
- 若异或和=0，先手必败 
- 若异或和!=0，先手必胜 
类似Nim的证明，若异或和=0，则怎样操作都会使异或和!=0；若异或和!=0，则一定有一步能使异或和=0.(NP性质的转换)
这两种状态不断转换，总会在某一时刻变为2.(1)中的状态，即一个必胜态，而这个必胜态是由异或和=0时转移来的。
即异或和=0时一定会在某一时刻转移到一个必胜状态。
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

int main()
{
	int t=read(),n,res,a; bool f;
	while(t--)
	{
		n=read(), f=res=0;
		while(n--)
			a=read(), a>1?f=1:0, res^=a;
		puts(f^(res>0)?"Brother":"John");
	}
	return 0;
}
