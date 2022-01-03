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
LL Gcd(LL x,LL y)
{
	return y?Gcd(y,x%y):x;
}

int main()
{
	LL a=read(),b=read(),x=read(),y=read(),g=Gcd(x,y);
	x/=g,y/=g;
	printf("%I64d\n",std::min(a/x,b/y));

	return 0;
}
