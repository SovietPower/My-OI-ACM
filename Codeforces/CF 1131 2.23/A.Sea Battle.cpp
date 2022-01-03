#include <set>
#include <map>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define pc putchar
#define gc() getchar()
typedef long long LL;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
LL c(LL a,LL b)
{
	return ((a+4+b)<<1)-4;
}

int main()
{
	LL w1=read(),h1=read(),w2=read(),h2=read();
	LL ans=c(w1,h1)+c(w2,h2)-((std::min(w1,w2)+2)<<1);
	printf("%d\n",ans);

	return 0;
}
