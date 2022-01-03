#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e3+5;

int n,m,cost[N],A[N];

inline int read()
{
	register int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(), m=read();
	for(int i=1; i<=n; ++i) cost[i]=read();
	for(int i=1; i<=m; ++i) A[i]=read();
	int now=1,ans=0;
	for(int i=1; i<=n && now<=m; ++i)
		if(cost[i]<=A[now]) ++ans, ++now;
	printf("%d\n",ans);

	return 0;
}
