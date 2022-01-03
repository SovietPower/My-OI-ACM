/*
119964kb	4380ms
���β�ѯ���Բ���ĸ����ǰ׺�Ͳ�ѯ(��������Ȼ ���ǿռ䲻��) 
ÿ��������ʾΪ(t,x,y)��tĬ�����򣬶�x���Σ�y����״����ά�� 
��ʼ��ֵ��Ҫ���޸Ĳ���ʵ�֡�
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
		{//�������ټ���Щ 
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
//		for(int i=l; i<=r; ++i) q[i]=tmp[i];//������Ȼ���� ��ѧ 
	}
}

int main()
{
	n=read(),m=read();
	int qcnt=0,mx=0;
	for(int x,y,i=1; i<=n; ++i)
		x=read()+1,y=read()+1, mx=std::max(mx,y), q[++qcnt]=Operation(0,x,y,0);//�������Ϊ[1,1e7+7] 
	for(int a,b,c,d,i=1; i<=m; ++i)
	{
		a=read()+1,b=read()+1,c=read()+1,d=read()+1;
		mx=std::max(mx,std::max(b,d));//��ȻҪ�Ͳ�ѯ����ȡmax������Ȼ���ϵ���ô������ 
		q[++qcnt]=Operation(i,a-1,d,-1), q[++qcnt]=Operation(i,a-1,b-1,1);
		q[++qcnt]=Operation(i,c,b-1,-1), q[++qcnt]=Operation(i,c,d,1);
	}
	BIT::Max=mx;
	CDQ(1,qcnt);
	for(int i=1; i<=m; ++i) printf("%d\n",Ans[i]);

	return 0;
}
