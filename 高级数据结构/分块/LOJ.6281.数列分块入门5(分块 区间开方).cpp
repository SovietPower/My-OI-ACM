#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=5e4+5;

int n,size,bel[N],A[N];
LL sum[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
LL Query_Sum(int l,int r)
{
	LL res=0ll; int t=std::min(bel[l]*size,r);
	for(int i=l; i<=t; ++i) res+=A[i];
	if(bel[l]!=bel[r])
		for(int i=(bel[r]-1)*size+1; i<=r; ++i)
			res+=A[i];
	for(int i=bel[l]+1; i<bel[r]; ++i) res+=sum[i];
	return res;
}
inline void Sqrt(int p)
{
	sum[bel[p]]-=A[p], A[p]=sqrt(A[p]), sum[bel[p]]+=A[p];
}
void Modify(int l,int r)
{
	int t=std::min(bel[l]*size,r);
	for(int i=l; i<=t; ++i)
		if(A[i]!=1) Sqrt(i);
	if(bel[l]!=bel[r])
		for(int i=(bel[r]-1)*size+1; i<=r; ++i)
			if(A[i]!=1) Sqrt(i);
	for(int i=bel[l]+1; i<bel[r]; ++i)
		if(sum[i]!=size)
			for(int j=(i-1)*size+1; j<=i*size; ++j)
				if(A[j]!=1) Sqrt(j);
}

int main()
{
	n=read(), size=sqrt(n);
	for(int i=1; i<=n; ++i) bel[i]=(i-1)/size+1;
	for(int i=1; i<=n; ++i) A[i]=read(),sum[bel[i]]+=A[i];
	for(int opt,l,r,c,i=1; i<=n; ++i)
	{
		opt=read(),l=read(),r=read(),c=read();
		if(opt) printf("%lld\n",Query_Sum(l,r));
		else Modify(l,r);
	}
	return 0;
}
