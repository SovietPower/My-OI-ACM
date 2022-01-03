#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define Fail return puts("NO"),0
const char OK[7]={'a','e','i','o','u','n'};
const int N=105;

int n;
char s[N];

bool Check(int p)
{
	for(int i=0; i<=5; ++i) if(s[p]==OK[i]) return 1;
	return 0;
}
bool Check2(int p)
{
	for(int i=0; i<5; ++i) if(s[p]==OK[i]) return 1;
	return 0;
}

int main()
{
	scanf("%s",s+1), n=strlen(s+1);
	for(int i=1; i<n; ++i)
		if(!Check(i)&&!Check2(i+1)) Fail;
	if(!Check(n)) Fail;
	puts("YES");

	return 0;
}
