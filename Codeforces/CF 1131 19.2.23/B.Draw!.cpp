//有点不知道说什么...看代码吧...
#include <set>
#include <map>
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

int A[N],B[N];

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
	for(int i=1; i<=n; ++i) A[i]=read(),B[i]=read();
	LL ans=0;
	for(int i=1,las=0; i<=n; ++i)
	{
		int x=std::max(A[i-1],B[i-1]),y=std::min(A[i],B[i]);
		x=std::max(x,las), las=y+1;
		ans+=std::max(y-x+1,0);
	}
	printf("%I64d\n",ans);

	return 0;
}
