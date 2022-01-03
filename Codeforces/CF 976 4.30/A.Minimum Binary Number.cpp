#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=105;

int n;
char s[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	scanf("%d%s",&n,s+1);
	int cnt=0;
	for(int i=1; i<=n; ++i)
		if(s[i]=='0') ++cnt;
	if(cnt==n) {puts("0"); return 0;}
	putchar('1');
	for(int i=1; i<=cnt; ++i) putchar('0');

	return 0;
}
