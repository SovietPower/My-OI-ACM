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

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	char s[5],t[5];
	scanf("%s",s);
	for(int i=1; i<=5; ++i)
	{
		scanf("%s",t);
		if(t[0]==s[0]||t[0]==s[1]||t[1]==s[0]||t[1]==s[1]) return puts("YES"),0;
	}
	puts("NO");

	return 0;
}
