/*
19604kb 36292ms
�����߶������߶�����ÿ����ά��O(k)����Ϣ������ϲ�ʱO(k^2)����O(mk^2logn)->GG 
���Ƿ���������һ��n+1�������(��Ȩ���ڱ��ϣ�����n+1����)������ÿ�����S��T���ߣ����ڵ����� 
���������е������ÿ������·һһ��Ӧ 
ÿ���������k�Σ�O(nmk)->still GG 
���Ƿ�������һ���̵�ʵ�ʣ�ÿ�������൱��̰�ģ�������ֻ�����������
ѡȡһ��(����һ������)������ѡ��ĳ��������ɾ��һ�� 
ʹ���߶���ʵ�����̰�Ĺ��̣�֧��(�����޸ġ�)�����ѯ����Ӷκ�(ѡȡ)������ȡ��(�൱��ɾ��) 
����ÿ�β�ѯ�޸�k�Σ������޸���һ��ԭ 
O(mklogn)
ע: 1.��Ҫά��һ��������Сֵ����Ϊȡ����ԭ������Сֵ�ͳ������ֵ 
2.�ö�ʽ�洢Ҫ���ã���Ϊ��������Ӷκ���Ҫ�õ�λ�� 
(1)���ڵ���0 
(2)������Merge����Update���Է��������Query()�� (�ð���ʵ��д����������ν) 
(3)��������Ҷ��ӵĻ������˺ϲ�ʱҲ�ĵ� and tag..
3.����'+'����������������Ҫ�� 
4.Reverse()����һ�ε��������䣬��Ϊ�ϱߵĽڵ���Ҫ�±ߵ�������Ϣ(�Բ�) 
*/
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
#define gc() getchar()
const int N=1e5+5;

int n,m,tp;
//char IN[MAXIN],*SS=IN,*TT=IN;
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
struct Node
{
	struct Node2
	{
		int l,r,val;
		inline friend Node2 operator +(const Node2 &x,const Node2 &y)
		{
			Node2 tmp;
			tmp.l=x.l, tmp.r=y.r, tmp.val=x.val+y.val;
			return tmp;
		}
		inline friend bool operator <(const Node2 &x,const Node2 &y)
		{
			return x.val<y.val;
		}
	}sum,lmn,rmn,lmx,smx,smn,rmx;
	int ls,rs;
	bool tag;
	inline void Init(int p,int v)
	{
		sum.val=lmx.val=rmx.val=lmn.val=rmn.val=smx.val=smn.val=v,
		sum.l=lmx.l=rmx.l=lmn.l=rmn.l=smx.l=smn.l=p;
		sum.r=lmx.r=rmx.r=lmn.r=rmn.r=smx.r=smn.r=p;
		ls=rs=-1, tag=0;
	}
}node[N<<1],sk[30];
struct Seg_Tree
{
	int tot;
	Node Merge(const Node &x,const Node &y)
	{
		Node rt;
//		printf("%d,%d(%d,%d) %d,%d(%d,%d)\n",x.smx.val,y.smx.val,x.smx.l,y.smx.r,x.rmx.val,y.lmx.val,x.rmx.l,y.lmx.r);
		rt.lmx=std::max(x.lmx,x.sum+y.lmx);
		rt.rmx=std::max(y.rmx,x.rmx+y.sum);//!
		rt.lmn=std::min(x.lmn,x.sum+y.lmn);
		rt.rmn=std::min(y.rmn,x.rmn+y.sum);
		rt.smx=std::max(x.rmx+y.lmx,std::max(x.smx,y.smx));
		rt.smn=std::min(x.rmn+y.lmn,std::min(x.smn,y.smn));
		rt.sum=x.sum+y.sum;
		rt.tag=0;//!
		return rt;
	}
	void Rev(int rt)
	{
		node[rt].tag^=1;
		std::swap(node[rt].lmx,node[rt].lmn), std::swap(node[rt].rmx,node[rt].rmn),
		std::swap(node[rt].smx,node[rt].smn),
		node[rt].lmx.val*=-1, node[rt].lmn.val*=-1, 
		node[rt].rmx.val*=-1, node[rt].rmn.val*=-1, 
		node[rt].smx.val*=-1, node[rt].smn.val*=-1, 
		node[rt].sum.val*=-1;
	}
	inline void PushDown(int rt)
	{
		Rev(node[rt].ls), Rev(node[rt].rs);
		node[rt].tag=0;
	}
	void Build(int l,int r)
	{
		int p=tot++;
		if(l==r) {node[p].Init(l,read()),node[p].ls=node[p].rs=-1; return;}
		int m=l+r>>1;
		node[p].ls=tot, Build(l,m),
		node[p].rs=tot, Build(m+1,r);
		int ls=node[p].ls,rs=node[p].rs;
		node[p]=Merge(node[ls],node[rs]);
		node[p].ls=ls, node[p].rs=rs;
//		printf("%d:%d~%d mx:%d(%d~%d) sum:%d\n",p+1,l,r,node[p].smx.val,node[p].smx.l,node[p].smx.r,node[p].sum.val);
	}
	void Modify(int l,int r,int rt,int p,int v)
	{
		if(l==r) {node[rt].Init(l,v); return;}
		if(node[rt].tag) PushDown(rt);
		int m=l+r>>1,ls=node[rt].ls,rs=node[rt].rs;
		if(p<=m) Modify(l,m,ls,p,v);
		else Modify(m+1,r,rs,p,v);
		node[rt]=Merge(node[ls],node[rs]);
		node[rt].ls=ls, node[rt].rs=rs;
	}
	void Reverse(int l,int r,int rt,int L,int R)
	{
		if(L==l && r==R) {Rev(rt); return;}//!
		if(node[rt].tag) PushDown(rt);
		int m=l+r>>1,ls=node[rt].ls,rs=node[rt].rs;
		if(L<=m)//!
			if(m<R) Reverse(l,m,ls,L,m),Reverse(m+1,r,rs,m+1,R);
			else Reverse(l,m,ls,L,R);
		else Reverse(m+1,r,rs,L,R);
		node[rt]=Merge(node[ls],node[rs]);
		node[rt].ls=ls, node[rt].rs=rs;
	}
	Node Query(int l,int r,int rt,int L,int R)
	{
//	WR:	if(L<=l && r<=R) return node[rt];
		if(L==l && r==R) return node[rt];//!
		if(node[rt].tag) PushDown(rt);
		int m=l+r>>1;
		if(L<=m)//!
			if(m<R) return Merge(Query(l,m,node[rt].ls,L,m),Query(m+1,r,node[rt].rs,m+1,R));
			else return Query(l,m,node[rt].ls,L,R);
		else return Query(m+1,r,node[rt].rs,L,R);
	}
//	void Print(int l,int r,int p)
//	{
//		if(l==r) return;
//		if(node[p].tag) PushDown(p);
//		int m=l+r>>1;
//		Print(l,m,node[p].ls),
//		printf("P:%d:%d~%d mx:%d(%d~%d) sum:%d\n",p+1,l,r,node[p].smx.val,node[p].smx.l,node[p].smx.r,node[p].sum.val);
//		Print(m+1,r,node[p].rs);
//	}
}t;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("3638.in","r",stdin);
#endif

	n=read();
	t.Build(1,n);//t.Print(1,n,0);
	m=read();
	int opt,p,k,l,r,res; Node pos;
	while(m--)
	{
		opt=read();
		if(!opt) p=read(),k=read(),t.Modify(1,n,0,p,k);
		else
		{
			l=read(),r=read(),k=read(),res=0;
			while(k--)
			{
				pos=t.Query(1,n,0,l,r);
//				printf("%d~%d val:%d\n",pos.smx.l,pos.smx.r,pos.smx.val);
				if(pos.smx.val<0) break;
				res+=pos.smx.val;
				sk[++tp]=pos;//��תǰ����ջ 
				t.Reverse(1,n,0,pos.smx.l,pos.smx.r);//t.Print(1,n,0);
			}
			printf("%d\n",res);
			while(tp)
				t.Reverse(1,n,0,sk[tp].smx.l,sk[tp].smx.r),--tp;
//			t.Print(1,n,0);
		}
	}
	return 0;
}
