//ÍüÈ¡max mmp
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=105;

int n,m,A[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(),m=read(); int s=0;
	for(int i=1; i<=n; ++i) s+=(A[i]=read());
	int mx=A[1];
	for(int i=2; i<=n; ++i) mx=std::max(mx,A[i]);
	printf("%d %d\n",std::max(mx,(s+m+n-1)/n),mx+m);

	return 0;
}
