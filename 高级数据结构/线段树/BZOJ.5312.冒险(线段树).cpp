/*
13528kb	4472ms
维护区间最大值？好像没什么用，修改的时候和暴力差不多。
我们发现有时候区间and/or对区间是没有影响的，有时候对区间所有数影响相同(都改变了某些位)。
比如区间and x，当$sum_{or}and x==sum_{or}$时，这个操作没有影响；
当区间所有数在x为1的位上相同，即x没有它们不共有的1，则可以直接打and/or标记，mx[rt]and/or=x。$sum_{and}^sum_{or}$就是区间内不共有的1。
（这个在and的时候也对啊，最大值and后还是>=其它数的。但是我还是写另一种方法吧。。即区间与和区间或修改后改变量都相同。）
在不满足这两个条件时继续递归子区间。
复杂度为$O(nklogn)$，$k$为位数。证明参见：https://csacademy.com/contest/round-70/task/and-or-max/solution。
另外区间and/or标记可以换成区间加标记。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 200000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=200005<<2;

char IN[MAXIN],*SS=IN,*TT=IN;
inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	int sand[N],sor[N],mx[N],tag[N];

	#define Update(rt) sand[rt]=sand[ls]&sand[rs],sor[rt]=sor[ls]|sor[rs],mx[rt]=std::max(mx[ls],mx[rs])
	void Build(int l,int r,int rt)
	{
		if(l==r) {sand[rt]=sor[rt]=mx[rt]=read(); return;}
		Build(l,(l+r>>1),ls), Build((l+r>>1)+1,r,rs);
		Update(rt);
	}
	inline void Upd(int rt,int v)
	{
		sand[rt]+=v, sor[rt]+=v, tag[rt]+=v, mx[rt]+=v;
	}
	inline void PushDown(int rt)//非叶 
	{
		Upd(ls,tag[rt]), Upd(rs,tag[rt]), tag[rt]=0;
	}
	void Modify_And(int l,int r,int rt,int L,int R,int v)
	{
		if((sor[rt]&v)==sor[rt]) return;//==优先级比&,|高。。
		if(L<=l && r<=R && (sand[rt]&v)-sand[rt]==(sor[rt]&v)-sor[rt])//!((sand[rt]^sor[rt])&v))//为什么不对呢。。
		{
			Upd(rt,(sand[rt]&v)-sand[rt]); return;
		}
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify_And(lson,L,R,v);
		if(m<R) Modify_And(rson,L,R,v);
		Update(rt);
	}
	void Modify_Or(int l,int r,int rt,int L,int R,int v)
	{
		if((sand[rt]|v)==sand[rt]) return;
		if(L<=l && r<=R && (sand[rt]|v)-sand[rt]==(sor[rt]|v)-sor[rt])//!((sand[rt]^sor[rt])&v))
		{
			Upd(rt,(sand[rt]|v)-sand[rt]); return;
		}
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify_Or(lson,L,R,v);
		if(m<R) Modify_Or(rson,L,R,v);
		Update(rt);
	}
	int Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return mx[rt];
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return std::max(Query(lson,L,R),Query(rson,L,R));
			else return Query(lson,L,R);
		return Query(rson,L,R);
	}
}T;

int main()
{
	int n=read(),m=read();
	T.Build(1,n,1);
	for(int opt,l,r; m--; )
	{
		if((opt=read())==1) l=read(),r=read(),T.Modify_And(1,n,1,l,r,read());
		else if(opt==2) l=read(),r=read(),T.Modify_Or(1,n,1,l,r,read());
		else l=read(),r=read(),printf("%d\n",T.Query(1,n,1,l,r));
	}
	return 0;
}
