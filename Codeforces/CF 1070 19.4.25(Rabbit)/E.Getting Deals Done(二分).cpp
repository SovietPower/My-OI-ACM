/*
46ms	2200KB(离散化的版本，那个写的太丑了留这个代码叭)
显然答案是可以三分的。但是答案是整数三分有点麻烦。
考虑能不能二分一个答案$mid$是否可行。如果至少选$mid$个，那么要选的肯定是最便宜的$mid$个物品。那么模拟一下就行了。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=2e5+5;

int A[N],ref[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline LL readll()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
bool Check(int x,int n,int m,LL T)
{
	LL sum=0;//longlongaaaTAT
	for(int res=0,now=0,i=1,val=ref[x]; i<=n; ++i)
		if(A[i]<=val)
		{
			if((T-=A[i])<0) return 0;
			if(++res>=x) return 1;
			sum+=A[i];
			if(++now==m) now=0, T-=sum, sum=0;
		}
	return 0;
}

int main()
{
	ref[0]=1;
	for(int Ts=read(); Ts--; )
	{
		const int n=read(),m=read(); const LL t=readll();
		for(int i=1; i<=n; ++i) ref[i]=A[i]=read();
		std::sort(ref+1,ref+1+n);
		int l=1,r=n,mid,ans=0;
		while(l<=r)
			if(Check(mid=l+r>>1,n,m,t)) ans=mid, l=mid+1;
			else r=mid-1;
		printf("%d %d\n",ans,ref[ans]);
	}

	return 0;
}
