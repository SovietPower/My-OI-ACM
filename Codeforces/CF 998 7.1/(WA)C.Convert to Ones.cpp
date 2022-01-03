//DP不行吧 有后效性？
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
using std::min;
typedef long long LL;
const int N=3e5+7;
const LL INF=1e17;

int n;
LL X,Y,f[N][2];
char s[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(), X=read(), Y=read(), scanf("%s",s+1);
	int cnt=0;
	for(int i=1; i<=n; ++i) if(s[i]=='0') ++cnt;
	if(!cnt) return putchar('0'),0;

	if(s[1]=='0') f[1][0]=0, f[1][1]=Y;
	else f[1][0]=Y, f[1][1]=0;
	for(int i=2; i<=n; ++i)
	{
		if(s[i]=='0')
			f[i][0]=min(f[i-1][1],f[i-1][0]),
			f[i][1]=min(f[i-1][1],f[i-1][0])+Y;
		else
			f[i][0]=min(f[i-1][1]+Y,f[i-1][0]+min(X,Y)),
			f[i][1]=min(f[i-1][1],f[i-1][0]+Y);
//		printf("%d:0:%I64d 1:%I64d\n",i,f[i][0],f[i][1]);
	}
	printf("%I64d",min(f[n][1],f[n][0]+Y));

	return 0;
}
