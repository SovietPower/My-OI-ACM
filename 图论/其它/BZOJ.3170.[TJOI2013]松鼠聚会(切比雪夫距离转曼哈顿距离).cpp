/*
3072kb	264ms
��ԭ����ϵÿ���������$(x,y)$��Ϊ$(x+y,x-y)$����ԭ����ϵ�е������پ������������ϵ�е��б�ѩ����롣
����������ԭ����ϵÿ���������$(x,y)$��Ϊ$(\frac{x+y}{2},\frac{x-y}{2})$����ԭ����ϵ�е��б�ѩ��������������ϵ�е������پ��롣
���д������Ϳ�����֤���ǶԵġ�

����Ŀ��ÿ���������$(x,y)$��Ϊ$(\frac{x+y}{2},\frac{x-y}{2})$��Ȼ���$dis(a,b)=\Delta X+\Delta Y$��ʾ������$a,b$��������پ��롣
ö��ÿһ����$x$����$x$�ľ���֮��Ϊ$Sum=\sum_{i=1}^ndis(i,x)$��
��$dis(i,x)$�𿪣���$$\begin{aligned}Sum&=\sum_{i=1}^n\Delta X(i,x)+\Delta Y(i,x)\\&=\Delta X(1,x)+\Delta X(2,x)+...+\Delta Y(1,x)+\Delta Y(2,x)...\end{aligned}$$
��ÿ���㰴$x$��$y$����ö�ٵ�ʱ�Ϳ���$O(1)$����$\Delta X$��$\Delta Y$�ı仯���ˡ�
��Ȼû��Ҫ�Ȱ�����$x,y$����$2$�����Ѵ𰸳���$2$���ɡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

LL Ans[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Point
{
	int x,y,id;
	Point(int tid=0,int ty=0,int tx=0) {id=tid, x=tx+ty, y=tx-ty;}
}p[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
bool cmpx(Point a,Point b)
{
	return a.x<b.x;
}
bool cmpy(Point a,Point b)
{
	return a.y<b.y;
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) p[i]=Point(i,read(),read());

	std::sort(p+1,p+1+n,cmpx);
	LL sum=-1ll*(n-1)*p[1].x;
	for(int i=2; i<=n; ++i) sum+=p[i].x;
	for(int i=1; i<=n; ++i)
		Ans[p[i].id]+=sum, sum+=(2ll*i-n)*(p[i+1].x-p[i].x);//i*dx-(n-i)*dx

	std::sort(p+1,p+1+n,cmpy);
	sum=-1ll*(n-1)*p[1].y;
	for(int i=2; i<=n; ++i) sum+=p[i].y;
	for(int i=1; i<=n; ++i)
		Ans[p[i].id]+=sum, sum+=(2ll*i-n)*(p[i+1].y-p[i].y);

	LL ans=1e18;
	for(int i=1; i<=n; ++i) ans=std::min(ans,Ans[i]);
	printf("%lld\n",ans>>1);

	return 0;
}
