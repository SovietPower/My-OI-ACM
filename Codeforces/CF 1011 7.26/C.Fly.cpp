#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define eps 1e-8
const int N=1005;

int n;
double m,A[N],B[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
bool Check(double x)
{
	x-=(m+x)/A[1];
	for(int i=2; i<=n; ++i)
	{
		x-=(m+x)/B[i], x-=(m+x)/A[i];
		if(x<0) return 0;
	}
	x-=(m+x)/B[1];
	return x>=0;//x>=eps;
}

int main()
{
	n=read(),m=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<=n; ++i) B[i]=read();
	double l=0,r=1e9+5,mid;
	for(int t=1; t<=7000&&r-l>eps; ++t)
		if(Check(mid=(l+r)*0.5)) r=mid;
		else l=mid;
	if(l>1e9) puts("-1");
	else printf("%.8lf\n",l);

	return 0;
}
