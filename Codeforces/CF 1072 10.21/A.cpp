#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
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
	int n=read(),m=read(),k=read();
	int xu=1,xd=n,yu=1,yd=m,ans=0;
	while(k--)
	{
		if(xu>xd||yu>yd) break;
		ans+=2*(xd-xu+1)+2*(yd-yu+1)-4;
		xd-=2, xu+=2, yd-=2, yu+=2;
	}
	printf("%d\n",ans);

	return 0;
}
