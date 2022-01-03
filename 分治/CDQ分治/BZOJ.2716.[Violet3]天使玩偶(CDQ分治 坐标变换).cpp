/*
43796kb	32744ms
$Description$
��άƽ���г�ʼ��$n$���㣬$m$�β�����1. ��ĳ��λ���½�һ���㣻2. ѯ�ʵ�ǰ���е�����ĳλ������ĵ��ж�Զ��
$n,m\leq 3\times 10^5$��
$Solution$
���Ƕ���������a,b������Ϊ|x[a]-x[b]|+|y[a]-y[b]|�����a��b�����ϣ������ǿ��԰Ѿ���ֵȥ������x[a]+y[a]-(x[b]+y[b])��
������Ҫ������x[b]<=x[a]��y[b]<=y[a]������x[b]+y[b]����CDQ����+��״��������
�����a����b�������أ�����ͨ������任���(��ΪҪ���ֻ����Ծ���)��
����任������Xmax��Ymax��ȥxi��yi��
�������֮ǰ�ķ�����ÿ�α任����ǰ��Ҫ�Ѳ������б�Ϊ��ʼ����(ʱ������)������������������
������ÿ�η���ǰ��x sortһ�飬����������tmΪ�ؼ�������(ͬһ������Ҫʱ������) 
�Ż�: �����޸�ʱ���޸ġ��������ź�����ɨһ����´� 
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
		while(p) res=std::max(t[p],res),p^=lb(p);//^����- 
		return res;
	}
	void Clear(int p){
		while(p<=Max)//�����Max�Ӱ����ϡ���
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
		for(int i=l; i<=r; ++i) q[i]=tmp[i];//���ź� ����֮��Ϳ���ֻ�ڲ�ѯʱ������(����Ҫ������) 
		p1=l, p2=m+1;
		for(; p2<=r; ++p2)
			if(q[p2].type)
			{
				for(; p1<=m&&q[p1].x<=q[p2].x; ++p1)
					if(!q[p1].type) A[++t]=q[p1].y,BIT::Update(q[p1].y,q[p1].x+q[p1].y);
				if(val=BIT::Query(q[p2].y))
					Ans[q[p2].type]=std::min(Ans[q[p2].type],q[p2].x+q[p2].y-val);//ֻ���е�ʱ���´�! ����𰸻�������x+y 
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
	for(int x,y,i=1; i<=n; ++i)//�Ǹ�����...
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
