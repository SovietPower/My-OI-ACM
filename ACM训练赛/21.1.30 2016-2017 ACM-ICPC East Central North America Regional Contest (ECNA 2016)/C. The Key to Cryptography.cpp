/*
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=1e6+5;

char s[N],t[N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	scanf("%s%s",s+1,t+1); int n=strlen(s+1),m=strlen(t+1);
	for(int i=m+1; i<=n; ++i) t[i]=s[i-m];
	for(int i=1; i<=n; ++i)
	{
		if(i>m) t[i]=s[i-m];
		int c=s[i]-'A'-(t[i]-'A');
		c=(c+26)%26, pc(s[i]=c+'A');
	}

	return 0;
}
