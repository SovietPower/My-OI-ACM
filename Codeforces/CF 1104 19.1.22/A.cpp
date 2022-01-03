#include <set>
#include <map>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define pc putchar
typedef long long LL;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	static int A[100];
	int n=read(),ans=1000,t;
	printf("%d\n",n);
	while(n--) printf("%d ",1);
//	for(int s=0,l=1<<10; s<l; ++s)
//	{
//		int x=n,cnt=0;
//		for(int i=1; i<10; ++i) if(s>>i&1) cnt+=x/i, x-=x/i*i;
//		if(!x && cnt<ans)
//		{
//			ans=cnt, t=0;
//			for(int i=1; i<10; ++i) if(s>>i&1) A[++t]=i;
//		}
//	}
//	printf("%d\n",ans);
//	int x=n;
//	for(int i=1; i<=t; ++i)
//		while(x>=A[i]) printf("%d ",A[i]), x-=A[i];

	return 0;
}
