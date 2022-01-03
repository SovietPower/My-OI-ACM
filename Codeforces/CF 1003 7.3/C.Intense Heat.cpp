#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define eps (1e-8)
const int N=5007;

int n,K,A[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	n=read(),K=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	double ans=0;
	for(int i=1; i<=n; ++i)
	{
		int sum=0;
		for(int j=i; j<=n; ++j)
		{
			sum+=A[j];
			if(j-i+1>=K) ans=std::max(ans,1.0*sum/(j-i+1));
		}
	}
	printf("%.10lf",ans);

	return 0;
}
