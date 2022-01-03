/*
20076K 297MS
Dinkelbach迭代 并不明白原理 先将就用 
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=1005;
const double eps=1e-4,INF=1e8;

int n,x[N],y[N],z[N],cost[N][N],pre[N];
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
double Check(double x)
{
	for(int i=1; i<=n; ++i)
		for(int j=i+1; j<=n; ++j)
			e[j][i]=e[i][j]=1.0*cost[i][j]-x*dis[i][j];
	double Dis=0,Cost=0;//Prim
	memset(vis,0,sizeof vis);
	for(int i=2; i<=n; ++i) d[i]=e[1][i],pre[i]=1;
	d[0]=INF, vis[1]=1;
	for(int now,i=1; i<n; ++i)
	{
		now=0;
		for(int j=2; j<=n; ++j)
			if(!vis[j] && d[j]<d[now]) now=j;
		vis[now]=1, Dis+=dis[pre[now]][now], Cost+=cost[pre[now]][now];
		for(int j=2; j<=n; ++j)
			if(!vis[j] && d[j]>e[now][j])
				d[j]=e[now][j], pre[j]=now;
	}
	return Cost/Dis;
}

int main()
{
	while(n=read(),n)
	{
		for(int i=1; i<=n; ++i) x[i]=read(),y[i]=read(),z[i]=read();
		for(int i=1; i<n; ++i)
			for(int j=i+1; j<=n; ++j)
				dis[j][i]=dis[i][j]=Calc(i,j), cost[j][i]=cost[i][j]=std::abs(z[i]-z[j]);
		double x=0,y;
		while(1)
		{
			y=Check(x);
			if(fabs(x-y)<eps) break;
			x=y;
		}
		printf("%.3f\n",x);
	}
	return 0;
}
