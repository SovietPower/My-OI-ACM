#include <set>
#include <map>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=1005;


inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	static char s[N];
	scanf("%s",s+1); int n=strlen(s+1);
	int t0=0,t1=0;//0:竖着的 1：横着的 
	for(int i=1; i<=n; ++i)
		if(s[i]=='0')
			printf("%d %d\n",4,2*(t0%2)+1), ++t0;
		else
			printf("%d %d\n",1,t1%4+1), ++t1;

	return 0;
}
