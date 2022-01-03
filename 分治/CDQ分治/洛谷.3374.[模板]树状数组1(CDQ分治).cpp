//每个操作分解为一个有序数对(t,p)，即(时间,操作位置)，时间默认有序，用CDQ分治处理第二维 
//对于位置相同的操作 修改优先于查询 
//时间是默认有序的 所以可以忽略掉对操作的影响；有影响的只是位置。 
#include <cstdio>
#include <cctype>
#define gc() getchar()
//typedef long long LL;
const int N=5e5+5;

int n,m,Ans[N];
struct Ques
{
	int id,pos,val;//id:0:Modify 1:left point 2:right point
	Ques() {;}
	Ques(int i,int p,int v): id(i),pos(p),val(v) {};
//	Ques(int i=0,int p=0,int v=0) {id=i,pos=p,val=v;}
	bool operator <(const Ques &a) const{
		return pos==a.pos?id<a.id:pos<a.pos;
	}
}q[N*3],tmp[N*3];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
void CDQ(int l,int r)
{
	if(l<r)
	{
		int m=l+r>>1; CDQ(l,m), CDQ(m+1,r);
		int p1=l,p2=m+1,t=0,sum=0;
		while(p1<=m&&p2<=r)
		{//注意理解归并的内涵: 对于同被划分到左/右边的，它们之间的影响已在合并该大区间前计算了，所以当前是不需要管的 
			if(q[p1]<q[p2])
			{//对于左边的区间统计修改值(左边表示操作位置靠左 所以会对右边的询问产生影响) 
				if(!q[p1].id) sum+=q[p1].val;
				tmp[t++]=q[p1++];
			}
			else
			{//对于右边的区间更新查询 
				if(q[p2].id==1) Ans[q[p2].val]-=sum;
				else if(q[p2].id==2) Ans[q[p2].val]+=sum;
				tmp[t++]=q[p2++];
			}
		}
		while(p1<=m) tmp[t++]=q[p1++];//无查询了 
		while(p2<=r)
		{
			if(q[p2].id==1) Ans[q[p2].val]-=sum;
			else if(q[p2].id==2) Ans[q[p2].val]+=sum;
			tmp[t++]=q[p2++];
		}
		for(int i=0; i<t; ++i) q[l+i]=tmp[i];
	}
}

int main()
{
	n=read(),m=read();
	int qcnt=0,acnt=0;
	for(int i=1; i<=n; ++i) q[++qcnt]=Ques(0,i,read());
	for(int id,l,r,i=1; i<=m; ++i)
	{
		id=read(),l=read(),r=read();
		if(id==1) q[++qcnt]=Ques(0,l,r);
		else ++acnt, q[++qcnt]=Ques(1,l-1,acnt), q[++qcnt]=Ques(2,r,acnt);
	}
	CDQ(1,qcnt);
	for(int i=1; i<=acnt; ++i) printf("%d\n",Ans[i]);

	return 0;
}
