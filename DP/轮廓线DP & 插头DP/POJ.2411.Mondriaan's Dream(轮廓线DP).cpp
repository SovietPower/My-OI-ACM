/*
388K	16MS
题意：求用1*2的矩形完全覆盖n*m的棋盘的方案数。
轮廓线DP。可以DFS预处理哪些状态能转移到哪些状态，就不用每次$2^m$枚举了。反正复杂度$O(nm2^m)$。
一个代码看了半小时还是十分感觉它不对 对自己的智商表示怀疑=-=。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int N=11;

LL f[2][(1<<N)+1];

int main()
{
	int n,m;
	while(scanf("%d%d",&n,&m),n&&m)
	{
		if(n*m&1) {puts("0"); continue;}
		if(n<m) std::swap(n,m);
		int lim=(1<<m)-1,p=1;
		memset(f[p],0,sizeof f[p]);
		f[p][lim]=1;
		for(int i=0; i<n; ++i)
			for(int j=0; j<m; ++j)
			{
				p^=1; memset(f[p],0,sizeof f[p]);
				for(int s=0; s<=lim; ++s)
				{
					f[p][s^(1<<j)]+=f[p^1][s];
					if(j && s>>j&1 && !((s>>j-1)&1)) f[p][s|(1<<j-1)]+=f[p^1][s];
				}
			}
		printf("%lld\n",f[p][lim]);
	}
	return 0;
}
