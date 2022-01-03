/*
46ms	6100KB
记四种人分别是$1,2,3,4$。显然$2,3$可以同时选，然后选一个$4$可以多选一个$1/2+3$。排序从大到小选就行了。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <functional>
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=4e5+5;

int val[4][N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline int read01()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*2+c-48,c=gc());
	return now;
}

int main()
{
	const int n=read();
	int cnt[4]={0};
	for(int i=1,type; i<=n; ++i) type=read01(), val[type][++cnt[type]]=read();
	if(!cnt[3]&&(!cnt[1]||!cnt[2])) return puts("0"),0;
	for(int i=0; i<4; ++i) std::sort(val[i]+1,val[i]+cnt[i]+1,std::greater<int>());
	int p0=1,p1=1,p2=1,p3=1,ans=0;
	for(; p1<=cnt[1]&&p2<=cnt[2]; ans+=val[1][p1++]+val[2][p2++]);
	for(int i=1; i<=cnt[3]; ++i)
	{
		if(val[1][p1]+val[2][p2]>val[0][p0]) ans+=val[1][p1++]+val[2][p2++];
		else ans+=val[0][p0++];
		ans+=val[3][i];
	}
	printf("%d\n",ans);

	return 0;
}
