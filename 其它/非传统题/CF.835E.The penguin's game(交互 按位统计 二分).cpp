/*
$Description$
有一个长为$n$的序列，其中有两个元素为$y$，其余全为$x$。你可以进行$19$次询问，每次询问你给出一个下标集合，交互库会返回这些元素的异或和。给定$n,x,y$，你需要求出两个$y$的下标。
$n\leq 1000,1\leq x,y\leq 10^9$。
$Solution$
对连续区间询问得到的结果只有那么几种，可以直接判断$y$的个数的奇偶性。但是区分不出来该区间有0个还是2个$y$。
两个$y$的下标不同。我们可以借此对下标某一位是$0/1$计算其异或和，若不同，则两个$y$的下标在这一位上不同。最后我们能得到两个$y$下标的异或和。
找一个$y$在某位不同且元素个数最少的位置，在较小的集合内（大小$\leq\frac{n}{2}$）二分，这里面只有一个$y$，就可以得到它的位置，异或之前的和就得到另一个。次数正好$19$。
当然也可以不二分。任找该位不同的一位$p$，然后枚举不等于$p$的每位，我们要判断是否有一个$y$（另一个可以直接通过之前在该位的询问得到）在该位上是$1$。只枚举$p,i$位为1的下标，可以保证只有一个$y$并判断出这个$y$是否在这位上是$1$，因为询问可以确定其中是否有$y$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1005;

int n,x,y;
bool vis[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline bool Query()
{
	int t=0, res;
	for(int i=1; i<=n; ++i) if(vis[i]) ++t;
	if(!t) return 0;
	printf("? %d",t);
	for(int i=1; i<=n; ++i) if(vis[i]) printf(" %d",i);
	putchar('\n'); fflush(stdout);
	return res=read(),(t&1&&!(res^y))||(!(t&1)&&res^y==x);//想错好多次。。
}

int main()
{
	n=read(), x=read(), y=read();
	int sum=0, p=0;
	for(int i=0; 1<<i<=n; ++i)
	{
		for(int j=1; j<=n; ++j) if(j>>i&1) vis[j]=1;
		if(Query()) sum|=1<<i, p=i;
		for(int j=1; j<=n; ++j) vis[j]=0;
	}
	int p1=0, p2=1<<p;
	for(int i=0; 1<<i<=n; ++i)
		if(i!=p)
		{
			for(int j=1; j<=n; ++j) if(j>>i&1 && j>>p&1) vis[j]=1;
			p2|=Query()<<i;
			for(int j=1; j<=n; ++j) vis[j]=0;
		}
	if((p1=p2^sum)>p2) std::swap(p1,p2);
	printf("! %d %d\n",p1,p2); fflush(stdout);

	return 0;
}
