/*
374ms	147200KB
$Description$
给定一个n边凸多边形(保证没有三点共线)，选择一条经过每个点最多一次的不会相交的路径，使得其长度最大。输出这个长度。
$Solution$
最长路径应该是尽可能多走点。因为路径不相交，如果当前在x，下次应是向x+1或x-1连边，区间也是如此，即当前区间一定是连续的。
画画图可以发现，每个状态应该是左边可以再连出边或右边可以再连出边。
那么令f[i][j][0/1]表示在[i,j]时左边/右边可以再连出边时的最长路径长度。
i->j在环上有两条路径，这都要考虑。所以i>j时表示从j逆时针走到i这条路径(i顺时针到j)。
转移可以从小区间每次长度+1地推到大的，所以只需O(n^2)。
f[i][j][0] = max(f[i+1][j][0]+dis(i,i+1), f[i+1][j][1]+dis(i,j)) (f[i][j-1][0/1]显然都不对啊)
f[i][j][1] = max(f[i][j-1][0]+dis(i,j), f[i][j-1][1]+dis(j,j-1))
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define Turn(x) ((x+n-1)%n+1)
#define Calc(x,x2,y,y2) (sqrt(1.0*(x-x2)*(x-x2)+1.0*(y-y2)*(y-y2)))
const int N=2505;

int n,x[N],y[N];
double dis[N][N],f[N][N][2];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) x[i]=read(),y[i]=read();
	for(int i=1; i<n; ++i)
		for(int j=i+1; j<=n; ++j)
			dis[j][i]=dis[i][j]=Calc(x[i],x[j],y[i],y[j]);
	double ans=0;
	for(int len=1; len<n; ++len)
		for(int i=1,j; i<=n; ++i)
		{
			j=Turn(i+len);
			f[i][j][0] = std::max(f[Turn(i+1)][j][0]+dis[i][Turn(i+1)], f[Turn(i+1)][j][1]+dis[i][j]);
			f[i][j][1] = std::max(f[i][Turn(j-1)][0]+dis[i][j], f[i][Turn(j-1)][1]+dis[j][Turn(j-1)]);
			ans=std::max(ans,std::max(f[i][j][0],f[i][j][1]));//不一定走n个点...吗?
		}
	printf("%.10lf\n",ans);

	return 0;
}
