#include <set>
#include <map>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define mod 1000000007//998244353
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=3e5+5;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	static int A[N];
	int n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	std::sort(A+1,A+1+n);
	LL ans=0;
	for(int i=1; i+i<=n; ++i) ans+=(A[i]+A[n-i+1])*(A[i]+A[n-i+1]);
	printf("%I64d\n",ans);

	return 0;
}
