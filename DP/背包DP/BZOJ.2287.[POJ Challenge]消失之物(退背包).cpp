/*
1136kb	56ms
退背包。和原DP的递推一样，再减去一次递推就行了。
f[i][j]=f[i-1][j-w[i]]+f[i-1][j]
f[i-1][j]=f[i][j]-f[i-1][j-w[i]]
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#define gc() getchar()
const int N=2005;

int w[N],f[N],g[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read(),m=read();
	for(int i=1; i<=n; ++i) w[i]=read();
	f[0]=1;
	for(int i=1; i<=n; ++i)
		for(int j=m,wi=w[i]; j>=wi; --j) (f[j]+=f[j-wi])%=10;
	for(int i=1; i<=n; ++i)
	{
		memcpy(g,f,sizeof g);
		for(int wi=w[i],j=wi; j<=m; ++j) (g[j]+=10-g[j-wi])%=10;//g[j]-=g[j-wi]
		for(int j=1; j<=m; ++j) putchar(g[j]+'0');
		putchar('\n');
	}

	return 0;
}
