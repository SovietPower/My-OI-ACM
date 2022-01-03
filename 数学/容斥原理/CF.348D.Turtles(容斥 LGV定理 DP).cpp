/*
498ms	44000KB
$Description$
给定$n*m$的网格，有些格子不能走。求有多少种从$(1,1)$走到$(n,m)$的两条不相交路径。
$n,m\leq 3000$。
$Solution$
容斥，用总方案数减去路径一定相交的方案数。
怎么算呢？注意到两条相交的路径（一定）可以看做从$(1,2)$到$(n,m-1)$和从$(2,1)$到$(n-1,m)$的两条路径。总方案数也可以看做从$(1,2)$到$(n-1,m)$和从$(2,1)$到$(n,m-1)$的两条路径（如果有相交可以对称过去得到这样的两条路径）。
所以$(1,2)$到$(n-1,m)$的方案数，乘上$(2,1)$到$(n,m-1)$的方案数，减去，$(1,2)$到$(n-1,m)$的方案数，乘上$(2,1)$到$(n-1,m)$的方案数，就是答案了。
其实我也还是感觉有点迷...

其实有一个引理：[Lindstr?m–Gessel–Viennot lemma](https://en.wikipedia.org/wiki/Lindstr?m–Gessel–Viennot_lemma)。
下面就粘[attack的](https://www.cnblogs.com/zwfymqz/p/10195838.html)了。
> 这个定理是说点集$A=\{a1,a2,…an\}$到$B=\{b1,b2,...,bn\}$的不相交路径条数等于行列式$$\begin{bmatrix}e(a_1, b_1) & e(a_1, b_2) & \dots & e(a_1, b_n) \\
e(a_2, b_1) & e(a_2, b_2) & \dots & e(a_2, b_n) \\
\vdots       & \vdots       & \ddots & \vdots       \\
e(a_n, b_1) & e(a_n, b_2) & \dots & e(a_n, b_n) \\
\end{bmatrix}$$的值。其中$e(x,y)$表示从$x$到$y$的路径条数
定理的本质还是容斥。
本题，我们需要找到两条不相交的路径。注意到任何一对合法的路径一定可以表示为，一条从$(1,2)$出发到$(n?1,m)$，另一条从$(2,1)$出发到$(n,m?1)$。
那么选取$A=\{(1,2)\ (2,1)\},B=\{(n?1,m)\ (n,m?1)\}$，带入到上述定理即可求解。

事实上只用一遍DP就可以了（两个DP数组，分别表示从$(1,2)$和$(2,1)$出发，`for`到$(n,m)$就可以了）。。
也可以加`fread`，懒得改了。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define mod 1000000007
#define Mod(x) x>=mod&&(x-=mod)
const int N=3005;

bool mp[N][N];

int Calc(int sx,int sy,int tx,int ty)
{
	static int f[N][N];
	memset(f,0,sizeof f);
	f[sx-1][sy]=1;//Init: f[sx][sy]=mp[sx][sy]==1;
	for(int i=sx; i<=tx; ++i)
		for(int j=sy; j<=ty; ++j)
			mp[i][j]?(f[i][j]=f[i-1][j]+f[i][j-1],Mod(f[i][j])):0;
	return f[tx][ty];
}

int main()
{
	int n,m; scanf("%d%d",&n,&m);
	char s[N];
	for(int i=1; i<=n; ++i)
	{
		scanf("%s",s+1);
		for(int j=1; j<=m; ++j) mp[i][j]=s[j]=='.';
	}
	printf("%I64d\n",(1ll*Calc(1,2,n-1,m)*Calc(2,1,n,m-1)%mod+mod-1ll*Calc(1,2,n,m-1)*Calc(2,1,n-1,m)%mod)%mod);

	return 0;
}
