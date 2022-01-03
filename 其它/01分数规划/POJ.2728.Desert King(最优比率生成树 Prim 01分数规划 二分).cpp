/*
19100K 1235MS
$Description$
将n个村庄连成一棵树，村之间的距离为两村的欧几里得距离，村之间的花费为海拔z的差，求花费和与长度和的最小比值 
$Solution$
二分，假设mid为可行的某一生成树的解，则应有 (∑cost)/(∑dis) = mid 
变形得 ∑(cost-mid*dis) = 0 
取cost-mid*dis为边权，Prim求最小生成树(即尽可能满足mid) 
若∑(cost-mid*dis) > 0，说明怎么也满足不了mid，mid不是可行解 偏小；若 < 0，则存在某些生成树满足条件，还可以更优 
若 = 0，那么就是最小值了 
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=1005;
const double eps=1e-4,INF=1e8;

int n,x[N],y[N],z[N],cost[N][N];
double dis[N][N],e[N][N],d[N];
bool vis[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline double Calc(int i,int j) {return sqrt(1.0*(x[i]-x[j])*(x[i]-x[j])+1.0*(y[i]-y[j])*(y[i]-y[j]));}
bool Check(double x)
{
	for(int i=1; i<=n; ++i)
		for(int j=i+1; j<=n; ++j)
			e[j][i]=e[i][j]=1.0*cost[i][j]-x*dis[i][j];
	double res=0;//Prim
	memset(vis,0,sizeof vis);
	for(int i=2; i<=n; ++i) d[i]=e[1][i];
	d[0]=INF, vis[1]=1;
	for(int now,i=1; i<n; ++i)
	{
		now=0;
		for(int j=2; j<=n; ++j)
			if(!vis[j] && d[j]<d[now]) now=j;
		vis[now]=1, res+=d[now];
		for(int j=2; j<=n; ++j)
			if(!vis[j] && d[j]>e[now][j])
				d[j]=e[now][j];
	}
	return res<=0;
}

int main()
{
	while(n=read(),n)
	{
		for(int i=1; i<=n; ++i) x[i]=read(),y[i]=read(),z[i]=read();
		for(int i=1; i<n; ++i)
			for(int j=i+1; j<=n; ++j)
				dis[i][j]=Calc(i,j),cost[i][j]=std::abs(z[i]-z[j]);
		double l=0.0,r=101.0,mid;//r=多少啊。。
		while(r-l>=eps)
		{
			if(Check(mid=(l+r)/2.0)) r=mid;
			else l=mid;
		}
		printf("%.3f\n",l);//POJ不能用%lf! 惊了 刚知道 
	}
	return 0;
}
