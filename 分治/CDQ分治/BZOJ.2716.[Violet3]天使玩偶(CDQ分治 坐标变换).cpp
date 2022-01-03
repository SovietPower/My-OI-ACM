/*
43796kb	32744ms
$Description$
二维平面中初始有$n$个点，$m$次操作：1. 在某个位置新建一个点；2. 询问当前所有点中离某位置最近的点有多远。
$n,m\leq 3\times 10^5$。
$Solution$
考虑对于两个点a,b，距离为|x[a]-x[b]|+|y[a]-y[b]|，如果a在b的右上，那我们可以把绝对值去掉，即x[a]+y[a]-(x[b]+y[b])。
即我们要求满足x[b]<=x[a]且y[b]<=y[a]的最大的x[b]+y[b]，用CDQ分治+树状数组解决。
那如果a不在b的右上呢？可以通过坐标变换解决(因为要求的只是相对距离)。
坐标变换可以用Xmax或Ymax减去xi或yi。
如果还用之前的方法，每次变换坐标前都要把操作序列变为初始序列(时间有序)，但是这样很慢。。
不如在每次分治前按x sort一遍，分治中再以tm为关键字排序(同一区间内要时间有序) 
优化: 遇到修改时才修改。所以先排好序再扫一遍更新答案 
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define lb(x) (x)&-(x)
const int N=5e5+5,MAXIN=2e6;

int n,m,qcnt,acnt,Ans[N],A[N<<1];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Operation
{
	int type,x,y,tm;
	Operation() {}
	Operation(int t,int _x,int _y,int _tm): type(t),x(_x),y(_y),tm(_tm) {}
	bool operator <(const Operation &a)const{
		return x==a.x?tm<a.tm:x<a.x;
	}
}q[N<<1],tmp[N<<1];

namespace BIT
{
	int Max,t[1000005];
	void Update(int p,int v){
		while(p<=Max) t[p]=std::max(t[p],v),p+=lb(p);
	}
	int Query(int p){
		int res=0;
		while(p) res=std::max(t[p],res),p^=lb(p);//^代替- 
		return res;
	}
	void Clear(int p){
		while(p<=Max)//被这个Max坑半晚上。。
			if(t[p]) t[p]=0,p+=lb(p);
			else break;
	}
}
inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void CDQ(int l,int r)
{
	if(l<r)
	{
		int m=l+r>>1; 
		int p1=l,p2=m+1,t=0,val;
		for(int i=l; i<=r; ++i)
			if(q[i].tm<=m) tmp[p1++]=q[i];
			else tmp[p2++]=q[i];
		for(int i=l; i<=r; ++i) q[i]=tmp[i];//先排好 这样之后就可以只在查询时更新了(不需要排序了) 
		p1=l, p2=m+1;
		for(; p2<=r; ++p2)
			if(q[p2].type)
			{
				for(; p1<=m&&q[p1].x<=q[p2].x; ++p1)
					if(!q[p1].type) A[++t]=q[p1].y,BIT::Update(q[p1].y,q[p1].x+q[p1].y);
				if(val=BIT::Query(q[p2].y))
					Ans[q[p2].type]=std::min(Ans[q[p2].type],q[p2].x+q[p2].y-val);//只在有点时更新答案! 否则答案会是它的x+y 
			}
//		for(int i=l; i<p1; ++i)
//			if(!q[i].type) BIT::Clear(q[i].y);
		for(int i=1; i<=t; ++i) BIT::Clear(A[i]);
		CDQ(l,m), CDQ(m+1,r);
	}
}

int main()
{
	n=read(),m=read();
	int Xmax=0,Ymax=0;
	for(int x,y,i=1; i<=n; ++i)//非负坐标...
		x=read()+1,y=read()+1,Xmax=std::max(Xmax,x),Ymax=std::max(Ymax,y),
		q[++qcnt]=Operation(0,x,y,qcnt);
	for(int t,x,y,i=1; i<=m; ++i)
		t=read(),x=read()+1,y=read()+1,Xmax=std::max(Xmax,x),Ymax=std::max(Ymax,y),
		q[++qcnt]=Operation(t==1?0:++acnt,x,y,qcnt);
	++Xmax,++Ymax,BIT::Max=Ymax;
	for(int i=1; i<=acnt; ++i) Ans[i]=Xmax+Ymax;

	std::sort(q+1,q+1+qcnt), CDQ(1,qcnt);

	for(int i=1; i<=qcnt; ++i) q[i].x=Xmax-q[i].x;
	std::sort(q+1,q+1+qcnt), CDQ(1,qcnt);

	for(int i=1; i<=qcnt; ++i) q[i].y=Ymax-q[i].y;
	std::sort(q+1,q+1+qcnt), CDQ(1,qcnt);

	for(int i=1; i<=qcnt; ++i) q[i].x=Xmax-q[i].x;
	std::sort(q+1,q+1+qcnt), CDQ(1,qcnt);

	for(int i=1; i<=acnt; ++i) printf("%d\n",Ans[i]);

	return 0;
}
