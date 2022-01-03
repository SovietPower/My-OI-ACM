#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e4+5;


inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read(),even=0,f=0;
	if(n==1)
	{
		int a=read();
		if(a==1||!(a&1)) puts("Bob");
		else puts("Alice");
		return 0;
	}
	for(int i=1,a; i<=n; ++i)
	{
		a=read();
		if(a&1 && a>1) f=1;
		else if(!(a&1)) ++even;
	}
	puts((even&&!(even&1)||(!even&&f))?"Alice":"Bob");

	return 0;
}
