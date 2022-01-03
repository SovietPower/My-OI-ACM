/*
13528kb	4472ms
ά���������ֵ������ûʲô�ã��޸ĵ�ʱ��ͱ�����ࡣ
���Ƿ�����ʱ������and/or��������û��Ӱ��ģ���ʱ�������������Ӱ����ͬ(���ı���ĳЩλ)��
��������and x����$sum_{or}and x==sum_{or}$ʱ���������û��Ӱ�죻
��������������xΪ1��λ����ͬ����xû�����ǲ����е�1�������ֱ�Ӵ�and/or��ǣ�mx[rt]and/or=x��$sum_{and}^sum_{or}$���������ڲ����е�1��
�������and��ʱ��Ҳ�԰������ֵand����>=�������ġ������һ���д��һ�ַ����ɡ������������������޸ĺ�ı�������ͬ����
�ڲ���������������ʱ�����ݹ������䡣
���Ӷ�Ϊ$O(nklogn)$��$k$Ϊλ����֤���μ���https://csacademy.com/contest/round-70/task/and-or-max/solution��
��������and/or��ǿ��Ի�������ӱ�ǡ�
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
	inline void PushDown(int rt)//��Ҷ 
	{
		Upd(ls,tag[rt]), Upd(rs,tag[rt]), tag[rt]=0;
	}
	void Modify_And(int l,int r,int rt,int L,int R,int v)
	{
		if((sor[rt]&v)==sor[rt]) return;//==���ȼ���&,|�ߡ���
		if(L<=l && r<=R && (sand[rt]&v)-sand[rt]==(sor[rt]&v)-sor[rt])//!((sand[rt]^sor[rt])&v))//Ϊʲô�����ء���
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
