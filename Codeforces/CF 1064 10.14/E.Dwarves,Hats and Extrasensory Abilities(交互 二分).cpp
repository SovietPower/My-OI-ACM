/*
容易想到根据点的颜色，不断二分调整询问位置。
但是$2^{30}>10^9$，$30$次二分要出事。。
我们可以先询问一次端点（$0$或$10^9$），后面的二分再根据这个判断位置，就是29次二分啦。
pretest直接$30$次二分都可以过的吗。。明明大于1e9我怎么当时就觉得可以了呢。。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=2e6+5;

inline char Get(int p)
{
	static char s[233];
	printf("10 %d\n",p), fflush(stdout);
	scanf("%s",s); return s[0];
}

int main()
{
	int n; scanf("%d",&n);
	int s=Get(0),l=0,r=1e9,mid;
	for(int i=1; i<n; ++i)
	{
		mid=l+r>>1;
		if(Get(mid)==s) l=mid;
		else r=mid;
	}
	printf("9 %d 11 %d\n",l,l+1), fflush(stdout);

	return 0;
}
