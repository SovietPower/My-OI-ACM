/*
1028kb	6256ms
模拟退火(Simulated Annealing,SA)：
(1)初始化一个温度(充分大)、初始解状态S、每个T值的迭代次数。
(2)对i=1,...,L，做(3)至(7)步。
(3)产生新解S'。
(4)计算Δt=C(S')-C(S)，其中C(S)为评价函数。
(5)若Δt<0，则接受新解S'作为当前解；否则以exp(-Δt'/(kT))的概率接受S'作为当前解(k为玻尔兹曼常数，一般不管它？)
(6)如果满足终止条件，则输出当前解作为最优解，结束程序。
终止条件通常为连续若干个新解都没有被接受时终止算法。
(7)T逐渐减少，且T->0，转(2)。
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define D (0.96)//as big as possible?
#define Rand() ((rand()<<1)-RAND_MAX)
const int N=10005;

int n;
struct Node{
	int w;
	double x,y;
}p[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline double Sqr(double x){
	return x*x;
}
inline double Dis(double x,double y,int i){
	return sqrt(Sqr(x-p[i].x)+Sqr(y-p[i].y));
}
double Calc(double x,double y)
{
	double res=0;
	for(int i=1; i<=n; ++i)
		res+=Dis(x,y,i)*p[i].w;//i->dis*w[i] i对答案产生dis*w[i]的影响 
	return res;
}
void SA()
{
	double ansx=0,ansy=0,ans;
	for(int i=1; i<=n; ++i)
		ansx+=p[i].x*p[i].w, ansy+=p[i].y*p[i].w;
	ansx/=n, ansy/=n, ans=Calc(ansx,ansy);
	for(int Time=1; Time<=5; ++Time)//多次！需要记录ans及now。
	{//一次大概要1000次。
		double T=1000,nowx=ansx,nowy=ansy,now=Calc(ansx,ansy),res,xx,yy;
		while(T>1e-12)
		{
//			xx=ansx+T*(2*(rand()%Max)-Max),yy=ansy+T*(2*(rand()%Max)-Max);//x(y)+[-Max,Max-2] 不能只是用坐标的最大值。。delta应该够大些。
			xx=nowx+T*Rand(),yy=nowy+T*Rand();//x(y)+[-RAND_MAX,RAND_MAX-1]
			res=Calc(xx,yy);
			if(res<ans) ans=res, ansx=xx, ansy=yy;
			if(res<now)
				nowx=xx, nowy=yy, now=res;
			else if(exp((now-res)/T)*RAND_MAX>rand())//exp(-delta/T)>rand()/RAND_MAX
				nowx=xx, nowy=yy;
			T*=D;
		}
	}
	printf("%.3lf %.3lf",ansx,ansy);
}

int main()
{
	srand(20180501);
	n=read();
	for(int i=1; i<=n; ++i) p[i].x=read(),p[i].y=read(),p[i].w=read();
	SA();
	return 0;
}
