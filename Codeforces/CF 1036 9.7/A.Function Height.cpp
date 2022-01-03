#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	LL n=read(),K=read();
	printf("%I64d\n",(K+n-1)/n);	
	return 0;
}
