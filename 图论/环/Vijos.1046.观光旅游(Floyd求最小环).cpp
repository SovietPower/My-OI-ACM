/*
最小环：
朴素算法：令e(u,v)表示u->v的连边，min(u,v)表示删掉e(u,v)后u->v的最短路 
		则最小环为 min(u,v) + e(u,v)
		O(EV^2) 
优化：将环分成三段，断点为i、j、k，环长则为两两距离，且路不能有交点 
	 所以想到 Map[i][k] + Map[k][j] + Min[i][j]，Map是两点直接相连的边，Min是最短路 
	 只要i到j的最短路Min[i][j]不经过k，那这就是一个环 
	 Folyd中，最外层循环进行k-1次后，dis[i][j]表示i到j的路径中，所有点的编号都<k的最短路径 
	 综上，Floyd一定能找到最小环 
(Floyd原理：http://blog.csdn.net/zhongkeli/article/details/8832946)

注意重边 注意3*INF不要溢出 
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=103,INF=1e8;

int n,m,dis[N][N],Map[N][N],Ans;

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar())
	  if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}

void Floyd()
{
	Ans=INF;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			dis[i][j]=Map[i][j];
	for(int k=1;k<=n;++k)
	{
		for(int i=1;i<k;++i)
			for(int j=i+1;j<k;++j)
				Ans=min(Ans,dis[i][j]+Map[i][k]+Map[k][j]);
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				dis[i][j]=min(dis[i][k]+dis[k][j],dis[i][j]);
	}
}

int main()
{
	while(~scanf("%d%d",&n,&m))
	{
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
//				if(i==j)
//					Map[i][j]=0;
//				else
					Map[i][j]=INF;
		for(int u,v,w,i=1;i<=m;++i)
			u=read(),v=read(),w=read(),
			Map[u][v]=Map[v][u]=min(Map[v][u],w);
		Floyd();
		if(Ans==INF)
			puts("No solution.");
		else
			printf("%d\n",Ans);
	}
	
	return 0;
}
