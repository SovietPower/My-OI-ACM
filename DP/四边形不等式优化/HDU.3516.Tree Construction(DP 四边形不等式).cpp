/*
$Description$
给出平面上的n个点，满足Xi严格单增，Yi严格单减。以x轴和y轴正方向作边，使这n个点构成一棵树，求边总长最小。
$Solution$
考虑有两棵构造好的树，要合并这两棵树，要从右边的树中找一个最优点连到左边的树上 
不难想到区间DP(~~真的想不到==~~) 
f[i][j]表示将[i,j]合并为一棵树的最小代价，那么有 f[i][j] = min{ f[i][k-1]+f[k][j]+cost(i,j,k) }
cost(i,j,k)=X[k]-X[i]+Y[k-1]-Y[j] //ps: 当前左边树主干在Xi位置，且下部高度为Y_{k-1}，合并后下部应为Yj；另外肯定是拿右边树的最左上点合并啊 
这个cost是三维的，证不了cost满足四边形不等式 
那想下 决策应该是满足单调性的，即 P[i][j-1]<=P[i][j]<=P[i+1][j] 
注意左端点应是max(P[i][j-1],i+1) 
f应该满足四边形不等式，不会证。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=1005;

int n,X[N],Y[N],P[N][N],f[N][N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	while(~scanf("%d",&n))
	{
		for(int i=1; i<=n; ++i) X[i]=read(),Y[i]=read();
		memset(f,0x3f,sizeof f);
		for(int i=1; i<=n; ++i) P[i][i]=i, f[i][i]=0;
		for(int tmp,i=n-1; i; --i)
			for(int j=i+1; j<=n; ++j)
				for(int k=std::max(P[i][j-1],i+1); k<=P[i+1][j]; ++k)
					if(f[i][j]>(tmp=f[i][k-1]+f[k][j]+X[k]-X[i]+Y[k-1]-Y[j]))
						f[i][j]=tmp, P[i][j]=k;
		printf("%d\n",f[1][n]);
	}
	return 0;
}
