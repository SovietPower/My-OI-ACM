#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read(),x=0;
	for(; n; n>>=1,++x);
	printf("%d\n",x);

	return 0;
}
