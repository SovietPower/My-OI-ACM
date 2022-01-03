#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=2e5+5;

int n,s,A[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(),s=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	std::sort(A+1,A+1+n);
	int p=(n+1)/2; long long ans=0;
	if(A[p]>s)
	{
		int p2=p;
		for(int i=1; i<p; ++i) if(A[i]>s) {p2=i; break;}
		for(int i=p2; i<=p; ++i) ans+=A[i]-s;
	}
	else if(A[p]<s)
	{
		int p2=p;
		for(int i=n; i>p; --i) if(A[i]<s) {p2=i; break;}
		for(int i=p; i<=p2; ++i) ans+=s-A[i];
	}
	printf("%I64d\n",ans);

	return 0;
}
