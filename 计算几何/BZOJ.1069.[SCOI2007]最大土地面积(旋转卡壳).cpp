/*
884kb	120ms
���ı�����������ö��һ���Խ��ߣ���Խ����������������������ɡ�
������$n^3$�ģ����׷��̶ֹ��Խ���һ���˵㣬��һ���˵��ƶ�ʱ������Զ����ƶ�Ҳ�ǵ����ġ���������ת�����Ż�һ�¾���$O(n^2)$����
*/
#include <cstdio>
#include <algorithm>
typedef long long LL;
const int N=2005;

struct Vec
{
	double x,y;
	Vec(double x=0,double y=0):x(x),y(y) {}
	Vec operator +(const Vec &a)const {return Vec(x+a.x, y+a.y);}
	Vec operator -(const Vec &a)const {return Vec(x-a.x, y-a.y);}
	double operator *(const Vec &a)const {return x*a.y-y*a.x;}
	bool operator <(const Vec &a)const {return x<a.x||(x==a.x&&y<a.y);}
}p[N],sk[N];


int main()
{
	int n; scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%lf%lf",&p[i].x,&p[i].y);
	std::sort(p+1,p+1+n);
	int top=1; sk[1]=p[1];
	for(int i=2; i<=n; ++i)
	{
		while(top>1 && (sk[top]-sk[top-1])*(p[i]-sk[top-1])<=0) --top;
		sk[++top]=p[i];
	}
	int k=top;
	for(int i=n-1; i>1; --i)
	{
		while(top>k && (sk[top]-sk[top-1])*(p[i]-sk[top-1])<=0) --top;
		sk[++top]=p[i];
	}
	double ans=0; sk[top+1]=sk[1];
	#define Inc(x) (x+1>top?1:x+1)
	for(int i=1; i+2<=top; ++i)
	{
		int x=i+1,y=i+3>top?1:i+3;
		for(int j=i+2; j<=top; ++j)
		{
			while((sk[x+1]-sk[i])*(sk[j]-sk[i])>(sk[x]-sk[i])*(sk[j]-sk[i])) x=Inc(x);
			while((sk[j]-sk[i])*(sk[y+1]-sk[i])>(sk[j]-sk[i])*(sk[y]-sk[i])) y=Inc(y);
			ans=std::max(ans,(sk[x]-sk[i])*(sk[j]-sk[i])+(sk[j]-sk[i])*(sk[y]-sk[i]));
		}
	}
	printf("%.3f\n",ans*0.5);

	return 0;
}
