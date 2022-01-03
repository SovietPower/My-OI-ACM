/*
0ms	0MB
$Description$
给定长为n的序列A。求有多少S，满足0<=S<2^{60}，且对于所有i∈[1,n-1]，a[i]^S<=a[i+1]^S。
n<=20。
$Solution$
考虑对于a,b，有哪些S满足a^S<=b^S。
找出a^b的最高位1（也就是a,b不同的最高位），如果这一位a是0，b是1，那么S这一位必须是0；否则S这一位必须是1。
所以每个a[i]^S<=a[i+1]^S实际上是限制了S的某一位。把所有限制算出来就行了。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define BIT 59
typedef long long LL;
const int N=66;

int ban[N];

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	memset(ban,0xff,sizeof ban);
	int n=read(); LL las=read();
	for(int i=2; i<=n; ++i)
	{
		LL now=read(),s=now^las;
		for(int j=BIT; ~j; --j)
		{
			if(!(s>>j&1)) continue;
			if(las>>j&1)
				if(!ban[j]) return puts("0"),0;
				else ban[j]=1;
			else
				if(ban[j]==1) return puts("0"),0;
				else ban[j]=0;
			break;
		}
		las=now;
	}
	LL ans=1;
	for(int i=BIT; ~i; --i) if(ban[i]==-1) ans<<=1ll;
	printf("%lld\n",ans);

	return 0;
}
