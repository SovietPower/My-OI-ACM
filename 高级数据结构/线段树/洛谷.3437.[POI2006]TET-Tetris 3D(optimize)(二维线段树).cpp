/*
3624ms 91035KB
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
初始为0的并不需要建树 
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
//#define gc() getchar()
#define gc() (SS==TT &&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define lson rt<<1,l,m
#define rson rt<<1|1,m+1,r
const int N=1002*3,MAXIN=5e6;

int n,m;
char IN[MAXIN],*SS=IN,*TT=IN;
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
struct Seg_Tree
{
	int maxh[N],all[N];
	void Modify(int rt,int l,int r,int L,int R,int v)
	{
		maxh[rt]=std::max(maxh[rt],v);
		if(L<=l && r<=R)
		{
			all[rt]=std::max(all[rt],v);
			return;
		}
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R,v);
		if(m<R) Modify(rson,L,R,v);
	}
	int Query(int rt,int l,int r,int L,int R)
	{
		if(L<=l && r<=R) return maxh[rt];
		int res=all[rt],m=l+r>>1;
		if(L<=m) res=std::max(res,Query(lson,L,R));
		if(m<R) res=std::max(res,Query(rson,L,R));
		return res;
	}
};
struct Seg_Tree2D
{
	Seg_Tree maxh[N],all[N];
	void Modify(int rt,int l,int r,int L,int R,int y1,int y2,int v)
	{
		maxh[rt].Modify(1,1,m,y1,y2,v);
		if(L<=l && r<=R)
		{
			all[rt].Modify(1,1,m,y1,y2,v);
			return;
		}
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R,y1,y2,v);
		if(m<R) Modify(rson,L,R,y1,y2,v);
	}
	int Query(int rt,int l,int r,int L,int R,int y1,int y2)
	{
		if(L<=l && r<=R) return maxh[rt].Query(1,1,m,y1,y2);
		int res=all[rt].Query(1,1,m,y1,y2),m=l+r>>1;
		if(L<=m) res=std::max(res,Query(lson,L,R,y1,y2));//不是(lson,L,m)![L,m]是查询区间 
		if(m<R) res=std::max(res,Query(rson,L,R,y1,y2));
		return res;
	}
}t;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("3437.in","r",stdin);
#endif

	n=read(),m=read();
	int q=read(),x,y,d,s,h,tmp,x2,y2;
	while(q--)
	{
		d=read(),s=read(),h=read(),x=read()+1,y=read()+1;
		x2=x+d-1, y2=y+s-1;
		tmp=t.Query(1,1,n,x,x2,y,y2);
		t.Modify(1,1,n,x,x2,y,y2,h+tmp);
	}
	printf("%d",t.Query(1,1,n,1,n,1,m));

	return 0;
}
