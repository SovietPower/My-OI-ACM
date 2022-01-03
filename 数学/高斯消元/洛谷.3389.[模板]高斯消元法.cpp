#include <cmath>
#include <cstdio>
#include <algorithm>
const int N=105;
const double eps=1e-10;

int n;
inline bool bigger(double a,double b) {return std::fabs(a)>std::fabs(b);}
inline bool cmp(double a) {return std::fabs(a)>eps;}
struct Gauss
{
	double f[N][N],ans[N];
	void Init()
	{
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=n+1; ++j)
				scanf("%lf",&f[i][j]);
	}
	bool Solve()
	{
		for(int j=1; j<=n; ++j)
		{
			int mxrow=j;
			for(int i=j+1; i<=n; ++i)
				if(bigger(f[i][j],f[mxrow][j])) mxrow=i;
			if(mxrow!=j) std::swap(f[j],f[mxrow]);
//				for(int i=1; i<=n+1; ++i)
//					std::swap(f[j][i],f[mxrow][i]);
			for (int i=j+1; i<=n; ++i)
				if(cmp(f[i][j]))
				{
					double t=f[i][j]/f[j][j];
					for(int k=1; k<=n+1; ++k)
						f[i][k]-=f[j][k]*t;
				}
		}
		for(int i=n; i; --i)
		{
			if(!cmp(f[i][i])) return 0;
			for(int j=i+1; j<=n; ++j)
				f[i][n+1]-=f[i][j]*ans[j];
			ans[i]=f[i][n+1]/f[i][i];
		}
		return 1;
	}
	void Print()
	{
		for(int i=1; i<=n; ++i) printf("%.2lf\n",ans[i]);
	}
}g;

int main()
{
	scanf("%d",&n);
	g.Init();
	if(g.Solve()) g.Print();
	else printf("No Solution");
	return 0;
}
