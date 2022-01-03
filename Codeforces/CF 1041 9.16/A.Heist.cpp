//直接A[n]-A[1]-n+1就行了。。
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e3+5;

int n,A[N];

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
	for(int i=1; i<=n; ++i) A[i]=read();
	std::sort(A+1,A+1+n);
	long long ans=0;
	for(int i=2; i<=n; ++i) ans+=A[i]-A[i-1]-1;
	printf("%I64d\n",ans);//A[n]-A[1]-n+1

	return 0;
}
