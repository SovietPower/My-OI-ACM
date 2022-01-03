#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1005;

int A[N],tm[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) ++tm[A[i]=read()];
	int cnt[5]={0,0,0,0,0};
	for(int i=1; i<=100; ++i) if(tm[A[i]]<3) ++cnt[tm[A[i]]]; else ++cnt[3];
	if(cnt[1]&1 && cnt[3]==0) return puts("NO"),0;
	puts("YES");
	int mid=cnt[1]>>1;
	if(cnt[1]&1)
	{
		int p=0;
		for(int i=1; i<=n; ++i) if(tm[A[i]]>2) {p=i; break;}
		for(int i=1; i<=n; ++i)
			if(tm[A[i]]==1)
			{
				if(mid) putchar('A'), --mid;
				else putchar('B');
			}
			else if(i!=p) putchar('B');
			else putchar('A');
	}
	else
	{
		for(int i=1; i<=n; ++i)
			if(tm[A[i]]==1)
			{
				if(mid) putchar('A'), --mid;
				else putchar('B');
			}
			else putchar('B');
	}

	return 0;
}
