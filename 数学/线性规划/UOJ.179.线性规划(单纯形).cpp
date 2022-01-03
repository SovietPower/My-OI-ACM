/*
0ms	520kb
引入基变量$x_{i+n}$，将约束$\sum_{i=1}^m a_{ij}x_j\leq b_i$改写为$x_{i+n}=b_i-\sum_{i=1}^m a_{ij}x_j$。
目标函数为$\sum_{i=1}^n C_ix_i$。当存在$r,c$满足$C_c>0$,$B_r>0$,$a_{rc}>0$，对第$r$个限制中的$x_c$做代换，即$x_c=B_r-\sum_{j!=c}a_{rj}x_j-x_{r+n}$（$x_c$成为基变量，$x_{r+n}$成为非基变量），然后代入目标函数中，非基变量取0，就一定可以使目标函数增大。
这一步通过$Pivot(r,c)$(转轴)实现，同时要把其它约束中的$x_c$替换掉。
若存在$B_r<0$，在限制$r$中找一个$a_{rc}<0$的$x_c$做代换，就可以使$B_r>0$。
当然前提是任意$x_i>0,I\in [1,n+m]$。
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define eps 1e-8
const int N=25;
const double INF=1e9;

int n,m,id[50];
double A[N][N],Ans[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
void Pivot(int r,int c)//r:Basic varivle c:Nonbasic variable
{//交换基变量与非基变量 
	std::swap(id[r+n],id[c]);
	double t=A[r][c]; A[r][c]=1;
	for(int i=0; i<=n; ++i) A[r][i]/=t;
	for(int i=0; i<=m; ++i)//在其它等式中换掉基变量 
		if(fabs(A[i][c])>eps && i!=r)
		{
			t=A[i][c]; A[i][c]=0;
			for(int j=0; j<=n; ++j) A[i][j]-=t*A[r][j];
		}
}
bool Init()
{
	for(int r,c; ; )
	{
		r=c=0;
		for(int i=1; i<=m; ++i)//B[r]<0
			if(A[i][0]<-eps && (!r || rand()&1)) r=i;
		if(!r) return 1;
		for(int i=1; i<=n; ++i)//A[r][c]<0
			if(A[r][i]<-eps && (!c || rand()&1)) c=i;
		if(!c) return puts("Infeasible"),0;
		Pivot(r,c);
	}
}
bool Simplex()
{
	for(int r,c; ; )
	{
		r=c=0;
		for(int i=1; i<=n; ++i)//C[c]>0 
			if(A[0][i]>eps) {c=i; break;}
		if(!c) return 1;
		double mn=INF;//找一个系数为正且约束最紧的A[r][c] 
		for(int i=1; i<=m; ++i)
			if(A[i][c]>eps && A[i][0]/A[i][c]<mn) r=i, mn=A[i][0]/A[i][c];
		if(!r) return puts("Unbounded"),0;//无约束
		Pivot(r,c);
	}
}

int main()//x[i+n]=B[i]-∑a[i][j]*x[j]
{
	srand(20180724);
	n=read(), m=read(); int type=read();
	for(int i=1; i<=n; ++i) A[0][i]=read();//目标函数系数C[i] 
	for(int i=1; i<=m; ++i)
	{
		for(int j=1; j<=n; ++j) A[i][j]=read();
		A[i][0]=read();//B[i]
	}
	for(int i=1; i<=n; ++i) id[i]=i;
	if(Init() && Simplex())
	{
		printf("%.8lf\n",-A[0][0]);//代换的时候Bi系数是负的s 
		if(type)
		{
			for(int i=1; i<=m; ++i) Ans[id[i+n]]=A[i][0];//成为基变量的xi取值即为bi，非基变量上的xi取0.
			for(int i=1; i<=n; ++i) printf("%.8lf ",Ans[i]);
		}
	}

	return 0;
}
