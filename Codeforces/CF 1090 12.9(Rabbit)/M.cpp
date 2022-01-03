#include <set>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

int A[N],vis[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	int n=read(),K=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	int ans=0; A[n+1]=A[n];
	for(int l=1,r=1; r<=n; )
	{
		while(r<=n && A[r]!=A[r+1]) ++r;
		ans=std::max(ans,r-l+1);
		l=++r;
	}
	printf("%d\n",ans);

	return 0;
}
