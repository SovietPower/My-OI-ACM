/*
0MS	1260K
插头DP。对于本题我们只需要记录之前$m$个格子的$m+1$个插头是否存在。
转移时根据左边、上边是否有插头讨论。用位运算可以写的很方便。
因为想对DP数组压压维，我也觉得写的好不直观=-=。反正就是从上一个格子转移，解决完一行将状态左移一位转给下一行。可以看链接里的代码。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=12;

LL f[2][(1<<N)+2];//m+1
bool mp[N][N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void Work(int x,int y,int lim,LL *f,LL *g)
{
	if(mp[x][y])
		for(int s=0,p1=1<<y-1,p2=1<<y; s<lim; ++s)
		{
			f[s^p1^p2]+=g[s];
			if((s>>y-1&1)!=(s>>y&1)) f[s]+=g[s];
		}
	else
		for(int s=0,p1=1<<y-1,p2=1<<y; s<lim; ++s)
			if(!(s&p1) && !(s&p2)) f[s]=g[s];
			else f[s]=0;
}

int main()
{
	for(int T=1,T2=read(); T<=T2; ++T)
	{
		int n=read(),m=read(),l1=1<<m,l2=1<<m+1;
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=m; ++j) mp[i][j]=read();
		int p=0; memset(f[p],0,sizeof f[p]);
		f[p][0]=1;
		for(int i=1; i<=n; ++i)
		{
			for(int j=1; j<=m; ++j)
			{
				p^=1, memset(f[p],0,sizeof f[p]);
				Work(i,j,l2,f[p],f[p^1]);
			}
			if(i!=n)
			{
				p^=1, memset(f[p],0,sizeof f[p]);
				for(int s=0; s<l1; ++s) f[p][s<<1]=f[p^1][s];
			}
		}
		printf("Case %d: There are %lld ways to eat the trees.\n",T,f[p][0]);//f[n][m][0]
	}
	return 0;
}
