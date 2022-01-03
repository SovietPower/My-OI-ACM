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
const int N=104;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	int n=read(),A=read(),B=read(),c1=0,c2=0,c3=0;
	for(int i=1; i<=n; ++i)
	{
		int a=read();
		if(a<=A) ++c1;
		else if(a<=B) ++c2;
		else ++c3;
	}
	printf("%d\n",std::min(c1,std::min(c2,c3)));

	return 0;
}
