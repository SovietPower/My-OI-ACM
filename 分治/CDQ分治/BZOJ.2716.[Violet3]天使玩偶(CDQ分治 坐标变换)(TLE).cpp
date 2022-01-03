/*
懒得改了 看另一个吧。。
考虑对于两个点a,b，距离为|x[a]-x[b]|+|y[a]-y[b]|，如果a在b的右上，那我们可以把绝对值去掉，即x[a]+y[a]-(x[b]+y[b])。
即我们要求满足x[b]<=x[a]且y[b]<=y[a]的最大的x[b]+y[b]，用CDQ分治+树状数组解决。
那如果a不在b的右上呢？可以通过坐标变换解决(因为要求的只是相对距离)。
坐标变换可以用Xmax或Ymax减去xi或yi。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define lb(x) (x)&-(x)
const int N=3e5+5;

int n,m,qcnt,acnt,Ans[N];
struct Operation
{
	int type,x,y;
	Operation() {};
	Operation(int t,int _x,int _y): type(t),x(_x),y(_y) {};
	bool operator <(const Operation &a)const{
		return x==a.x?type<a.type:x<a.x;
	}
}q[N<<1],tmp[N<<1],A[N<<1];

namespace BIT
{
	int Max,t[1000005];
	void Update(int p,int v){
		while(p<=Max) t[p]=std::max(t[p],v),p+=lb(p);
	}
	int Query(int p){
		int res=0;
		while(p) res=std::max(t[p],res),p-=lb(p);
		return res;
	}
	void Clear(int p){
		while(p<=Max)//被这个Max坑了半晚上。。
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
{//同理可以只在后半部分修改时更新前半部分 这个tm是有序的 结束后要按x归并使x有序 
	if(l<r)
	{
		int m=l+r>>1; CDQ(l,m), CDQ(m+1,r);
		int p1=l,p2=m+1,t=0,val;
		while(p1<=m&&p2<=r)
		{
			if(q[p1]<q[p2])
			{
				if(!q[p1].type) BIT::Update(q[p1].y,q[p1].x+q[p1].y);
				tmp[t++]=q[p1++];
			}
			else
			{
				if(q[p2].type)
					if(val=BIT::Query(q[p2].y))//只在有点时更新答案! 否则答案会是它的x+y 
						Ans[q[p2].type]=std::min(Ans[q[p2].type],q[p2].x+q[p2].y-val);
				tmp[t++]=q[p2++];
			}
		}
		if(p1<=m)
		{
			for(int i=l; i<p1; ++i)
				if(!q[i].type) BIT::Clear(q[i].y);
			while(p1<=m) tmp[t++]=q[p1++];
		}
		else
		{
			while(p2<=r)
			{
				if(q[p2].type)
					if(val=BIT::Query(q[p2].y))
						Ans[q[p2].type]=std::min(Ans[q[p2].type],q[p2].x+q[p2].y-val);
				tmp[t++]=q[p2++];
			}
			for(int i=l; i<=m; ++i)
				if(!q[i].type) BIT::Clear(q[i].y);
		}
		for(int i=0; i<t; ++i) q[l+i]=tmp[i];
	}
}

int main()
{
	n=read(),m=read();
	int Xmax=0,Ymax=0;
	for(int x,y,i=1; i<=n; ++i)//非负坐标...
		x=read()+1,y=read()+1,Xmax=std::max(Xmax,x),Ymax=std::max(Ymax,y),
		q[++qcnt]=Operation(0,x,y);
	for(int t,x,y,i=1; i<=m; ++i)
		t=read(),x=read()+1,y=read()+1,Xmax=std::max(Xmax,x),Ymax=std::max(Ymax,y),
		q[++qcnt]=Operation(t==1?0:++acnt,x,y);
	++Xmax,++Ymax,BIT::Max=Ymax;
	for(int i=1; i<=acnt; ++i) Ans[i]=Xmax+Ymax;
	for(int i=1; i<=qcnt; ++i) A[i]=q[i];

	CDQ(1,qcnt);

	for(int i=1; i<=qcnt; ++i) q[i]=A[i];
	for(int i=1; i<=qcnt; ++i) q[i].x=Xmax-q[i].x;
	CDQ(1,qcnt);

	for(int i=1; i<=qcnt; ++i) q[i]=A[i];
	for(int i=1; i<=qcnt; ++i) q[i].y=Ymax-q[i].y;
	CDQ(1,qcnt);
	
	for(int i=1; i<=qcnt; ++i) q[i]=A[i];
	for(int i=1; i<=qcnt; ++i) q[i].x=Xmax-q[i].x,q[i].y=Ymax-q[i].y;
	CDQ(1,qcnt);

	for(int i=1; i<=acnt; ++i) printf("%d\n",Ans[i]);

	return 0;
}
