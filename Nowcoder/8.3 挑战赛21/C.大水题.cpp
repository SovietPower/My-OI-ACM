#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=3e5+5;

int n,A[N],ref[N],las[N];
LL sum[N],f[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline LL readll()
{
	LL now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline int Find(int x,int r)
{
	int l=1,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}
inline void Discrete()
{
	std::sort(ref+1,ref+1+n); int cnt=1;
	for(int i=2; i<=n; ++i) if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	for(int i=1; i<=n; ++i) A[i]=Find(A[i],cnt);
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) ref[i]=A[i]=read();
	Discrete();
	for(int i=1; i<=n; ++i) sum[i]=sum[i-1]+readll();
	for(int i=1,L; i<=n; ++i)
	{
		f[i]=f[i-1];
		if(L=las[A[i]]) f[i]=std::max(f[i],std::max(f[L-1]+sum[i]-sum[L-1],f[L]+sum[i]-sum[L]));
		las[A[i]]=i;
	}
	printf("%lld\n",f[n]);

	return 0;
}
