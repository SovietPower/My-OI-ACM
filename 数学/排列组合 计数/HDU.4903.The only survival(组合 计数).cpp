/*
312MS	1200K
$Description$
给定$n,k,L$，表示，有一张$n$个点的无向完全图，每条边的边权在$[1,L]$之间。求有多少张无向完全图满足，$1$到$n$的最短路为$k$。
$n,k\leq 12,\ L\leq10^9$。
$Solution$
考虑暴力，直接枚举$1$到每个点的最短路$d_i$是多少。
对于方案数，如果$d_i=d_j$，那么$i,j$之间的边权随便定。否则设$d_i\lt d_j$，那么$i,j$之间的边权不小于$d_j-d_i$，且对于$j$，至少存在一个$i$满足$d_i+e[i][j]=d_j$。
这样的复杂度是$O(12^{13})$的（$d_i\geq k$的全在一起算）。

注意到我们并不关心具体$d_i=x$的点是哪些。所以考虑直接枚举$d_i=x$的点有多少个。
$DFS$一下，算下组合数就好啦。复杂度是$C_{n-1+k}^k$叭？
**具体：**首先要强制$d_1=0,d_n=k$。
对于当前的$x$，如果有$t$个点$d_i=x$，它们之间可以任意连边，方案数是，$\prod_{i=0}^{t-1}L^i$。（当然还要乘个组合数）
然后这$t$个点和之前$m$个点连边，不考虑存在$d_i+e[i][j]=x$的限制，（每个点的）方案数是$\prod_{i=1}^{m}(L-(x-d_i)+1)$，容斥一下，再减掉$\prod_{i=1}^{m}(L-(x-d_i))$，就可以啦。
如果要求的最短路$\geq k$，不需要减后面那项（在边权范围内xjb连即可，不是需要恰好$=k$）。
最后再算一下$n$点连边的方案数即可。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define mod 1000000007
#define gc() getchar()
typedef long long LL;
const int N=15;

int n,K,L,C[N][N],now,d[N],pw[N];
LL Ans;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
void DFS(int x,int coef)
{
	LL c1=1,c2=1;
	for(int i=1; i<=now; ++i) c1=c1*(L-x+d[i]+1)%mod, c2=c2*(L-x+d[i])%mod;
	LL c3=c1+mod-c2;
	if(x==K)
	{
		LL c=coef*c3%mod*pw[n-1-now]%mod;//n与其他点的贡献 
		for(int i=now+1; i<n; ++i) c=c*c1%mod*pw[i-now-1]%mod;
		Ans+=c;
		return;
	}
	DFS(x+1,coef);
	int tmp=now,t=0;
	for(LL c=coef; now+1<n; )
		d[++now]=x, c=c*c3%mod*pw[t]%mod, ++t, DFS(x+1,c*C[n-1-now+t][t]%mod);
	now=tmp;
}

int main()
{
	C[0][0]=pw[0]=1;
	for(int i=1; i<=12; ++i)
	{
		C[i][0]=C[i][i]=1;
		for(int j=1; j<i; ++j) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	for(int T=read(); T--; )
	{
		n=read(),K=read(),L=read();
		for(int i=1; i<=n; ++i) pw[i]=1ll*pw[i-1]*L%mod;
		Ans=0, d[now=1]=0, DFS(1,1), printf("%lld\n",Ans%mod);
	}

	return 0;
}
