/*
78ms	1100KB
$Description$
给定$v_i,a_i$，每次可以在$a_i$中删除一个子段$[l,r]$，但需满足：$|a_i-a_{i+1}|=1,\ 2a_i\geq a_{i+1}+a_{i-1}$。
删除后将该子段删除，并获得$v_{r+l-1}$的收益。可以不删完。求最大收益。
$n\leq 400$。
$Solution$
合法的子序列只有三种情况：递增，递减，前半部分递增然后一直递减（下去了就不会再上去了）（当然还要都满足$|a_{i+1}-a_i|=1$）。
容易想到区间DP。$f[i][j]$表示把区间$[i,j]$全部删除的最大收益，还需要$g[i][j]$表示将区间$[i,j]$删成连续上升的一段（$a_i\sim a_j$）的最大收益，$h[i][j]$表示将区间$[i,j]$删成连续下降的一段（$a_i\sim a_j$）的最大收益。
那么$g[i][j]$的元素个数就是$a_j-a_i+1$，$h[i][j]$的元素个数为$a_i-a_j+1$，合并$g[i][k],h[k][j]$后的元素个数就是$2a_k-a_i-a_j+2-1$（减掉1个$a_k$）。
那么
$$f[i][j]=\max\{f[i][k]+f[k+1][j],\ g[i][k]+h[k][j]+v[2a_k-a_i-a_j+1]\}$$
其实$g,h$用一个数组就可以了，因为只需要判断一下$a_i,a_j$的大小关系，就知道是上升序列还是下降序列了。
最后的答案就是$f$的最大子段和。$n^2$求出来即可。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=405,INF=0x3f3f3f3f;

int A[N],val[N],f[N][N],g[N][N],dp[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) val[i]=read();
	for(int i=1; i<=n; ++i) A[i]=read();

	for(int i=1; i<=n; ++i)
	{
		f[i][i]=val[1], g[i][i]=0;
		for(int j=i+1; j<=n; ++j) f[i][j]=g[i][j]=-INF;
	}

	for(int len=1; len<n; ++len)
		for(int i=1; i+len<=n; ++i)
		{
			int j=i+len;
			for(int k=i; k<j; ++k)
			{
				f[i][j]=std::max(f[i][j],f[i][k]+f[k+1][j]);
				if((A[i]<A[j] && A[j]==A[k]+1)||(A[i]>A[j] && A[j]==A[k]-1))
					g[i][j]=std::max(g[i][j],g[i][k]+f[k+1][j-1]);
			}
			for(int k=i; k<=j; ++k)
				if(A[k]>=A[i] && A[k]>=A[j] && 2*A[k]-A[i]-A[j]+1<=n)//这东西显然不会<=0啊 
					f[i][j]=std::max(f[i][j],g[i][k]+g[k][j]+val[2*A[k]-A[i]-A[j]+1]);
		}
	for(int i=1; i<=n; ++i)
	{
		dp[i]=dp[i-1];
		for(int j=1; j<=i; ++j) dp[i]=std::max(dp[i],dp[j-1]+f[j][i]);
	}
	printf("%d\n",dp[n]);

	return 0;
}
