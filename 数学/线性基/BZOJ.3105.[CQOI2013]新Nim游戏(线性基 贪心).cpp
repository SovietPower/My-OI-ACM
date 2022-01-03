/*
820kb	0ms
如果后手想要胜利，那么在后手第一次取完石子后 可以使石子数异或和为0。那所有数异或和为0的线性基长啥样呢，不知道。。
往前想，后手可以取走某些石子使得剩下石子异或和为0，那不就是存在异或和为0的子集吗。。
so先手要使得他取完后不存在异或和为0的子集。从大到小依次尝试插入线性基即可。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define Bit 30
const int N=105;

int n,A[N],base[36];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int Insert(int v)
{
	for(int i=Bit,x=v; ~i; --i)
		if(x>>i & 1)
			if(base[i]) x^=base[i];
			else {base[i]=x; return 0;}
	return v;
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	std::sort(A+1,A+1+n);
	long long ans=0;
	for(int i=n; i; --i) ans+=Insert(A[i]);
	printf("%lld\n",ans);

	return 0;
}
