#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
typedef long long LL;
const int N=1e6+5;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int A,B,n,m,ans1[N],ans2[N];

bool Check(int x)
{
	int a=A,b=B;
	while(x)
	{
		if(a<b) std::swap(a,b);
		if(a<x) return 0;
		a-=x, --x;
	}
	return 1;
}

int main()
{
	A=read(),B=read(),n=0,m=0;
	int l=0,r=1e6,mid,ans=0;
	while(l<=r)
	{
		if(Check(mid=l+r>>1)) l=mid+1,ans=mid;
		else r=mid-1;
	}
	int a=A,b=B;
	for(int i=ans; i; --i)
		if(a<b) b-=i, ans2[++m]=i;
		else a-=i, ans1[++n]=i;
	printf("%d\n",n);
	for(int i=n; i; --i) printf("%d ",ans1[i]); putchar('\n');
	printf("%d\n",m);
	for(int i=m; i; --i) printf("%d ",ans2[i]); putchar('\n');

	return 0;
}
