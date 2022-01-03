/*
171ms	1500KB
$Description$
有两条平行于$x$轴的直线$A,B$，每条直线上的某些位置有传感器。你需要确定$A,B$轴上任意两个整点位置$x_A,x_B$，使得一条光线沿$x_A\to x_B$射出（碰到$A,B$后反射），能够碰到的传感器数量最多是多少。
$Solution$
~~由光的反射定律可知，~~光束上相邻两个点的水平距离是确定的，设这个距离为$dx$（纵坐标就没有什么用了）。
那么会被从$x_A$出发的光束照到的点，在$A$轴上满足坐标为$x_A+2k\cdot dx$；在$B$轴上满足坐标为$x_A+(2k-1)\cdot dx$。
我们发现若$dx=a\cdot b$，$a$为奇数，$b$为$1$或偶数，则$dx'=\frac{dx}{a}=b$会碰到所有$dx$会碰到的点，即不会更差。
换句话说就是，所有$dx=奇数$可以被$dx'=1$取代，$dx=偶数$可以被$dx'=某个2的幂$取代。
所以存在（除$1$外的）奇数因子的$dx$没有必要判断。那么我们只需要判断$dx=2^l,l\geq 0$的情况。这一共有$\log(10^9)$种。
对于一个确定的$dx$，如果$A$轴上两个点$x_1,x_2$同时被碰到，那么满足$x_1\equiv x_2\mod{(2 \cdot dx)}$；
如果选了$A$轴上的$x_1$，$B$轴上的一个点$x_2$想要被碰到，就要满足$x_1+dx\equiv x_2\mod{(2 \cdot dx)}$。
所以我们把$A$点集中的每个$x_i$对$2dx$取模，$B$组中的每个$x_i$减掉一个$dx$再对$2dx$取模）。
然后把余数相同的分为一组，点数最多的一组就是当前最优解。
sort或直接map都可以。复杂度$O(n\log n\log(10^9))$。
注意$ans$初始是$2$。。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 150000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=2e5+5;

int n,A[N],tmp[N],Now;
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read(); read();
	for(int i=1; i<=n; ++i) A[i]=read();
	int m=read(),tot=n+m; read();
	for(int i=n+1; i<=tot; ++i) A[i]=read();

	int ans=2/*!*/; tmp[tot+1]=2e9+1;
	for(int dx=1; dx<=int(1e9); dx<<=1)
	{
		int mod=dx<<1;
		for(int i=1; i<=n; ++i) tmp[i]=A[i]%mod;
		for(int i=n+1; i<=tot; ++i) tmp[i]=(A[i]+dx)%mod;
		std::sort(tmp+1,tmp+1+tot);
		for(int i=1,las=1; i<=tot; ++i)
			if(tmp[i+1]!=tmp[i]) ans=std::max(ans,i-las+1), las=i+1;
	}
	printf("%d\n",ans);

	return 0;
}
