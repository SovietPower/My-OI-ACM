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

inline int read()
{
	int now=0,f=1;
	register char c=gc();
	for(; !isdigit(c); c=='-'&&(f=-1),c=gc());
	for(; isdigit(c); now=now*10+c-'0',c=gc());
	return now*f;
}
int ans;

signed main()
{
	int A = read(), B = read(), C = read();
	for(int i = 1; i <= 100; i++)
	{
		if(i <= A && (i + 1 <= B) && (i + 2 <= C)) ans = i + i + 1 + i + 2;
	}
	printf("%d\n",ans);
	return 0;
}
