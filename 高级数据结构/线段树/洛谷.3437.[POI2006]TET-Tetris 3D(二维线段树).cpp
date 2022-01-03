/*
6564ms 123972KB
����һ��d*s�ķ��飬��Ҫ�����ƽ��������һ����ߵ�h' 
��������ƽ�������ֵΪh+h' 

���ڱ��⣬ά�����߶�h��all 
����ƽ���x��ά��һ���߶���t1��ÿ��t1�Ľڵ�ά����Ӧy��������߶���t2(h��all)
(ͬһά����Ҫά�������������߶���)
t1Ҫ�ñ�����û�ʵ�֣�t2��ͨ�ͱ�����û������� 
�ռ�O(n^2) ʱ��O(n*(logn)^2) 

������û�: 
����������(��ά�߶���)��˵������´�(PushDown)����Ϣ�ϴ�(PushUp)�ͺ���ʵ���� 
��ʱ�õ�������û� 
д��ͨ�߶���ʱ�����޸�������ǣ�����Ҫ��ʱ���·ű�ǲ����� 
�ǿɲ����Բ��Ա�ǽ����·ţ����Ǿ�����ʱ��ͳ�Ʊ�ǶԴ𰸵Ĺ��ף��Ӷ�ʡȥ����·Ź��̣�
������ӡ����Ϊ�������߶���ÿ���ڵ�ά��sum,all���ֱ��ʾ�ýڵ��������ĺͣ���ýڵ�������������䶼�еı��all 
����ʱ��һ·���¾����ڵ��sumֵ��ֱ����ǰ�ڵ�������ȫ��Ŀ�����串�ǣ����¸ýڵ��all��return (˳���޸ľ�ʡȥ��PushUp)
��ѯʱ ���෴��һ·ͳ�ƾ����ڵ��allֵ��ֱ����ǰ�ڵ�������ȫ��Ŀ�����串�ǣ��øýڵ��sum���´� 

ע:������θ߶�ֻ��Խ��Խ�ߣ�������Ϣ�ϴ�ʱ����Ҫ�õ����Ҷ��ӵ���Ϣ��ʹ�ñ�����û��Ͳ��������� 
���𰸲����ǵ����ģ���ô���´�ʱ�ͻ�������⣬��Ϊ����֪����Ǵ��ϵ�˳����˭��ǰ˭�ں� 
���ұ���Ҫȡ���ֵ������ֱ�Ӹ��� 
��̫����...
ע���Ǵ�0��ʼ ��Ҫд��
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
#define gc() getchar()
//#define gc() (SS==TT &&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define lson node[rt].ls,l,m
#define rson node[rt].rs,m+1,r
const int N=1e3+2,MAXIN=5e6;

int r,c;
//char IN[MAXIN],*SS=IN,*TT=IN;
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
struct Seg_Tree
{
	int tot;
	struct Node
	{
		int ls,rs,maxh,all;
	}node[N<<1];
	void Build(int l,int r)
	{
		int p=tot++;
		node[p].maxh=node[p].all=0;
		if(l==r) {node[p].ls=node[p].rs=-1; return;}
		int m=l+r>>1;
		node[p].ls=tot, Build(l,m);
		node[p].rs=tot, Build(m+1,r);
	}
	void Init(int l,int r)
	{
		tot=0, Build(l,r);
	}
	void Modify(int rt,int l,int r,int L,int R,int v)
	{
//		node[rt].maxh=v;
		node[rt].maxh=std::max(node[rt].maxh,v);
		if(L<=l && r<=R)
		{
			node[rt].all=std::max(node[rt].all,v);
			return;
		}
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R,v);
		if(m<R) Modify(rson,L,R,v);
	}
	int Query(int rt,int l,int r,int L,int R)
	{
		if(L<=l && r<=R) return node[rt].maxh;
		int res=node[rt].all,m=l+r>>1;
		if(L<=m) res=std::max(res,Query(lson,L,R));
		if(m<R) res=std::max(res,Query(rson,L,R));
		return res;
	}
};
struct Seg_Tree2D
{
	int tot;
	struct Node
	{
		int ls,rs;
		Seg_Tree maxh,all;
	}node[N<<1];
	void Build(int l,int r,int c)
	{
		int p=tot++;
		node[p].all.Init(0,c), node[p].maxh.Init(0,c);
//		node[p].l=l, node[p].r=r;
		if(l==r) {node[p].ls=node[p].rs=-1; return;}
		int m=l+r>>1;
		node[p].ls=tot, Build(l,m,c);
		node[p].rs=tot, Build(m+1,r,c);
	}
	void Init(int l,int r,int c)
	{
		tot=0, Build(l,r,c);
	}
	void Modify(int rt,int l,int r,int x1,int x2,int y1,int y2,int v)
	{
		node[rt].maxh.Modify(0,0,c,y1,y2,v);
		if(x1<=l && r<=x2)
		{
			node[rt].all.Modify(0,0,c,y1,y2,v);
			return;
		}
		int m=l+r>>1;
		if(x1<=m) Modify(lson,x1,x2,y1,y2,v);
		if(m<x2) Modify(rson,x1,x2,y1,y2,v);
	}
	int Query(int rt,int l,int r,int x1,int x2,int y1,int y2)
	{
		if(x1<=l && r<=x2) return node[rt].maxh.Query(0,0,c,y1,y2);
		int res=node[rt].all.Query(0,0,c,y1,y2),m=l+r>>1;
		if(x1<=m) res=std::max(res,Query(lson,x1,x2,y1,y2));//����(lson,x1,m)![x1,m]�ǲ�ѯ���� 
		if(m<x2) res=std::max(res,Query(rson,x1,x2,y1,y2));
		return res;
	}
}t;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("3437.in","r",stdin);
#endif

	r=read()-1,c=read()-1;
	t.Init(0,r,c);
	int m=read(),x,y,d,s,h,tmp,x2,y2;
	while(m--)
	{
		d=read(),s=read(),h=read(),x=read(),y=read();
		x2=x+d-1, y2=y+s-1;
		tmp=t.Query(0,0,r,x,x2,y,y2);
		t.Modify(0,0,r,x,x2,y,y2,h+tmp);
//		printf("MAX:%d\n",t.Query(0,0,r,0,c));
	}
	printf("%d",t.Query(0,0,r,0,r,0,c));

	return 0;
}
