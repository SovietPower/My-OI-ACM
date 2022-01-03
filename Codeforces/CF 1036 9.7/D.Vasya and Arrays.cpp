#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=3e5+5;

int n,m,A[N],B[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(); LL sa=0,sb=0;
	for(int i=1; i<=n; ++i) sa+=(A[i]=read());
	m=read();
	for(int i=1; i<=m; ++i) sb+=(B[i]=read());
	if(sa!=sb) return puts("-1"),0;
	int la=n,lb=m,nowa=1,nowb=1,lim=std::min(n,m);
	sa=A[1],sb=B[1];
	while(nowa<n && nowb<m)
	{
		if(sa==sb) sa=A[++nowa], sb=B[++nowb];
		else if(sa>sb) sb+=B[++nowb], --lb;
		else sa+=A[++nowa], --la;
	}
	while(nowa<n) sa+=A[++nowa], --la;
	while(nowb<m) sb+=B[++nowb], --lb;
	if(la==lb&&sa==sb) printf("%d\n",la);
	else puts("-1");

	return 0;
}
