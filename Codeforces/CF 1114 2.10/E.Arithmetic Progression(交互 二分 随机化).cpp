/*
31ms	3700KB
首先通过操作二可以二分出最大值。
然后剩下$30$次操作一能干什么呢。。只能帮我们确定出数列中有某些数，那能做的好像就是随机确定$30$个数。
等差数列中任意两个数作差可以得到$x\cdot d$，把确定出的数两两作差然后对差求$\gcd$，是有可能得到真正的$d$的。
正确概率是多少呢，感觉挺高的。。然后有最大值有公差，就做完了。
[官方题解](https://codeforces.com/blog/entry/65136)中对正确概率有证明，大约是$1.86185\times10^{-9}$。

做差的时候先排序，只求出相邻两个数的差就够了，并不需要所有数两两之间作差。
*/
#include <ctime>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define Flush() fflush(stdout)
typedef long long LL;
const int N=1e6+5;

int id[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline int Rd()
{
	return rand()<<15|rand();
}
inline int Query1(int n)
{
	int p=Rd()%n+1;
	printf("? %d\n",id[p]), Flush();
	std::swap(id[p],id[n]);//不这么写也行 差别不大 无所谓啦 
	return read();
}
inline int Query2(int x)
{
	printf("> %d\n",x), Flush();
	return read();
}

int main()
{
	static int A[66];
	srand(time(0));
	int n=read();
	int l=0,r=1e9,mid,mx=0,rest=60;
	while(l<=r)
		if(--rest,Query2(mid=l+r>>1)) mx=l=mid+1;
		else r=mid-1;

	for(int i=1; i<=n; ++i) id[i]=i;
	int t=0; rest=std::min(rest,n);
	for(int now=n; rest; --rest) A[++t]=Query1(now--);

	std::sort(A+1,A+1+t), A[++t]=mx;
	int d=A[2]-A[1];
	for(int i=3; i<=t; ++i) if(A[i]!=A[i-1]) d=std::__gcd(d,A[i]-A[i-1]);
	printf("! %d %d\n",mx-(n-1)*d,d), Flush();

	return 0;
}
