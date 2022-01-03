/*
f[i][j]表示当前处理完i个物品，重量差为j。j∈[-MAX,MAX]。
转移三种情况。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define D 10200
#define gc() getchar()
const int N=105,M=21005;

int n,m,W[N],f[N][M];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(),m=read(); int s=0;
	for(int i=1; i<=n; ++i) s+=(W[i]=read());
	memset(f,-0x3f,sizeof f);
	f[0][D]=0;//not f[0][0]
	for(int i=1; i<=n; ++i)
		for(int j=-s+D,w=W[i]; j<=s+D; ++j)
			f[i][j]=std::max(std::max(f[i-1][j-w],f[i-1][j+w])+w,f[i-1][j]);
	int ans=0;
	for(int i=-m+D; i<=m+D; ++i) ans=std::max(ans,f[n][i]);
	printf("%d\n",ans);

	return 0;
}
