#include <set>
#include <map>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define pc putchar
#define gc() getchar()
typedef long long LL;


inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	int x=read(),y=read(),z=read(),a=read(),b=read(),c=read();
	if(a<x) return puts("NO"),0;
	a-=x;
	if(a+b<y) return puts("NO"),0;
	int tot=a+b+c-y-z;
	if(tot<0) return puts("NO"),0;
	return puts("YES"),0;

	return 0;
}
