#include <set>
#include <map>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define pc putchar
#define gc() getchar()

inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	for(; !isdigit(ch); ch=getchar())if(ch=='-')f=-1;
	for(; isdigit(ch); ch=getchar())x=x*10+ch-'0';
	return x*f;
}

char s[10000];

int main ()
{
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	int x = 0, h = 0;
	for (int i = 1; i <= n; ++i)
	{
		if (s[i] == '1')
		{
			if (h == 0) puts("1 1");
			else puts("1 3");
			h ++;
			h %= 2;
		}
		if (s[i] == '0')
		{
			if (x == 0) puts("3 1");
			else if (x == 1) puts("3 2");
			else if (x == 2) puts("3 3");
			else puts("3 4");
			x ++;
			x %= 4;
		}
	}
	return 0;
}
