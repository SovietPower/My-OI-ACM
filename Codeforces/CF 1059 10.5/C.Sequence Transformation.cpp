#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()

int Ans[1000005];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	int n=read();
	if(n==1) printf("1\n");
	if(n==2) printf("1 2\n");
	if(n==3) printf("1 1 3\n");
	if(n<=3) return 0;

	int d=1, p1=2, p2=3, cnt=0;

	while(d!=n)
	{
		int tot=n/d;
		if(tot-n/p1 < tot-n/p2)
		{
			for(int i=d; i<=n; i+=d)
				if(i%p1) Ans[++cnt]=d;
			d=p1;
		}
		else
		{
			for(int i=d; i<=n; i+=d)
				if(i%p2) Ans[++cnt]=d;
			d=p2;
		}
		p1=d<<1;
		p2=3*d;
		if(d==n) Ans[++cnt]=d;
		if(cnt==n) break;
	}
	for(int i=1; i<=n; ++i) printf("%d ", Ans[i]);

	return 0;
}
