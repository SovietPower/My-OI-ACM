#include <cstdio>
#include <cctype>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
#define LL long long
#define int LL
const int N=1e6+10,INF=1e9+10,mod=1e9+7;

int n,K,A[N],Max[N];

inline int read()
{
	int now=0,f=1;
	register char c=gc();
	for(; !isdigit(c); c=='-'&&(f=-1),c=gc());
	for(; isdigit(c); now=now*10+c-'0',c=gc());
	return now*f;
}
inline int cmp(int A,int B)
{
	return A>B;
}

main()
{
	n=read(), K=read();
	int mn=INF,mx=0;
	for(int i=1; i<=n; ++i) A[i]=read(),mn=std::min(A[i],mn);
	std::sort(A+1,A+n+1,cmp);
	for(int i=1; i<=n; ++i) A[i]-=mn,mx=std::max(A[i],mx);
	for(int i=1,tmp; i<=n; ++i) ++Max[A[i]];
	int tmp=0,ans=0,tot=0;
	for(int i=mx; i>=1; --i)
	{
		tot+=Max[i];
		tmp+=tot;
		if(tmp>K) ans++,tmp=tot;
	}
	printf("%d\n",ans+(tmp!=0));

	return 0;
}
