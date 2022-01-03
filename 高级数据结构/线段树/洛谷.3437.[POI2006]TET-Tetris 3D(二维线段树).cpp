/*
6564ms 123972KB
下落一个d*s的方块，则要在这个平面区域找一个最高的h' 
更新整个平面区域的值为h+h' 

对于本题，维护最大高度h和all 
对于平面的x轴维护一棵线段树t1，每个t1的节点维护对应y轴的两棵线段树t2(h和all)
(同一维，需要维护独立的两棵线段树)
t1要用标记永久化实现，t2普通和标记永久化都可以 
空间O(n^2) 时间O(n*(logn)^2) 

标记永久化: 
对于树套树(二维线段树)来说，标记下传(PushDown)与信息上传(PushUp)就很难实现了 
这时用到标记永久化 
写普通线段树时，对修改区间打标记，在需要的时候下放标记并更新 
那可不可以不对标记进行下放，而是经过的时候统计标记对答案的贡献，从而省去标记下放过程？
以区间加、求和为例，新线段树每个节点维护sum,all，分别表示该节点包含区间的和，与该节点包含的整个区间都有的标记all 
更新时，一路更新经过节点的sum值，直到当前节点区间完全被目标区间覆盖，更新该节点的all，return (顺序修改就省去了PushUp)
查询时 正相反，一路统计经过节点的all值，直到当前节点区间完全被目标区间覆盖，用该节点的sum更新答案 

注:本题矩形高度只会越来越高，所以信息上传时不需要用到左右儿子的信息，使用标记永久化就不会有问题 
若答案并不是单调的，那么更新答案时就会出现问题，因为并不知道标记打上的顺序是谁在前谁在后 
而且必须要取最大值，不能直接覆盖 
不太明白...
注意是从0开始 不要写错！
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
		if(x1<=m) res=std::max(res,Query(lson,x1,x2,y1,y2));//不是(lson,x1,m)![x1,m]是查询区间 
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
