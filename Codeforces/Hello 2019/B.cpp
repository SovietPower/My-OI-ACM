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
const int N=20;

int A[N];

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
	for(int i=0; i<n; ++i) A[i]=read();
	for(int s=0; s<1<<n; ++s)
	{
		int x=0;
		for(int j=0; j<n; ++j)
			s>>j&1 ? x+=A[j] : x-=A[j];
		if(!((x%360+360)%360)) return puts("YES"),0;
	}
	puts("NO");

	return 0;
}
