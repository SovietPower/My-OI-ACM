#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1000;

char s[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	int T=read();
	while(T--)
	{
		scanf("%s",s+1); int n=strlen(s+1);
		int f1=0,f2=0,f3=0;//1 a A
		for(int i=1; i<=n; ++i)
			if(isdigit(s[i])) ++f1;
			else if(s[i]>='a'&&s[i]<='z') ++f2;
			else ++f3;
		s[n+1]='\0';
		if(f1&&f2&&f3) ;
		else if(f1&&f2)
		{
			if(f1>1) for(int i=1; i<=n; ++i) if(isdigit(s[i])) {s[i]='A'; break;} else ;
			else for(int i=1; i<=n; ++i) if(s[i]>='a'&&s[i]<='z') {s[i]='A'; break;}
		}
		else if(f2&&f3)
		{
			if(f3>1) for(int i=1; i<=n; ++i) if(!isdigit(s[i])&&!(s[i]>='a'&&s[i]<='z')) {s[i]='1'; break;} else ;
			else for(int i=1; i<=n; ++i) if(s[i]>='a'&&s[i]<='z') {s[i]='1'; break;} else ;
		}
		else if(f1&&f3)
		{
			if(f1>1) for(int i=1; i<=n; ++i) if(isdigit(s[i])) {s[i]='a'; break;} else ;
			else for(int i=1; i<=n; ++i) if(!isdigit(s[i])&&!(s[i]>='a'&&s[i]<='z')) {s[i]='a'; break;} else ;
		}
		else if(f1) s[1]='a', s[2]='A';
		else if(f2) s[1]='0', s[2]='A';
		else if(f3) s[1]='a', s[2]='0';
		puts(s+1);
	}
	return 0;
}
