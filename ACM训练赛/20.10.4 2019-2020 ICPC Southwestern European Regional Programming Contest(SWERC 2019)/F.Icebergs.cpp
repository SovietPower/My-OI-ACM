/*
计算几何模板，求多边形面积。
*/
#include <bits/stdc++.h>
#define gc() getchar()
typedef long long LL;
const int N=1005;
const double eps=1e-10;

inline int dcmp(double x) {return fabs(x)<eps?0:x<0?-1:1;}

struct Vec
{
	LL x,y;
	Vec(LL x=0,LL y=0):x(x),y(y) {}
	Vec operator +(const Vec &a)const {return Vec(x+a.x,y+a.y);}
	Vec operator -(const Vec &a)const {return Vec(x-a.x,y-a.y);}
	Vec operator *(const double a)const {return Vec(x*a,y*a);}

	LL operator *(const Vec &a)const {return x*a.y-y*a.x;}
	bool operator <(const Vec &a)const {return x<a.x||(x==a.x&&y<a.y);}
	bool operator ==(const Vec &a)const {return !dcmp(x-a.x)&&!dcmp(y-a.y);}
};
typedef  Vec Point;
struct Polygon
{
	std::vector<Point> ps;
	LL Area()//多边形有向面积（逆时针为正，顺时针为负） 
	{
		LL res=0;
		for(int i=1,lim=ps.size(); i+1<lim; ++i)
			res+=(ps[i]-ps[0])*(ps[i+1]-ps[0]);
		return abs(res);
	}
}poly;

bool cmp(Point a,Point b)
{
	if(atan2(a.y,a.x)!=atan2(b.y,b.x))
		return atan2(a.y,a.x)<atan2(b.y,b.x);
	else return a.x<b.x;
}

inline int read()
{
	int now=0,f=1; char c=gc();
	for(; !isdigit(c); c=='-'&&(f=-1),c=gc());
	for(; isdigit(c); now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	LL res=0;
	for(int Ts=read(); Ts--; )
	{
		int n=read();
		poly.ps.clear();
		for(int i=1,x; i<=n; ++i) x=read(),poly.ps.push_back(Point(x,read()));
		res+=poly.Area();
	}
	printf("%lld\n",(res/2));

	return 0;
}
