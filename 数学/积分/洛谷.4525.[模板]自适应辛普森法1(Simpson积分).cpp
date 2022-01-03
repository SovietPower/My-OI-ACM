//0ms	1.7MB
#include <cmath>
#include <cstdio>
#include <algorithm>
#define eps (1e-6)

double a,b,c,d,L,R;

inline double f(double x){
	return (c*x+d)/(a*x+b);
}
inline double Simpson(double l,double r){
	return (r-l)*(f(r)+f(l)+4*f((l+r)*0.5))/6.0;
}
double asr(double l,double r,double Eps,double ans)
{
	double mid=(l+r)*0.5, lans=Simpson(l,mid), rans=Simpson(mid,r);
	if(fabs(lans+rans-ans)<Eps) return lans+rans;
	return asr(l,mid,Eps*0.5,lans)+asr(mid,r,Eps*0.5,rans);
}

int main()
{
	scanf("%lf%lf%lf%lf%lf%lf",&a,&b,&c,&d,&L,&R);
	printf("%.6lf",asr(L,R,eps,Simpson(L,R)));

	return 0;
}
