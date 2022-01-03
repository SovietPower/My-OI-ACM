#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=500;

int n,A[N],tm[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) ++tm[read()];
	int res=0;
	for(int i=1; i<=100; ++i) res=std::max(res,tm[i]);
	printf("%d",res);

	return 0;
}
