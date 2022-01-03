/*
764ms	97900KB
$Description$
有$n$个多重集合，初始都为空。有$q$次操作，操作共四种：
$1\ x\ v$：将第$x$个集合赋值为$\{v\}$。
$2\ x\ y\ z$：把第$x$个集合设为第$y$个集合与第$z$个集合的并。
$3\ x\ y\ z$：把第$x$个集合设为$\{\gcd(a,b)|a\in y,b\in z\}$。
$4\ x\ v$：询问第$x$个集合中，数字$v$出现次数模$2$后的值。
$n\leq10^5,\ q\leq10^6$，出现的所有数字均为正整数且$\leq7000$。
$Solution$
先考虑第三个类似卷积的操作如何处理。题解用到了类似$FFT$的方法，将“卷积”转化成对应位置的“点值”分别进行运算。
在$x$位置处，不去维护数字$x$的出现次数，而是维护$x$所有倍数的出现次数。这样就可以对不同位置的点值分别维护“$\gcd$卷积”啦。
比如$y$集合中$x$的倍数有$a$个，$z$集合中$x$的倍数有$b$个，那么“卷积”之后$x$的倍数就有$a*b$个（而且这个$a,b$与其它位置的值互不影响）。
具体实现，因为只需要判断奇偶性，拿一个大小为$7000$的$bitset\ A_i$。操作二就是$A_y\ ^{\wedge}A_z$（加），操作三就是$A_y\&A_z$（乘）。
但是查询的时候需要容斥：$Ans=A_x-A_{2x}-A_{3x}+A_{6x}$...注意到容斥系数只有$\mu=1$或$-1$，而$1\equiv-1(mod\ 2)$，所以直接把$\mu(i*x)\neq0$的这些位置上的值加起来就好，也就是全与起来再模$2$。
这样每次操作的复杂度都是$O(\frac{7000}{w})$。
*/
#include <cstdio>
#include <cctype>
#include <bitset>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5,M=7001;

int mu[N];
std::bitset<M> A[N],ori[M],Mu[M];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
void Init()
{
	static int P[M>>3];
	static bool notP[M];
	mu[1]=1;
	for(int i=2,cnt=0; i<M; ++i)
	{
		if(!notP[i]) P[++cnt]=i, mu[i]=-1;
		for(int j=1,v; j<=cnt&&(v=P[j]*i)<M; ++j)
		{
			notP[v]=1;
			if(!(i%P[j])) break;
			mu[v]=-mu[i];
		}
	}
}

int main()
{
	Init();
	for(int i=1; i<M; ++i)
		for(int j=i; j<M; j+=i)
			ori[j][i]=1, Mu[i][j]=(mu[j/i]!=0);

	for(int n=read(),q=read(),x,y,z,v; q--; )
		switch(read())
		{
			case 1: x=read(),v=read(),A[x]=ori[v]; break;
			case 2: x=read(),y=read(),z=read(),A[x]=A[y]^A[z]; break;
			case 3: x=read(),y=read(),z=read(),A[x]=A[y]&A[z]; break;
			case 4: x=read(),v=read(),putchar(48+((A[x]&Mu[v]).count()&1)); break;
		}
	return 0;
}
