/*
29392kb	1952ms
$Description$
给定序列$a_n$和$A,B$，每次从序列中删除连续的一段，代价为$A+B*(\max-\min)^2$。删除后剩余数会前移。求删完的最小代价。
$n\leq 50,a_i\leq 1000$。
$Solution$
显然是个区间DP。令$f[l][r]$表示全部消掉区间$[l,r]$的最小花费。
因为是可以通过删掉若干子串来删子序列的，所以并不好直接转移。而花费只与最大最小值有关，所以再令$g[l][r][j][k]$表示将区间$[l,r]$中的数删到只剩下权值在$[j,k]$中的数的最小花费（也就是让剩下数的最小值为$j$，最大值为$k$，最后一次取走$[j,k]$这些数来删掉整个$[l,r]$）。为了方便转移强制右端点$r$保留，同整个区间最后一起删掉。
然后$f,g$就可以互相转移了：$g[l][r][\min(val_r,j)][\max(val_r,k)]=\min\{g[l][i][j][k]+f[i+1][r-1]\}$，$f[l][r]=\min\{f[l][i]+g[i+1][r][j][k]+Cost(j,k)\}$。
复杂度$O(n^5)$。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define Sqr(x) ((x)*(x))
typedef long long LL;
const int N=52;

int w[N],ref[N],f[N][N],g[N][N][N][N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	const int n=read(),A=read(),B=read();
	for(int i=1; i<=n; ++i) w[i]=ref[i]=read();
	std::sort(ref+1,ref+1+n);
	int cnt=std::unique(ref+1,ref+1+n)-ref-1;
	for(int i=1; i<=n; ++i) w[i]=std::lower_bound(ref+1,ref+1+cnt,w[i])-ref;

	memset(f,0x3f,sizeof f), memset(g,0x3f,sizeof g);
	for(int i=1; i<=n; ++i) f[i][i]=A, f[i][i-1]=0, g[i][i][w[i]][w[i]]=0;
	f[n+1][n]=0;
	for(int len=1; len<n; ++len)
		for(int l=1,r; (r=l+len)<=n; ++l)
		{
			for(int i=l; i<r; ++i)
				for(int j=1; j<=cnt; ++j)
					for(int k=j,nj=std::min(j,w[r]),nk; k<=cnt; ++k)
						nk=std::max(k,w[r]), g[l][r][nj][nk]=std::min(g[l][r][nj][nk],g[l][i][j][k]+f[i+1][r-1]);
			for(int i=l-1; i<r; ++i)
				for(int j=1; j<=cnt; ++j)
					for(int k=j; k<=cnt; ++k)
						f[l][r]=std::min(f[l][r],f[l][i]+g[i+1][r][j][k]+A+B*Sqr(ref[k]-ref[j]));
//						f[l][r]=std::min(f[l][r],g[l][i][j][k]+f[i+1][r]+A+B*Sqr(ref[k]-ref[j]));
		}
	printf("%d\n",f[1][n]);

	return 0;
}
