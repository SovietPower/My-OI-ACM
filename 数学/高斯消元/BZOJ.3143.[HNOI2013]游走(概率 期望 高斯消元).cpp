/*
12784kb	740ms
$Description$
给定无向连通图，从$1$开始随机游走，到点$n$结束。每走过一条边会获得其编号对应的分数（可重复获得）。安排每条边的编号，使得分的期望值最小。输出最小值。
$n\leq 500$。
$Solution$
　　把走每条边的概率乘上分配的标号就是它的期望，所以我们肯定是把大的编号分配给走的概率最低的边。
　　我们只要计算出经过所有点的概率，就可以得出经过一条边($u->v$)的概率$P_{ei}$。用$dgr[i]$表示点$i$的度数，那么
$$P_{ei}=\frac{P_u}{dgr[u]}+\frac{P_v}{dgr[v]}$$
　　每个点的概率怎么求呢？就是
$$P_i=\sum_{(i,j)\in G}\frac{P_j}{dgr[j]}$$
　　用$a[i][j]$为从点$j$走到点$i$的概率，即
$$a[i][j]=\frac{1}{dgr[j]}$$
　　那么每个点的概率
$$P_i=\sum_{(i,j)\in G} a[i][j]\times P[j]$$
　　注意走到$n$就不会再走了，所以高斯消元不处理与$n$有关的东西。
　　$a[i][i]=1$，然后把每个概率$P_i$看做一个变量，可以列出$n-1$个含$n-1$个未知数的方程
$$a[i][i]\times P_i-a[i][j]\times P_j-a[i][k]\times P_k-\ldots = 0$$
　　每个$a[i][i]$对应的变量就是$P_i$了。

　　因为一开始就在$1$号点，所以第一个方程的结果应设为$1$，即$P_1=1+\sum\frac{P_j}{dgr[j]}$。
　　高斯消元，复杂度$O(n^3)$，好像有$\frac{1}{6}$的常数？
注意边数，没说就是n^2级别的！
精度(eps)要高！
md高斯写错。。
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <iostream>
#include <algorithm>
#define gc() getchar()
#define eps 1e-12
const int N=505,M=N*N*2;

int n,m,Enum,H[N],fr[M],to[M],nxt[M],dgr[N];
double A[N][N],Ans[N],pe[M];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v)
{
	++dgr[u], to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum;
	++dgr[v], to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum;
}
inline bool cmp(const double &a,const double &b){
	return std::fabs(a)>std::fabs(b);
}
void Gauss()
{
	for(int j=1; j<n; ++j)
	{
		int mxrow=j;
		for(int i=j+1; i<n; ++i)
			if(cmp(A[i][j],A[mxrow][j])) mxrow=i;
		if(mxrow!=j) std::swap(A[mxrow],A[j]);//和下一行也差不多 
//		if(mxrow!=j) for(int i=1; i<=n; ++i) std::swap(A[mxrow][i],A[j][i]);
		for(int i=j+1; i<n; ++i)
			if(fabs(A[i][j])>eps)//判一下显然快(吗?) 但要注意精度 
//			if(A[i][j])
			{
				double t=A[i][j]/A[j][j];
				for(int k=j; k<=n; ++k)
					A[i][k]-=A[j][k]*t;
			}
	}
	for(int i=n-1; i; --i)
	{
		for(int j=i+1; j<n; ++j) A[i][n]-=A[i][j]*Ans[j];
		Ans[i]=A[i][n]/A[i][i];
	}
}

int main()
{
	n=read(),m=read();
	for(int u,v,i=1; i<=m; ++i) u=read(),v=read(),AddEdge(u,v);

	for(int x=1; x<n; A[x][x]=1.0,++x)
		for(int i=H[x]; i; i=nxt[i])
			if(to[i]!=n) A[x][to[i]]=-1.0/dgr[to[i]];
	A[1][n]=1.0;
	Gauss();

	for(int i=1; i<=m; ++i) pe[i]=Ans[fr[i<<1]]/dgr[fr[i<<1]]+Ans[to[i<<1]]/dgr[to[i<<1]];
	std::sort(pe+1,pe+1+m,std::greater<double>());
	double res=0;
	for(int i=1; i<=m; ++i) res+=1.0*i*pe[i];
	printf("%.3lf",res);

	return 0;
}
