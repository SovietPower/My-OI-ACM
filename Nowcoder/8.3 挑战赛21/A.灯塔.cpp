#include <cmath>
#include <cctype>
#include <cstdio>
#define gc() getchar()
const int N=1e6+5;
const double PI=acos(-1);

inline int read();
struct Point
{
   	double x,y;
   	inline void Init() {x=read(),y=read();}
   	bool operator ==(const Point &a)const{
		return x==a.x&&y==a.y;
	}
}p[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline bool Check1(Point a,Point b) {return a.x<b.x;}
inline bool Check2(Point a,Point b) {return a.y>b.y;}
inline bool Check3(Point a,Point b) {return a.y<b.y;}
inline bool Check4(Point a,Point b) {return a.x>b.x;}
inline Point Rotate(Point p) {
	return (Point){sin(PI/4.0)*p.x+sin(PI/4.0)*p.y, sin(PI/4.0)*p.x-sin(PI/4.0)*p.y};
}

int main () {
	for(int Case=read(); Case--; )
	{
		int n=read();
		for(int i=1; i<=n; ++i) p[i].Init();
		Point a,b,c,d;
		a=b=c=d=p[1];
		for(int i=2; i<=n; ++i)
		{
			if(Check1(p[i],a)) a=p[i];
			if(Check2(p[i],b)) b=p[i];
			if(Check3(p[i],c)) c=p[i];
			if(Check4(p[i],d)) d=p[i];
		}
		if(a==b||a==c||d==b||d==c) {puts("Yes"); continue;}
		for(int i=1; i<=n; ++i) p[i]=Rotate(p[i]);
		a=b=c=d=p[1];
		for(int i=2; i<=n; ++i)
		{
			if(Check1(p[i],a)) a=p[i];
			if(Check2(p[i],b)) b=p[i];
			if(Check3(p[i],c)) c=p[i];
			if(Check4(p[i],d)) d=p[i];
		}
		if(a==b||a==c||d==b||d==c) puts("Yes");
		else puts("No");
	}
	return 0;
}
