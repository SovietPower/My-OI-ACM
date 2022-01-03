/*
$Description$
一个国家有1~n座城市，其中一些城市之间可以修建高速公路(无自环和重边)。
求有多少种方案，选择修建一些高速公路，组成一个交通网络，使得任意两座城市之间恰好只有一条路径。
$Solution$
生成树计数 直接上Matrix Tree 
无解情况别忘了判 
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=15;

int n;
double K[N][N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
double Gauss()
{
	for(int j=1; j<n; ++j)//去掉第一行第一列 
	{
		int mxrow=j;
		for(int i=j+1; i<n; ++i)
			if(fabs(K[i][j])>fabs(K[mxrow][j])) mxrow=i;
		if(!K[mxrow][j]) return 0.0;//别忘判 
		if(mxrow!=j) std::swap(K[mxrow],K[j]);
		for(int i=j+1; i<n; ++i)
			if(K[i][j])
			{
				double t=K[i][j]/K[j][j];
				for(int k=j; k<n; ++k)
					K[i][k]-=t*K[j][k];
			}
	}
	double res=1;
	for(int i=1; i<n/*&& res*/; ++i) res*=K[i][i];
	return res>0?res:-res;
}

int main()
{
	int t=read(),m,u,v;
	while(t--)
	{
		memset(K,0,sizeof K);
		n=read(),m=read();
		while(m--)
			u=read()-1,v=read()-1, ++K[u][u], ++K[v][v], --K[u][v], --K[v][u];
		printf("%.0lf\n",Gauss());
	}
	return 0;
}
