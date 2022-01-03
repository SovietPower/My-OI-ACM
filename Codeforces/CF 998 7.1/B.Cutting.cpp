#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1004;

int n,B,A[N],c[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(),B=read();
	int cnt=0;
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1,odd=0,even=0; i<=n; ++i)
	{
		if(A[i]&1) ++odd; else ++even;
		if(odd==even&&i!=n) c[++cnt]=std::abs(A[i+1]-A[i]);
	}
	std::sort(c+1,c+1+cnt);
	int res=0;
	for(int i=1; i<=cnt; ++i)
		if(B>=c[i]) ++res, B-=c[i];
		else break;
	printf("%d",res);

	return 0;
}
