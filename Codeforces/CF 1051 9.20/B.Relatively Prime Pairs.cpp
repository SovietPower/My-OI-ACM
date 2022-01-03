#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;

inline LL read()
{
	LL now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	LL l=read(),r=read();
	if(l==r) return puts("NO"),0;
	puts("YES");
	for(LL i=l; i<r; i+=2) printf("%I64d %I64d\n",i,i+1);

    return 0;
}
