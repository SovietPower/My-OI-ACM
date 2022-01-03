/*
19604kb 36292ms
朴素线段树：线段树上每个点维护O(k)个信息，区间合并时O(k^2)，总O(mk^2logn)->GG 
考虑费用流：建一条n+1个点的链(点权设在边上，故需n+1个点)，链上每个点和S、T连边，相邻点连边 
这样数列中的区间和每条增广路一一对应 
每次最多增广k次，O(nmk)->still GG 
考虑费用流这一过程的实质：每次增广相当于贪心，本质上只有两种情况：
选取一段(新增一个区间)、从已选的某个区间中删除一段 
使用线段树实现这个贪心过程，支持(单点修改、)区间查询最大子段和(选取)、区间取反(相当于删除) 
这样每次查询修改k次，最后把修改逐一复原 
O(mklogn)
注: 1.需要维护一个区间最小值，因为取反后原区间最小值就成了最大值 
2.用堆式存储要更好，因为查找最大子段和需要得到位置 
(1)根节点是0 
(2)另外用Merge代替Update可以方便地用在Query()中 (好吧其实再写个函数无所谓) 
(3)如果存左右儿子的话别忘了合并时也改掉 and tag..
3.重载'+'后左右两运算数不要反 
4.Reverse()必须一次到完整区间，因为上边的节点需要下边的完整信息(脑补) 
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
				sk[++tp]=pos;//反转前先入栈 
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
