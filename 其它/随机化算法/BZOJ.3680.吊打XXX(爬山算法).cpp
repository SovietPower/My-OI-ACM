/*
1016kb	2584ms
��ɽ�㷨��
�о����̺ʹ����е㡣����д�ˡ�
ÿ�ν���ǰ���(���е�)�Դ𰸵�Ӱ�����������𰸽���Ӱ��*T���ֵ��T�𽥼�С��ֱ��T�㹻С����𰸡�
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define D (0.97)//������Щ��
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
void Hill_Climb()
{
	double ansx=0,ansy=0;
	for(int i=1; i<=n; ++i)
		ansx+=p[i].x*p[i].w, ansy+=p[i].y*p[i].w;
	ansx/=n, ansy/=n;
	double T=1000,dis,xx,yy;
	while(T>1e-8)
	{
		xx=yy=0;
		for(int i=1; i<=n; ++i){
			dis=Dis(ansx,ansy,i);
			if(dis<1e-10) continue;//��0����
			xx+=(p[i].x-ansx)*p[i].w/dis,//ÿ����Դ𰸲���x(y)/r*w[i]��Ӱ�졣
			yy+=(p[i].y-ansy)*p[i].w/dis;
		}
		ansx+=xx*T, ansy+=yy*T;
		T*=D;
	}
	printf("%.3lf %.3lf",ansx,ansy);
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) p[i].x=read(),p[i].y=read(),p[i].w=read();
	Hill_Climb();
	return 0;
}
