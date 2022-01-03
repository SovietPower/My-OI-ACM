/*
假设抛物线上一点p'为(x,ax^2+bx+c)，则p(X,Y)与p'的距离为min{sqrt((X-x)^2+(Y-ax^2-bx-c)^2)}
化简后是个四次函数，可以用求导来求极值，但是对计算机很麻烦...
可以发现代入x的不同，dis的变化是个凸函数(下凹) 
而求的dis，就是这个凸函数的极点 
注意三分边界不是x的，是dis的，可以把精度设得更高些，这样没必要记上一次的值(虽然不知道这样为什么错) 
*/
#include<cmath>
#include<cstdio>
using namespace std;
const double eps=1e-7;

double a,b,c,X,Y;

double Calc(double x)
{
	return sqrt((x-X)*(x-X)+(Y-a*x*x-b*x-c)*(Y-a*x*x-b*x-c));
}

int main()
{
	scanf("%lf%lf%lf%lf%lf",&a,&b,&c,&X,&Y);
	double l=-1e4,r=1e4,lm,rm;//左右边界大一些 
	while(r-l>eps)
	{
		lm=l+(r-l)/3, rm=r-(r-l)/3;
		if(Calc(lm)>Calc(rm)) l=lm;
		else r=rm;
	}
	printf("%.3lf",Calc(l));

	return 0;
}
