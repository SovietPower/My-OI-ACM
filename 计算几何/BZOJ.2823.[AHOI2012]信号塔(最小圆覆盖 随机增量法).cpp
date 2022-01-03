/*
16952kb	780ms
一个经典的**随机增量法**，具体可以看[这里](https://www.luogu.org/blog/boshi/solution-p1742)，只记一下大体流程。
一个定理：**如果一个点$p$不在点集$S$的最小覆盖圆内，那么它一定在$S\bigcup p$的最小覆盖圆上。**
所以假设我们有了前$i-1$个点的最小覆盖圆，那么只需要判断$i$在不在其内，就可以确定$i$是否在当前最小覆盖圆上。
**算法流程：**
1. 设前$i-1$个点的最小覆盖圆是$C$，判断第$i$个点是否在$C$内。如果是，则$i$个点的最小覆盖圆也是$C$；否则进行$2$。
2. 确定$p_i$为最小覆盖圆上的一个点。枚举点$j$，判断$j$是否在当前最小覆盖圆内。如果是，跳过；否则确定$p_j$也是最小覆盖圆上的一个点，圆心为线段$(p_i,p_j)$的中点，半径为$\frac{dis(p_i,p_j)}{2}$，进行$3$。
3. 枚举点$k$，判断$k$是否在当前最小覆盖圆内。如果是，跳过；否则确定当前最小覆盖圆为$(p_i,p_j,p_k)$的外接圆。

**算法的复杂度分析：**（随机数据下，）因为只需要确定三个点，$n$个点中每个点在圆上的概率是$\frac3n$。
那么第一层循环的复杂度$T_1(n)=O(n)+\sum_{i=1}^nT_2(i)$，第二层循环复杂度$T_2(n)=O(n)+\sum_{i=1}^nT_3(i)$，第三次循环复杂度为$T_3(n)=O(n)$。
化简一下就可以得出算法的均摊复杂度为$O(n)$。
注意要保证点的顺序是随机的。

**具体细节：**
如何求三个点$(p_i,p_j,p_k)$的最小覆盖圆：
就是用一个性质。。垂直平分线（中垂线）上的点到线段两边点的距离相同。那么求出两条线段的垂直平分线，求个交点就行了。
垂直平分线的求法就是先求一个中点（坐标相加除以$2$），然后做垂线（将另一个两点之间的向量旋转$90^{\circ}$）。
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
	Line PerpendicularBisector()const//垂直平分线=-=
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
	srand(330), std::random_shuffle(p+1,p+1+n);//话说这个srand不够随机啊= = 
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
//	for(int i=1; i<=n; ++i) p[i]=(Point){read(),read()};//声明构造函数之后再这么用，貌似。。= = 不同编译器结果不同。。
	Solve(n);

	return 0;
}
