//392K	1188MS
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define Rate (0.97)
//#define Rand() (1.0*((rand()<<1)-RAND_MAX)/RAND_MAX)
#define Rand() (1.0*rand()/RAND_MAX)

const int N=1005;

int n,X,Y;
double DIS,ans_dis[30];
struct Node{
	double x,y;
	Node() {}
	Node(double x,double y):x(x),y(y) {}
}p[N],ans[30];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline double Sqr(double x){
	return x*x;
}
inline double Dis(double x,double y,int i){
	return sqrt(Sqr(x-p[i].x)+Sqr(y-p[i].y));
}
double Calc(double x,double y)
{
	double res=1e9;//DIS;
	for(int i=1; i<=n; ++i)
		res=std::min(res,Dis(x,y,i));
	return res;
}
void Rand_Point(double &x,double &y,Node a,Node b){
	x=a.x+(b.x-a.x)*Rand(), y=a.y+(b.y-a.y)*Rand();
}
void Solve()
{
	DIS=sqrt(X*X+Y*Y);
	const int tot=15;
	ans[1]=Node(0,0), ans[2]=Node(X,Y), ans[3]=Node(X,0), ans[4]=Node(0,Y);//
	for(int i=5; i<=tot; ++i)
		Rand_Point(ans[i].x,ans[i].y,ans[1],ans[2]);
//		ans[i].x=Rand()*X,ans[i].y=Rand()*Y;
	for(int i=1; i<=tot; ++i) ans_dis[i]=Calc(ans[i].x,ans[i].y);
	double T=std::min(X,Y),xx,yy,dis;//this...
	while(T>0.01)
	{
		for(int i=1; i<=tot; ++i)
			for(int j=1; j<=20; ++j)
			{
				Rand_Point(xx,yy,Node(std::max(0.0,ans[i].x-T),std::max(0.0,ans[i].y-T)),Node(std::min(1.0*X,ans[i].x+T),std::min(1.0*Y,ans[i].y+T)));
				dis=Calc(xx,yy);
				if(dis>ans_dis[i]) ans[i]=Node(xx,yy),ans_dis[i]=dis;
			}
		T*=Rate;
	}
	int res=1;
	for(int i=2; i<=tot; ++i)
		if(ans_dis[i]>ans_dis[res]) res=i;
	printf("The safest point is (%.1f, %.1f).\n",ans[res].x,ans[res].y);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
#endif

	srand(20180428);
	int T=read();
	while(T--)
	{
		X=read(),Y=read(),n=read();
		for(int i=1; i<=n; ++i) p[i].x=read(),p[i].y=read();
		Solve();
	}
	return 0;
}
