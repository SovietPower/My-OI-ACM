/*
530MS 1544K
$Description$
给定一个集合S，每次只能拿S中某个元素个数的石子。每组数据有多组询问，询问给出m堆石子个数，问先手是否必胜。有多组数据。
$Solution$
首先对操作数组排个序，再预处理求sg就好了。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=10002;

int n,A[N],sg[N+3];
bool vis[N+3];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Init_SG()
{
	for(int i=1; i<N; ++i)
	{
		memset(vis,0,sizeof vis);
		for(int j=1; j<=n&&A[j]<=i; ++j)
			vis[sg[i-A[j]]]=1;
		for(int j=0; ; ++j)
			if(!vis[j]) {sg[i]=j; break;}
	}
}

int main()
{
	while(n=read(),n)
	{
		for(int i=1; i<=n; ++i) A[i]=read();
		std::sort(A+1,A+1+n);
		Init_SG();
		int m=read();
		while(m--)
		{
			int mx=read(),res=0;
			for(int i=1; i<=mx; ++i) res^=sg[read()];
			putchar(res?'W':'L');
		}
		putchar('\n');
	}
	return 0;
}
