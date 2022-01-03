/*
940kb	820ms
同样按位考虑，假设$m=1$。
我们要在一堆$01$中填$\&$和$|$。注意到对于任意数$x$，$x\&0=0$，$x\&1=x$，$x|0=x$，$x|1=1$。也就是$\&1$和$|0$没有影响，而$\&0$和$|1$相当于直接赋值。
如果要求最后结果是$1$，那我们要在某个$1$前面填$|$，且这之后的位置只能$1$前填$\&$、$0$前填$|$；若最后结果是$0$，同理找到某个$0$在前面填$\&$，后面位置的$1$前填$\&$、$0$前填$|$。
令`&`=1，`|`=0，然后设操作串=$y$，从后往前是从高位到低位，那如果$x>y$最后结果是$1$，如果$x<y$结果是$0$（很好理解，因为要找到从后往前第一个不同的位置，就是难想到...）。
因为初始是$0$所以$x=y$是结果也是$0$。
也就是说，这一位要求是$1$，则有$y<x$；要求是$0$，有$y\geq x$。
扩展到$m$位，对于每一次询问就可以得到$m$个这样的不等式，设解出来是$l\leq y<r$，答案就是$r-l$。

怎么做解决了，但是直接实现起来还是有点麻烦...
可以先将$m$个$x$从小到大排序，对于询问$s$就`for`一遍找到$s_i=1$的位置上最小的$x$记作$r$，再`for`一遍找到$s_i=0$的位置上最大的$x$记作$l$，答案就是$\max(r-l,0)$（注意初始$l=0,r=2^m$...）。
可以基数排序，然而不会~~`sort`还是会的~~...感觉后缀数组白学了= =
每次以当前是$0$是$1$为第一关键字，之前的排名为第二关键字，背一下SA的板子就好了...

复杂度$O((n+q)m)$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define mod 1000000007
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
#define gc() getchar()
typedef long long LL;
const int N=5005;

int rk[N],tmp[N],pw[N],x[N],X[N],s[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void Read(int n)
{
	register char c=gc(); while(c!='0'&&c!='1') c=gc();
	s[1]=c-48;
	for(int i=2; i<=n; s[i++]=gc()-48);
}

int main()
{
//	freopen("hunt.in","r",stdin);
//	freopen("hunt.out","w",stdout);

	int n=read(),m=read(),Q=read();
	pw[1]=1;
	for(int i=2; i<=n+1; ++i) pw[i]=pw[i-1]<<1, Mod(pw[i]);
	int *rk=::rk,*tmp=::tmp;
	for(int i=1; i<=m; ++i) rk[i]=i;
	for(int i=1,tm[2]; i<=n; ++i)
	{
		tm[0]=0, tm[1]=m, Read(m);
		for(int j=1; j<=m; ++j) s[j]?Add(x[j],pw[i]):++tm[0];
		for(int j=m; j; --j) tmp[tm[s[rk[j]]]--]=rk[j];
		std::swap(rk,tmp);
	}
	for(int i=1; i<=m; ++i) X[i]=x[rk[i]];//rk[i]=j 排第i名的是j（SA里的sa...）
	X[m+1]=pw[n+1];
	while(Q--)
	{
		Read(m); int L=0,R=m+1;//Init: L=0, R=2^n(n位二进制数)
		for(int i=1; i<=m; ++i) if(s[rk[i]]) {R=i; break;}
		for(int i=m; i; --i) if(!s[rk[i]]) {L=i; break;}
		printf("%d\n",R<L?0:(X[R]-X[L]+mod)%mod);
	}

	return 0;
}
