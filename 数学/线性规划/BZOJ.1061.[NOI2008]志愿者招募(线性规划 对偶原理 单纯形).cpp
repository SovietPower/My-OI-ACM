//79668kb	1172ms
//https://www.cnblogs.com/SovietPower/p/9362857.html
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define eps 1e-8
const int N=1005,M=10005;

int n,m;
double A[M][N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Pivot(int r,int c)
{
	double t=A[r][c]; A[r][c]=1;
	for(int i=0; i<=n; ++i) A[r][i]/=t;
	for(int i=0; i<=m; ++i)
		if(i!=r && fabs(A[i][c])>eps)
		{
			double t=A[i][c]; A[i][c]=0;
			for(int j=0; j<=n; ++j) A[i][j]-=t*A[r][j];
		}
}
void Simplex()
{
	for(int r,c; ; )
	{
		r=c=0;
		for(int i=1; i<=n; ++i)
			if(A[0][i]>eps) {c=i; break;}
		if(!c) break;
		double mn=1e15;
		for(int i=1; i<=m; ++i)
			if(A[i][c]>eps && mn>A[i][0]/A[i][c]) r=i, mn=A[i][0]/A[i][c];
		if(!r) break;
		Pivot(r,c);
	}
}

int main()
{
	n=read(), m=read();
	for(int i=1; i<=n; ++i) A[0][i]=read();
	for(int i=1,l,r; i<=m; ++i)
	{
		l=read(), r=read(), A[i][0]=read();
		for(int j=l; j<=r; ++j) A[i][j]=1;
	}
	Simplex(), printf("%.0lf\n",-A[0][0]);
	
	return 0;
}
