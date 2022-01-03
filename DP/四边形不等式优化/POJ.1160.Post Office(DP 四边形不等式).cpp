/*
$Description$
一条直线上有n个村庄，位置各不相同。选择p个村庄建邮局，求每个村庄到最近邮局的距离之和的最小值。
$Solution$
先考虑在[l,r]建一个邮局，最优解肯定是建在中间。
这样mid两边对称，距离和是最小的；若建在mid-1，(假设mid与mid-1相距1)虽然左边mid-1个村庄dis都-1了，但是右边有mid个村庄dis+1 
如果区间长度为偶数，建在中间两个位置任意一个都是最优的。 
设f[i][j]表示在前i个村庄建了j个邮局的最小值，那么 f[i][j] = min{ f[k][j-1]+dis(k+1,i) }
dis(k+1,i)表示只考虑在[k+1,i]建一个邮局的最小值 
预处理dis时 如果已知dis[i][j-1]，那么无论j-1是奇是偶，dis[i][j]都等于dis[i][j-1]+ j到i~j中点的距离(也可以算出来吧) 
另外满足决策单调性P[i][j-1]<=P[i][j]<=P[i+1][j]，应该能用四边形不等式优化到O(np) 
~~于是从0ms优化到了16ms??~~0ms了 
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=305;

int n,m,A[N],f[N][35],dis[N][N],P[N][N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void DP1()//O(n^2m)
{
	for(int i=1; i<=n; ++i)
		for(int j=2; j<=m; ++j)//from 2
			for(int k=j-1; k<i; ++k)
				f[i][j]=std::min(f[i][j],f[k][j-1]+dis[k+1][i]);
}
void DP2()//O(nm)
{
	for(int tmp,j=2; j<=m; ++j)//先枚举j吧 (不知道为什么先i不对==) 
	{
		P[n+1][j]=n-1;//上边界！
		for(int i=n; i>=j; --i)
			for(int k=P[i][j-1]; k<=P[i+1][j]; ++k)
				if(f[i][j]>(tmp=f[k][j-1]+dis[k+1][i]))
					f[i][j]=tmp, P[i][j]=k;
	}
}

int main()
{
	n=read(),m=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<n; ++i)
		for(int j=i+1; j<=n; ++j)
			dis[i][j]=dis[i][j-1]+A[j]-A[i+j>>1];
	memset(f,0x3f,sizeof f);
	for(int i=1; i<=n; ++i) f[i][1]=dis[1][i] ,P[i][i]=i;//预处理！
	DP2();
	printf("%d",f[n][m]);

	return 0;
}
