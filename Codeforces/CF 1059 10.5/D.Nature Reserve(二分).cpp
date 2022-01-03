/*
61ms	7700KB
二分半径r。我们发现半径确定后，圆心的纵坐标也确定（在y=r上）。
这样我们要求是否存在圆心在y=r上的覆盖所有点的圆。对每个点画一个半径为r的圆，它们需要在y=r这条直线上有交。
每个圆到y=r的两个交点可以用勾股定理算出来，可以转成区间是否有交的问题。求最左的右端点和最右的左端点就行了。
因为要与x轴相切，所以半径可能非常大，用勾股定理可以得到最大是5e13+。因为范围较大注意简化运算减少误差。
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 200000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e6+6;

int n,x[N],y[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
bool Check(double r)
{
	double L=-1e18,R=1e18,tmp;
	for(int i=1; i<=n; ++i)
	{
		if(r+r<y[i]) return 0;
		tmp=sqrt(1.0*(r+r-y[i])*y[i]);
		L=std::max(L,-tmp+x[i]), R=std::min(R,tmp+x[i]);
		if(L>R) return 0;
	}
	return 1;
}

int main()
{
	n=read(); int cnt=0;
	for(int i=1; i<=n; ++i) x[i]=read(),y[i]=read(),cnt+=(y[i]<0);
	if(cnt)
	{
		if(cnt!=n) return puts("-1"),0;
		for(int i=1; i<=n; ++i) y[i]=-y[i];
	}
	double l=0,r=1e14,mid;
	for(int T=80; T--; )
	{
//		if(l>1 && l+1>r) mid=sqrt(l*r);//几何平均数该这么写么。。
//		else mid=(l+r)*0.5;
		if(Check(mid=(l+r)*0.5)) r=mid;
		else l=mid;
	}
	printf("%.7lf\n",l);

	return 0;
}
