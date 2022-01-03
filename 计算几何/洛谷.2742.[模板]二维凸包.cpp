/*
22ms	1180KB
$Granham's\ Scan$��
1. ѡ�����е��к�������С�������ͬȡ��������С�ģ��ĵ�$x$�������е㰴��$x$�ļ���������
2. ��$x$�ŵ�ջ���һ�鵥��ջ��͹����
��������ƺ����Ȳ�̫�á�

��һ�������ǣ�
1. �����е㰴������Ϊ��һ�ؼ��֣�������Ϊ�ڶ��ؼ�������
2. ��$1$�ŵ�ŵ�ջ�����ջ��һ����͹�ǡ�
3. ����ԭ��ջ�е�Ԫ�أ�����ջ��һ����͹�ǡ�
���Ӷȶ���$O(n\log n)$��
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e4+6;

int sk[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Vec
{
	double x,y;
	Vec(double x=0,double y=0):x(x),y(y) {}
	Vec operator +(const Vec &a)const {return Vec(x+a.x, y+a.y);}
	Vec operator -(const Vec &a)const {return Vec(x-a.x, y-a.y);}
	Vec operator *(const double a)const {return Vec(x*a, y*a);}
	bool operator <(const Vec &a)const {return x<a.x||(x==a.x&&y<a.y);}
	double operator *(const Vec &a)const {return x*a.y-y*a.x;}
	double Length() {return sqrt(x*x+y*y);}
}p[N];
typedef Vec Point;

inline double read()
{
	double x=0,y=0.1,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);x=x*10+c-48,c=gc());
	for(c=='.'&&(c=gc());isdigit(c);x+=y*(c-48),y*=0.1,c=gc());
	return x*f;
}
double Convex(int n)
{
	std::sort(p+1,p+1+n);
	int top=1; sk[1]=1;
	for(int i=2; i<=n; ++i)
	{
		while(top>1 && (p[sk[top]]-p[sk[top-1]])*(p[i]-p[sk[top-1]])<=0) --top;
		sk[++top]=i;
	}
	int m=top;
	for(int i=n-1; i; --i)
	{
		while(top>m && (p[sk[top]]-p[sk[top-1]])*(p[i]-p[sk[top-1]])<=0) --top;
		sk[++top]=i;
	}
	double ans=0;
	for(int i=1; i<top; ++i) ans+=(p[sk[i+1]]-p[sk[i]]).Length();
	return ans;
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) p[i]=(Point){read(),read()};
	printf("%.2f\n",Convex(n));

	return 0;
}
