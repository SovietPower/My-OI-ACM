#include <set>
#include <map>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
typedef long long LL;
const int N=1005;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}/*
5
1 1 1 100 100
*/

int main()
{
	static int A[N];
	int n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	int ans=1e9,anst=1;
	for(int t=1; t<=100; ++t)
	{
		int res=0;
		for(int i=1; i<=n; ++i)
		{
			if(A[i]<t) res+=std::max(t-1-A[i],0);
			else if(A[i]>t) res+=std::max(A[i]-t-1,0);
		}
		if(ans>res) ans=res, anst=t;
	}
	printf("%d %d\n",anst,ans);

	return 0;
}
