//ÿ�������ֽ�Ϊһ����������(t,p)����(ʱ��,����λ��)��ʱ��Ĭ��������CDQ���δ���ڶ�ά 
//����λ����ͬ�Ĳ��� �޸������ڲ�ѯ 
//ʱ����Ĭ������� ���Կ��Ժ��Ե��Բ�����Ӱ�죻��Ӱ���ֻ��λ�á� 
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
		{//ע�����鲢���ں�: ����ͬ�����ֵ���/�ұߵģ�����֮���Ӱ�����ںϲ��ô�����ǰ�����ˣ����Ե�ǰ�ǲ���Ҫ�ܵ� 
			if(q[p1]<q[p2])
			{//������ߵ�����ͳ���޸�ֵ(��߱�ʾ����λ�ÿ��� ���Ի���ұߵ�ѯ�ʲ���Ӱ��) 
				if(!q[p1].id) sum+=q[p1].val;
				tmp[t++]=q[p1++];
			}
			else
			{//�����ұߵ�������²�ѯ 
				if(q[p2].id==1) Ans[q[p2].val]-=sum;
				else if(q[p2].id==2) Ans[q[p2].val]+=sum;
				tmp[t++]=q[p2++];
			}
		}
		while(p1<=m) tmp[t++]=q[p1++];//�޲�ѯ�� 
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
