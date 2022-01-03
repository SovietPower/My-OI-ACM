/*
������������һ��p'Ϊ(x,ax^2+bx+c)����p(X,Y)��p'�ľ���Ϊmin{sqrt((X-x)^2+(Y-ax^2-bx-c)^2)}
������Ǹ��Ĵκ�����������������ֵ�����ǶԼ�������鷳...
���Է��ִ���x�Ĳ�ͬ��dis�ı仯�Ǹ�͹����(�°�) 
�����dis���������͹�����ļ��� 
ע�����ֱ߽粻��x�ģ���dis�ģ����԰Ѿ�����ø���Щ������û��Ҫ����һ�ε�ֵ(��Ȼ��֪������Ϊʲô��) 
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
	double l=-1e4,r=1e4,lm,rm;//���ұ߽��һЩ 
	while(r-l>eps)
	{
		lm=l+(r-l)/3, rm=r-(r-l)/3;
		if(Calc(lm)>Calc(rm)) l=lm;
		else r=rm;
	}
	printf("%.3lf",Calc(l));

	return 0;
}
