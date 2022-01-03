/*
119964kb	4380ms
矩形查询可以拆成四个点的前缀和查询(树套树显然 但是空间不够) 
每个操作表示为(t,x,y)，t默认有序，对x分治，y用树状数组维护 
初始赋值需要靠修改操作实现。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define lb(x) (x)&-(x)
const int N=5e5+5;

int n,m,Ans[N];
struct Operation
{
	int id,x,y,val;//id=0:Modify val=1/-1
	Operation() {;}
	Operation(int i,int X,int Y,int v): id(i),x(X),y(Y),val(v) {};
	bool operator <(const Operation &a)const{
		return x==a.x?id<a.id:x<a.x;
	}
}q[N*5],tmp[N*5];

namespace BIT
{
	int Max,t[10000005];
	void Add(int p,int v){
		while(p<=Max) t[p]+=v,p+=lb(p);
	}
	int Query(int p){
		int res=0;
		while(p) res+=t[p],p-=lb(p);
		return res;
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
		int m=l+r>>1; CDQ(l,m), CDQ(m+1,r);
		int p1=l,p2=m+1,t=0;
		while(p1<=m&&p2<=r)
		{
			if(q[p1]<q[p2])
			{
				if(!q[p1].id) BIT::Add(q[p1].y,1);
				tmp[t++]=q[p1++];
			}
			else
			{
				if(q[p2].id) Ans[q[p2].id]+=q[p2].val*BIT::Query(q[p2].y);
				tmp[t++]=q[p2++];
			}
		}
		if(p1<=m)
		{//特判下少计算些 
			for(int i=l; i<p1; ++i)
				if(!q[i].id) BIT::Add(q[i].y,-1);
			while(p1<=m) tmp[t++]=q[p1++];
		}
		else
		{
			while(p2<=r)
			{
				if(q[p2].id) Ans[q[p2].id]+=q[p2].val*BIT::Query(q[p2].y);
				tmp[t++]=q[p2++];
			}
			for(int i=l; i<=m; ++i)
				if(!q[i].id) BIT::Add(q[i].y,-1);
		}
		for(int i=0; i<t; ++i) q[l+i]=tmp[i];
//		for(int i=l; i<=r; ++i) q[i]=tmp[i];//这样竟然会慢 玄学 
	}
}

int main()
{
	n=read(),m=read();
	int qcnt=0,mx=0;
	for(int x,y,i=1; i<=n; ++i)
		x=read()+1,y=read()+1, mx=std::max(mx,y), q[++qcnt]=Operation(0,x,y,0);//将坐标改为[1,1e7+7] 
	for(int a,b,c,d,i=1; i<=m; ++i)
	{
		a=read()+1,b=read()+1,c=read()+1,d=read()+1;
		mx=std::max(mx,std::max(b,d));//当然要和查询区域取max。。不然边上的怎么更新呢 
		q[++qcnt]=Operation(i,a-1,d,-1), q[++qcnt]=Operation(i,a-1,b-1,1);
		q[++qcnt]=Operation(i,c,b-1,-1), q[++qcnt]=Operation(i,c,d,1);
	}
	BIT::Max=mx;
	CDQ(1,qcnt);
	for(int i=1; i<=m; ++i) printf("%d\n",Ans[i]);

	return 0;
}
