#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <algorithm>
#define gc() getchar()
const int N=70,INF=0x7fffffff;

int n,m,opt[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline int Query(int x)
{
	printf("%d\n",x); fflush(stdout);
	int t; scanf("%d",&t); return t;
//	return read();
}

int main()
{
//	m=read(),n=read();
	scanf("%d%d",&m,&n);
	for(int i=0; i<n; ++i)
	{
		int t=Query(m);
		if(!t) exit(0);
		opt[i]=t==-1;
	}
	int l=1,r=m,mid,now=0;
	while(l<=r)
	{
		int res=Query(mid=l+r>>1);
		if(!res) exit(0);//return 0;
		if((res==1&&opt[now])||(res==-1&&!opt[now]))//mid<x
			l=mid+1;
		else r=mid-1;//mid>x
		now=(now+1)%n;
	}
	Query(l); exit(0);

	return 0;
}
