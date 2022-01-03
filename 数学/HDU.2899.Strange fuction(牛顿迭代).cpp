//0MS	1628K
//www.cnblogs.com/SovietPower/p/9162128.html
#include <cmath>
#include <cstdio>
#include <algorithm>
#define eps (1e-7)

double y;
inline double f(double x){
	return 6*pow(x,7)+8*pow(x,6)+7*pow(x,3)+5*x*x-y*x;
}
inline double fd(double x){
	return 42*pow(x,6)+48*pow(x,5)+21*x*x+10*x-y;
}
inline double fdd(double x){
	return 252*pow(x,5)+240*pow(x,4)+42*x+10;
}
double Get_zero(double x)
{
	double las=x+1;
	while(fabs(las-x)>eps) las=x, x=x-fd(x)/fdd(x);
	return x;
}

int main()
{
	int T; scanf("%d",&T);
	while(T--)
	{
		scanf("%lf",&y);
		double ans=1e15;
		for(int i=0; i<=100; i+=10) ans=std::min(ans,f(Get_zero(i)));
		printf("%.4lf\n",ans);
	}
	return 0;
}
