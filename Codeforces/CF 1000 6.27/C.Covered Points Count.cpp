#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e6+7;

int n,cnt,val[N];
LL ref[N*4],L[N],R[N],Ans[N];

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int Find(LL x)
{
	int l=1, r=cnt, mid;
	while(l<r)
		if(ref[mid=l+r>>1]>=x) r=mid;
		else l=mid+1;
	return l;
}

int main()
{
	n=read(); int tot=0;
	for(int i=1; i<=n; ++i) L[i]=ref[++tot]=read(), ref[++tot]=L[i]-1, R[i]=ref[++tot]=read(), ref[++tot]=R[i]+1;

	std::sort(ref+1,ref+1+tot), cnt=1;
	for(int i=2; i<=tot; ++i) if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];

	for(int i=1; i<=n; ++i) ++val[Find(L[i])], --val[Find(R[i]+1)];
	ref[0]=ref[1]-1;
	for(int now=0,i=1; i<=cnt; ++i)
	{
		now+=val[i];
		Ans[now]+=ref[i]-ref[i-1];
	}
	for(int i=1; i<=n; ++i) printf("%I64d ",Ans[i]);

	return 0;
}
