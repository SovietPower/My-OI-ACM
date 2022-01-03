//824kb	40ms
//HDU3571弱化版 跟那个一比这个太水了，练模板吧。
//列出$n+1$个二次方程后两两相减，就都是一次方程了。
#include <cmath>
#include <cstdio>
#include <algorithm>
const int N=12;

int n;
double A[N][N],B[N],f[N][N];

void Gauss()
{
	for(int mxrow,j=0; j<n; ++j)
	{
		mxrow=j;
		for(int i=j+1; i<n; ++i)
			if(fabs(f[i][j])>fabs(f[mxrow][j])) mxrow=i;
		if(mxrow!=j) std::swap(f[mxrow],f[j]);
		for(int i=j+1; i<n; ++i)
			if(f[i][j])
			{
				double t=f[i][j]/f[j][j];
				for(int k=j; k<=n; ++k)
					f[i][k]-=t*f[j][k];
			}
	}
	for(int i=n-1; ~i; --i)
	{
		for(int j=i+1; j<n; ++j) f[i][n]-=f[i][j]*f[j][n];
		f[i][n]/=f[i][i];
	}
	for(int i=0; i<n; ++i) printf("%.3lf ",f[i][n]);
}

int main()
{
	scanf("%d",&n);
	for(int i=0; i<=n; ++i)
		for(int j=0; j<n; ++j)
			scanf("%lf",&A[i][j]), B[i]+=A[i][j]*A[i][j];
	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j) f[i][j]=(A[i][j]-A[i+1][j])*2.0;
	for(int i=0; i<n; ++i) f[i][n]=B[i]-B[i+1];
	Gauss();

	return 0;
}
