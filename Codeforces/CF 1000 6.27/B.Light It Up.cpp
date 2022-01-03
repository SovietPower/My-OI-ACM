#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+7;

LL n,m,A[N],sum[N],suf[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(),m=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<=n; i+=2) sum[i+1]=sum[i]=sum[i-1]+A[i]-A[i-1];
	if(n&1){
		for(int i=n-1; i>0; i-=2) suf[i-1]=suf[i]=suf[i+1]+A[i+1]-A[i];
	}
	else{
		A[n+1]=m;
		for(int i=n; i>0; i-=2) suf[i-1]=suf[i]=suf[i+1]+A[i+1]-A[i];
	}
//	for(int i=1; i<=n; ++i) printf("%d:pre:%I64d suf:%I64d\n",i,sum[i],suf[i]);
	LL ans=sum[n];
	if(!(n&1)) ans+=m-A[n];
	if(n&1) A[++n]=m;
	for(LL i=1; i<=n; ++i)
		if(A[i]-A[i-1]>1){
			if(i&1) ans=std::max(ans,sum[i-1]+A[i]-A[i-1]-1+m-A[i]-suf[i]);
			else ans=std::max(ans,sum[i-1]+A[i]-A[i-1]-1+m-A[i]-suf[i]);
		}
	printf("%I64d",ans);

	return 0;
}