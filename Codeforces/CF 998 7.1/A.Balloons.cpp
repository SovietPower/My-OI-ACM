#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=150;

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
	n=read(); int pos=1,sum=0;
	for(int i=1; i<=n; ++i)
		sum+=(A[i]=read()), A[pos]>A[i]&&(pos=i);
	sum-=A[pos];
	if(sum<=A[pos]) puts("-1");
	else
	{
		printf("%d\n",n-1);
		for(int i=1; i<=n; ++i) if(i!=pos) printf("%d ",i);
	}

	return 0;
}
