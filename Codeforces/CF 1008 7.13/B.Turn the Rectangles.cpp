#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define Failed return puts("NO"),0
const int N=1e5+5;

int n,A[N],B[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read();
	for(int i=1,a,b; i<=n; ++i) A[i]=read(),B[i]=read();
	for(int now=std::max(A[1],B[1]),i=2; i<=n; ++i)
	{
		if(now>=std::max(A[i],B[i])) now=std::max(A[i],B[i]);
		else if(now>=std::min(A[i],B[i])) now=std::min(A[i],B[i]);
		else Failed;
	}
	puts("YES");

	return 0;
}
