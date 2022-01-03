/*
$Description$
给定两个数$n,m$，每次可以使n减一或使n乘2。求最少需要多少次可以使n等于m。
$Solution$
暴力连边BFS或者DP都行，都是O(n)的。有更优的做法。
过程是可逆的，我们考虑m变成n，有两种操作：1是m+=1；2是当m为偶数时，m/=2。
要用最少的次数使得m<=n。
因为m加两次再除以二和先除以二再加一次得到的结果是一样的，即能除就不加。这样就O(logn)解决了。
正推n到m好像推不出性质啊。。正推不行就试试倒推吧。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read(),m=read(),ans=0;
	for(; m>n; m>>=1, ++ans)
		if(m&1) ++m, ++ans;
	printf("%d\n",ans+n-m);

	return 0;
}
