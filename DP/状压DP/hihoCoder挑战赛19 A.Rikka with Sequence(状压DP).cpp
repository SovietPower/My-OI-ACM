/*
$Description$
![](https://img2018.cnblogs.com/blog/1143196/201810/1143196-20181013075426036-577478146.png)
给定$n$个数$a_i$，求有多少个子集满足：其异或和等于其所有数的AND。
$n\leq 50,\ a_i\lt 2^{13}$。
$Solution$
https://www.cnblogs.com/SovietPower/p/9781573.html
暴力：f[i][j][k]表示前$i$个数，与起来为j，异或和为k的方案数。复杂度$O(n*4^{13})$。
考虑位运算的性质，最后怎么得到某一位的1：&要求所有数这一位为1，^只需判这一位为1的数的奇偶性。
所以我们用13位三进制s表示13位01的状态（2表示全1，0/1表示奇偶性），再存一下选的数的个数。
这样DP就是$O(n*3^{13})$了。
但是直接f[i][s][0/1]不会写啊，求路过dalao教。。（拆状态好像也挺麻烦）
记异或和为x，位与和为y，因为是与，所以x再与y和y是有关系的，也就是当选了奇数个数时，x&y=y；否则x&y=0。
那么暴力中的合法的$j,k$实际没有$2^{13}*2^{13}$那么多。
所有合法状态满足x&y=y或是x&y=0，也就是y要么是x的子集，要么与x没有交集（别忘这种情况）。
因为有第二种情况所以只求异或和的所有子集不行。但再求一遍补集存状态也不对。
令xx=x&(~y)，我们发现xx还是确定的？而且因为x,y的关系，选奇数个时x就是xx|y，否则x=xx。
我们枚举y，再枚举~y的子集（要&8191）得到xx，在DP的时候根据奇偶性把x转化出来就行了（得状态再&(~y)）。然后就可以同暴力直接转移。
状态数为$O(3^{13})$。
答案是$f[n][status(0,0)][0]+\sum_s f[n][status(s,s)][1]$。
复杂度也是$O(n*3^{13})$。
DP数组也要longlong（随机的话倒也爆不了int）。
id[][]按枚举顺序确定下标会快近一倍。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define all 8191
#define cnt 1594323
typedef long long LL;
const int N=8192+3,M=1594323+3;

int And[M],XX[M],id[N][N];
LL F[M][2],G[M][2];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Init()
{
	int n=0;
	for(int y=0; y<=all; ++y)//y
	{
		int ss=(~y)&all;
		for(int x=ss; ; x=(x-1)&ss)
		{
			id[y][x]=++n;
			XX[n]=x, And[n]=y;
			if(!x) break;
		}
	}
	return n;
}

int main()
{
//	const int all=8191;
//	const int cnt=1594323;
	Init();
	int n=read(); LL (*f)[2]=F,(*g)[2]=G;
	f[id[all][0]][0]=1;
	for(int i=1,ai; i<=n; ++i)
	{
		ai=read(), std::swap(f,g);
		memcpy(f,g,sizeof F);//f[i][s]=f[i-1][s]
		for(int j=1; j<=cnt; ++j)
			for(int k=0; k<2; ++k)
			{
				if(!g[j][k]) continue;
				int x=XX[j],y=And[j];
				k && (x|=y);
				x^=ai, y&=ai;
				x&=(~y);
				f[id[y][x]][k^1]+=g[j][k];
			}
	}
	LL ans=f[id[0][0]][0];
	for(int i=1; i<=cnt; ++i) if(!XX[i]) ans+=f[i][1];//x==y xx=0
	printf("%lld\n",ans);

	return 0;
}
