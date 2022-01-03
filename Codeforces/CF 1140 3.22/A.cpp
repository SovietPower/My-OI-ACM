#include <map>
#include <set>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

int A[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	int ans=0;
	for(int i=1; i<=n; ++i)
	{
		int j=i,mx=A[i];
		while(j<n && j!=mx) ++j, mx=std::max(mx,A[j]);
		i=j, ++ans;
	}
	printf("%d\n",ans);

	return 0;
}
