#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define eps 1e-8
typedef long long LL;
const int N=1e5+7;

inline int read()
{
	register int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	int n=read(), m=read();
	LL sum=0, sumX=0, C1, C2=1ll*n*(n-1)>>1;
	if(n&1) C1=1ll*(n>>1)*((n>>1)+1);
	else C1=1ll*(n>>1)*((n>>1)+1)-1ll*(n>>1);
	LL x,d;
	for(int i=1; i<=m; ++i)
	{
		x=read(), d=read(), sumX+=x;
		if(d>0) sum+=C2*d;
		else if(d<0) sum+=C1*d;
	}
	printf("%.8lf",1.0*(sum+1ll*n*sumX)/n);

	return 0;
}
