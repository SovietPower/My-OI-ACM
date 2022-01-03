#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=107;

int n,m,tm[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(), m=read();
	for(int i=1; i<=m; ++i) ++tm[read()];
	int res=0;
	for(int x=100; x; --x)
	{
		int num=0;
		for(int i=1; i<=100; ++i) num+=tm[i]/x;
		if(num>=n) {res=x; break;}
	}
	printf("%d\n",res);

	return 0;
}
