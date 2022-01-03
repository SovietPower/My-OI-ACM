//392K	500MS
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define Rate (0.9)
#define Rand() (1.0*((rand()<<1)-RAND_MAX)/RAND_MAX)
const int N=1005;

int n,X,Y;
double DIS,ans_dis[20];
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
	double res=DIS;
	for(int i=1; i<=n; ++i)
		res=std::min(res,Dis(x,y,i));
	return res;
}
void Print(){
	for(int i=1; i<=15; ++i) printf("%d:%.5lf %.5lf %.5lf   %d %d\n",i,ans[i].x,ans[i].y,ans_dis[i],X,Y);
}
void Solve()
{
	DIS=sqrt(X*X+Y*Y);
	const int tot=15;
	for(int i=1; i<=tot; ++i)
		ans[i].x=1.0*rand()/RAND_MAX*X,ans[i].y=1.0*rand()/RAND_MAX*Y,ans_dis[i]=Calc(ans[i].x,ans[i].y);
	double T=DIS,xx,yy,dis;//this...
	while(T>0.01)
	{
		for(int i=1; i<=tot; ++i)
			for(int j=1; j<=30; ++j)
			{
				xx=ans[i].x+T*Rand(), yy=ans[i].y+T*Rand();
				if(xx<0||xx>X||yy<0||yy>Y) continue;//!
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