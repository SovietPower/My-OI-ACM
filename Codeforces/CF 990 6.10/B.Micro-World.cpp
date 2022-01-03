//31ms	1376KB
//注意重复就好了 
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=2e5+5;

int n,K,A[N],val[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(), K=read();
	int res=n;
	for(int i=1; i<=n; ++i) A[i]=read();//,++val[A[i]];
	std::sort(A+1,A+1+n);
	int cnt=1; val[1]=1;
	for(int i=2; i<=n; ++i)
		if(A[i]!=A[i-1]) A[++cnt]=A[i], val[cnt]=1;
		else ++val[cnt];
	for(int i=2; i<=cnt; ++i)
		if(A[i]<=A[i-1]+K) res-=val[i-1];
	printf("%d",res);

	return 0;
}
