/*
1028kb	6256ms
ģ���˻�(Simulated Annealing,SA)��
(1)��ʼ��һ���¶�(��ִ�)����ʼ��״̬S��ÿ��Tֵ�ĵ���������
(2)��i=1,...,L����(3)��(7)����
(3)�����½�S'��
(4)���㦤t=C(S')-C(S)������C(S)Ϊ���ۺ�����
(5)����t<0��������½�S'��Ϊ��ǰ�⣻������exp(-��t'/(kT))�ĸ��ʽ���S'��Ϊ��ǰ��(kΪ��������������һ�㲻������)
(6)���������ֹ�������������ǰ����Ϊ���Ž⣬��������
��ֹ����ͨ��Ϊ�������ɸ��½ⶼû�б�����ʱ��ֹ�㷨��
(7)T�𽥼��٣���T->0��ת(2)��
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
		res+=Dis(x,y,i)*p[i].w;//i->dis*w[i] i�Դ𰸲���dis*w[i]��Ӱ�� 
	return res;
}
void SA()
{
	double ansx=0,ansy=0,ans;
	for(int i=1; i<=n; ++i)
		ansx+=p[i].x*p[i].w, ansy+=p[i].y*p[i].w;
	ansx/=n, ansy/=n, ans=Calc(ansx,ansy);
	for(int Time=1; Time<=5; ++Time)//��Σ���Ҫ��¼ans��now��
	{//һ�δ��Ҫ1000�Ρ�
		double T=1000,nowx=ansx,nowy=ansy,now=Calc(ansx,ansy),res,xx,yy;
		while(T>1e-12)
		{
//			xx=ansx+T*(2*(rand()%Max)-Max),yy=ansy+T*(2*(rand()%Max)-Max);//x(y)+[-Max,Max-2] ����ֻ������������ֵ����deltaӦ�ù���Щ��
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
