#include <set>
#include <map>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define pc putchar
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
typedef long long LL;


inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	int n=read(),H=read(),W=read();
	printf("%d\n",(n-H+1)*(n-W+1));

	return 0;
}
