/*
3072kb	264ms
将原坐标系每个点的坐标$(x,y)$变为$(x+y,x-y)$，则原坐标系中的曼哈顿距离等于新坐标系中的切比雪夫距离。
反过来，将原坐标系每个点的坐标$(x,y)$变为$(\frac{x+y}{2},\frac{x-y}{2})$，则原坐标系中的切比雪夫距离等于新坐标系中的曼哈顿距离。
随便写两个点就可以验证这是对的。

将题目中每个点的坐标$(x,y)$改为$(\frac{x+y}{2},\frac{x-y}{2})$，然后记$dis(a,b)=\Delta X+\Delta Y$表示两个点$a,b$间的曼哈顿距离。
枚举每一个点$x$，则到$x$的距离之和为$Sum=\sum_{i=1}^ndis(i,x)$。
把$dis(i,x)$拆开，即$$\begin{aligned}Sum&=\sum_{i=1}^n\Delta X(i,x)+\Delta Y(i,x)\\&=\Delta X(1,x)+\Delta X(2,x)+...+\Delta Y(1,x)+\Delta Y(2,x)...\end{aligned}$$
把每个点按$x$或$y$排序，枚举点时就可以$O(1)$计算$\Delta X$或$\Delta Y$的变化量了。
当然没必要先把坐标$x,y$除以$2$。最后把答案除以$2$即可。
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
