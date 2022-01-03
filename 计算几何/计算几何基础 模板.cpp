/*
互相垂直的两向量点积为0。
叉积具有分配率。
A叉B的结果：<0，B在A的顺时针方向；>0，B在A的逆时针方向；=0，共线。
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

const double eps=1e-10;

inline int dcmp(double x) {return fabs(x)<eps?0:x<0?-1:1;}

struct Vec
{
	double x,y;
	Vec(double x=0,double y=0):x(x),y(y) {}
	Vec operator +(const Vec &a)const {return Vec(x+a.x, y+a.y);}
	Vec operator -(const Vec &a)const {return Vec(x-a.x, y-a.y);}
	Vec operator *(const double p)const {return Vec(x*p, y*p);}

	double operator *(const Vec &a)const {return x*a.y-y*a.x;}//cross product
	bool operator <(const Vec &a)const {return x<a.x||(x==a.x&&y<a.y);}
	bool operator ==(const Vec &a)const {return !dcmp(x-a.x)&&!dcmp(y-a.y);}

	double Norm() {return x*x+y*y;}//范数 
	double Length() {return sqrt(x*x+y*y);}//模长 
	double Dot(Vec a) {return x*a.x+y*a.y;}//dot product
	double Angle(Vec a) {return acos(Dot(a)/Length()/a.Length());}//两向量夹角 
	Vec Normal() {double t=Length(); return Vec(-y/t,x/t);}//单位法向量 
	Vec Rotate(double rad) {return Vec(x*cos(rad)-y*sin(rad),x*sin(rad)+y*cos(rad));}//顺时针旋转rad度 
};
typedef Vec Point;

struct Line
{
	Point a; Vec v;
	Line(Point a,Vec v):a(a),v(v) {}

	bool OnLine(const Point &p) {return !dcmp((a-p)*v);}//!dcmp((a-p)*(b-p))
	bool OnSegment(const Point &p) {return !dcmp((a-p)*v)&&dcmp((a-p).Dot(a+v-p))<=0;}//PA*PB<=0
	int Relation(const Line &l)//直线之间的关系 0:平行 1:相交 2:重合(无数个交点) 
	{
		return dcmp(v*l.v)?1:dcmp(v*(a-l.a))?0:2;
	}
	Point Intersection(const Line &l)//直线交点 
	{
		return a+v*((l.v*(a-l.a))/(v*l.v));//注意方向（叉积的正负）
	}
};

inline bool cmp(const Point &a,const Point &b) {return a.x==b.x?a.y<b.y:a.x<b.x;}

struct Polygon
{
	int sk[N];
	std::vector<Point> ps;

	bool Include(const Point &p)//点在多边形内 
	{
		int cnt=0;
		for(int i=0,lim=ps.size(); i<lim; ++i)
		{
			const Point a=ps[i],b=ps[i+1==lim?0:i+1];
			if(Line(a,b-a).OnSegment(p)) return 1;
			double d1=a.y-p.y,d2=b.y-p.y,tmp=(a-p)*(b-p);
			if((tmp<0&&d1<0&&d2>=0)||(tmp>0&&d1>=0&&d2<0)) ++cnt;
		}
		return cnt&1;
	}
	double Area()//多边形有向面积（逆时针为正，顺时针为负） 
	{
		double res=0;
		for(int i=0,lim=ps.size(); i<lim; ++i)
			res+=ps[i]*ps[i+1==lim?0:i+1];
		return res*0.5;
	}
	int Convex()//求凸包 存在sk[]里 
	{
		std::sort(ps.begin(),ps.end(),cmp);
		int top=1,n=ps.size(); sk[1]=0;
		for(int i=1; i<n; ++i)
		{
			while(top>=2 && (ps[sk[top]]-ps[sk[top-1]])*(ps[i]-ps[sk[top-1]])<=0) --top;
			sk[++top]=i;
		}
		int k=top;
		for(int i=n-2; ~i; --i)
		{
			while(top>k && (ps[sk[top]]-ps[sk[top-1]])*(ps[i]-ps[sk[top-1]])<=0) --top;
			sk[++top]=i;
		}
		return top;
	}
};

int main()
{
	return 0;
}
