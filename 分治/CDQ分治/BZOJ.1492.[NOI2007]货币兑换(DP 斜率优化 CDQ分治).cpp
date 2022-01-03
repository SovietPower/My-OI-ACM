/*
12648kb	792ms
如果某天能够赚钱，那么一定会在这天把手上的金券全卖掉。同样如果某天要买，一定会把所有钱花光。
那么令$f_i$表示到第$i$天所拥有的最多钱数（此时手上没有任何金券），可以选择什么都不干，$f_i=f_{i-1}$；也可以从之前的某一天$j$花$f_j$的钱买金券，在第$i$天全卖掉。用第$j$天的信息算一下买了多少$A,B$，就可以得到第$i$天卖了多少钱。
所以有$f_i=\max\{f_{i-1},\ A_i\frac{f_jk_j}{A_jk_j+B_j}+B_i\frac{f_j}{A_jk_j+B_j}\}$。
把后面那部分写成直线的形式：$\frac{f_i}{B_i}-\frac{A_i}{B_i}*\frac{f_jk_j}{A_jk_j+B_j}=\frac{f_j}{A_jk_j+B_j}$，令$x_j=\frac{A_i}{B_i}*\frac{f_jk_j}{A_jk_j+B_j},\ y_j=\frac{A_i}{B_i}*\frac{f_j}{A_jk_j+B_j}$，$\frac{f_i}{B_i}-\frac{A_i}{B_i}x_j=y_j$。要求用$k=-\frac{A_i}{B_i}$的直线去切$(x_j,y_j)$使得截距最大，也就是维护上凸壳。
但$x$即每个决策点不是单调的，就需要平衡树/CDQ分治去维护凸包。
**CDQ分治：**
先将所有点按斜率$k$排序。
先处理完左区间询问，然后将左区间按横坐标$x$归并排好序。这样处理右区间询问的时候（现在只考虑当前左区间对整个右区间询问的影响，也就是要对左区间维护上凸壳），左区间的$x$有序就可以直接用单调栈把上凸壳维护出来了。
而右区间已经按斜率$k$排好序了，所以可以$O(n)$在上凸壳中得到最优解（实现当前整个左区间对右区间的转移）。
当递归到$l=r$，就说明已经处理完该点$l$之前的点对$l$的影响了，就可以直接得到$f_l$的值（顺便要和$f_{l-1}$取$\max$）并更新$l$这个决策点的信息了。
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define eps 1e-9
typedef long long LL;
const int N=1e5+5;
const double INF=1e17;

double f[N],read();
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int id;
	double A,B,k,Rate,x,y;
	inline void Init(int i)
	{
		id=i,A=read(),B=read(),k=-A/B,Rate=read();
	}
	bool operator <(const Node &x)const
	{
		return k<x.k;
	}
}q[N];

inline double read()
{
	double x=0,y=0.1;register char c=gc();
	for(;!isdigit(c)&&c!='.';c=gc());
	for(;isdigit(c);x=x*10+c-'0',c=gc());
	for(c=='.'&&(c=gc());isdigit(c);x+=(c-'0')*y,y*=0.1,c=gc());
	return x;
}
inline double GetK(int i,int j)
{
	return fabs(q[i].x-q[j].x)<=eps?(q[i].y<q[j].y?-INF:INF):(q[i].y-q[j].y)/(q[i].x-q[j].x);
//	return fabs(q[i].x-q[j].x)<=eps?INF:(q[i].y-q[j].y)/(q[i].x-q[j].x);
}
void CDQ(int l,int r)
{
	static int sk[N];
	static Node tmp[N];
	if(l==r)
	{
		f[l]=std::max(f[l],f[l-1]);
		q[l].y=f[l]/(q[l].A*q[l].Rate+q[l].B), q[l].x=q[l].y*q[l].Rate;
		return;
	}
	int mid=l+r>>1,p1=l,p2=mid+1;
	for(int i=l; i<=r; ++i)//将前mid个询问放在左边 后mid个放在右边 
		q[i].id<=mid?tmp[p1++]=q[i]:tmp[p2++]=q[i];
	for(int i=l; i<=r; ++i) q[i]=tmp[i];
	CDQ(l,mid);

	int top=0;
	for(int i=l; i<=mid; ++i)
	{
		while(top>=2 && GetK(i,sk[top])>GetK(sk[top],sk[top-1])) --top;
		sk[++top]=i;
	}
	for(int i=mid+1; i<=r; ++i)
	{
		while(top>=2 && GetK(sk[top],sk[top-1])<q[i].k) --top;
		int j=sk[top];
		f[q[i].id]=std::max(f[q[i].id],q[i].A*q[j].x+q[i].B*q[j].y);
	}
	CDQ(mid+1,r);

	p1=l,p2=mid+1; int p=l;//处理完整个区间后按x排序 
	while(p1<=mid && p2<=r) q[p1].x<=q[p2].x?tmp[p++]=q[p1++]:tmp[p++]=q[p2++];
	while(p1<=mid) tmp[p++]=q[p1++];
	while(p2<=r) tmp[p++]=q[p2++];
	for(int i=l; i<=r; ++i) q[i]=tmp[i];
}

int main()
{
	int n=read(); f[0]=read();
	for(int i=1; i<=n; ++i) q[i].Init(i);
	std::sort(q+1,q+1+n), CDQ(1,n);
	printf("%.3lf\n",f[n]);

	return 0;
}
