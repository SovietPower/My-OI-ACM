#include <set>
#include <map>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
typedef long long LL;
typedef unsigned long long ull;
const int N=1005;

int X[N],Y[N],A[N],B[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) X[i]=read(), Y[i]=read();
	for(int i=1; i<=n; ++i) A[i]=read(), B[i]=read();
	for(int i=1; i<=n; ++i)
	{
		bool f=1;
		int ansx=X[1]+A[i],ansy=Y[1]+B[i];
		std::map<int,int> vx,vy;
		for(int j=2; j<=n; ++j)
			++vx[X[j]], ++vy[Y[j]];
		for(int j=1; j<=n; ++j)
		{
			if(i==j) continue;
			if(!vx[ansx-A[j]]||!vy[ansy-B[j]]) {f=0; break;}
			--vx[ansx-A[j]], --vy[ansy-B[j]];
		}
		if(f) return printf("%d %d\n",ansx,ansy),0;
	}
	return 0;
}
