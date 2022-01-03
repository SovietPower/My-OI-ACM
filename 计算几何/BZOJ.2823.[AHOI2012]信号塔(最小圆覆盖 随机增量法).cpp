/*
16952kb	780ms
һ�������**���������**��������Կ�[����](https://www.luogu.org/blog/boshi/solution-p1742)��ֻ��һ�´������̡�
һ������**���һ����$p$���ڵ㼯$S$����С����Բ�ڣ���ô��һ����$S\bigcup p$����С����Բ�ϡ�**
���Լ�����������ǰ$i-1$�������С����Բ����ôֻ��Ҫ�ж�$i$�ڲ������ڣ��Ϳ���ȷ��$i$�Ƿ��ڵ�ǰ��С����Բ�ϡ�
**�㷨���̣�**
1. ��ǰ$i-1$�������С����Բ��$C$���жϵ�$i$�����Ƿ���$C$�ڡ�����ǣ���$i$�������С����ԲҲ��$C$���������$2$��
2. ȷ��$p_i$Ϊ��С����Բ�ϵ�һ���㡣ö�ٵ�$j$���ж�$j$�Ƿ��ڵ�ǰ��С����Բ�ڡ�����ǣ�����������ȷ��$p_j$Ҳ����С����Բ�ϵ�һ���㣬Բ��Ϊ�߶�$(p_i,p_j)$���е㣬�뾶Ϊ$\frac{dis(p_i,p_j)}{2}$������$3$��
3. ö�ٵ�$k$���ж�$k$�Ƿ��ڵ�ǰ��С����Բ�ڡ�����ǣ�����������ȷ����ǰ��С����ԲΪ$(p_i,p_j,p_k)$�����Բ��

**�㷨�ĸ��Ӷȷ�����**����������£�����Ϊֻ��Ҫȷ�������㣬$n$������ÿ������Բ�ϵĸ�����$\frac3n$��
��ô��һ��ѭ���ĸ��Ӷ�$T_1(n)=O(n)+\sum_{i=1}^nT_2(i)$���ڶ���ѭ�����Ӷ�$T_2(n)=O(n)+\sum_{i=1}^nT_3(i)$��������ѭ�����Ӷ�Ϊ$T_3(n)=O(n)$��
����һ�¾Ϳ��Եó��㷨�ľ�̯���Ӷ�Ϊ$O(n)$��
ע��Ҫ��֤���˳��������ġ�

**����ϸ�ڣ�**
�����������$(p_i,p_j,p_k)$����С����Բ��
������һ�����ʡ�����ֱƽ���ߣ��д��ߣ��ϵĵ㵽�߶����ߵ�ľ�����ͬ����ô��������߶εĴ�ֱƽ���ߣ������������ˡ�
��ֱƽ���ߵ��󷨾�������һ���е㣨������ӳ���$2$����Ȼ�������ߣ�����һ������֮���������ת$90^{\circ}$����
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e6+5;

char IN[MAXIN],*SS=IN,*TT=IN;
struct Vec
{
	double x,y;
	Vec(double x=0,double y=0):x(x),y(y) {}
	Vec operator +(const Vec &a)const {return Vec(x+a.x, y+a.y);}
	Vec operator -(const Vec &a)const {return Vec(x-a.x, y-a.y);}
	Vec operator *(const double a)const {return Vec(x*a, y*a);}
	double operator *(const Vec &a)const {return x*a.y-y*a.x;}
	Vec Rotate_90()const {return Vec(y,-x);}
	double len()const {return sqrt(x*x+y*y);}
	double len2()const {return x*x+y*y;}
}p[N];
typedef Vec Point;
struct Line
{
	Point p; Vec v;
	Line(Point p,Vec v):p(p),v(v) {}
	Line PerpendicularBisector()const//��ֱƽ����=-=
	{
		return Line((p+p+v)*0.5,v.Rotate_90());
	}
	Point Intersection(const Line &l)const
	{
		return p+v*((l.v*(p-l.p))/(v*l.v));
	}
};

inline double read()
{
	double x=0,y=0.1,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);x=x*10+c-48,c=gc());
	for(c=='.'&&(c=gc());isdigit(c);x+=y*(c-48),y*=0.1,c=gc());
	return x*f;
}
Point CalcCircle(const Point &a,const Point &b,const Point &c)
{
//	Line A=Line(a,b-a).PerpendicularBisector(),B=Line(a,c-a).PerpendicularBisector();
	Line A=Line((a+b)*0.5,(b-a).Rotate_90()),B=Line((a+c)*0.5,(c-a).Rotate_90());
	return A.Intersection(B);
}
void Solve(const int n)
{
	srand(330), std::random_shuffle(p+1,p+1+n);//��˵���srand���������= = 
	Point O=p[1]; double R=0;
	for(int i=2; i<=n; ++i)
		if((p[i]-O).len2()>R)
		{
			O=p[i], R=0;
			for(int j=1; j<i; ++j)
				if((p[j]-O).len2()>R)
				{
					O=(p[i]+p[j])*0.5, R=(p[i]-O).len2();
					for(int k=1; k<j; ++k)
						if((p[k]-O).len2()>R)
							O=CalcCircle(p[i],p[j],p[k]), R=(p[k]-O).len2();
				}
		}
	printf("%.2f %.2f %.2f\n",O.x,O.y,sqrt(R));
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) p[i].x=read(),p[i].y=read();
//	for(int i=1; i<=n; ++i) p[i]=(Point){read(),read()};//�������캯��֮������ô�ã�ò�ơ���= = ��ͬ�����������ͬ����
	Solve(n);

	return 0;
}
