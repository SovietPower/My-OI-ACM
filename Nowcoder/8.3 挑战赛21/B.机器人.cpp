#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=55;

int n,m;
char s[N][N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	for(int Case=read(); Case--; )
	{
		n=read(),m=read();
		int x=0,y;
		for(int i=1; i<=n; ++i)
		{
			scanf("%s",s[i]+1);
			if(x) continue;
			for(int j=1; j<=m; ++j)
				if(s[i][j]=='S') x=i, y=j;
		}
		bool f=0;
		for(int i=x-1; i; --i) if(s[i][y]=='#') {f=1; break;}
		if(!f) for(int i=x+1; i<=n; ++i) if(s[i][y]=='#') {f=1; break;}
		if(!f) for(int i=y-1; i; --i) if(s[x][i]=='#') {f=1; break;}
		if(!f) for(int i=y+1; i<=m; ++i) if(s[x][i]=='#') {f=1; break;}
		if(f) puts("-1");
		else printf("%d\n",n-1+m-1);
	}
	return 0;
}
