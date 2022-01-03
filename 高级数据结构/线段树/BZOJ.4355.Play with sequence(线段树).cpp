/*
52708kb	4412ms
问题在于操作二。操作二可以拆分成：区间加C、区间(对0)取max。
注意到操作一的C都是非负数，即数列中不会出现负数，所以我们直接维护最小值和最小值出现的次数即可得到答案。
操作一的赋值和操作二的加都是模板。但是取max会影响最小值的个数（某些>mn的值一起变成最小值）。
参照吉司机线段树，我们还需要维护严格次小值se。
进行max(v)操作时，若mn[rt]>=v，则直接返回；若se[rt]>v>mn[rt]，则直接打个max标记；
若v>=se[rt]>mn[rt]，没办法做，只能继续递归区间。
复杂度可证明，为O(mlog^2n)，直接表现常为O(mlogn)。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=3e5+5,INF=1e9+1;
const LL INFl=1e16;

char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

struct Segment_Tree
{
	#define S N<<2
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,rt<<1
	#define rson m+1,r,rt<<1|1
	int cnt[S],cov[S],sz[S];
	LL add[S],tag[S],mn[S],se[S];

	inline void Update(int rt)
	{
		int l=ls, r=rs;
		mn[rt]=std::min(mn[l],mn[r]);
		if(mn[l]<mn[r]) se[rt]=std::min(se[l],mn[r]), cnt[rt]=cnt[l];
		else if(mn[l]>mn[r]) se[rt]=std::min(se[r],mn[l]), cnt[rt]=cnt[r];
		else se[rt]=std::min(se[l],se[r]), cnt[rt]=cnt[l]+cnt[r];
	}
	inline void Cov(int x,int v)
	{
		add[x]=0, tag[x]=-INFl, cov[x]=v, cnt[x]=sz[x], mn[x]=v, se[x]=INFl;
	}
	inline void Add(int x,LL v)//LL!
	{
		add[x]+=v, mn[x]+=v;
		if(se[x]!=INFl) se[x]+=v;
		if(tag[x]!=-INFl/*!*/) tag[x]+=v;
	}
	inline void Max(int x,LL v)
	{
		mn[x]=std::max(mn[x],v), tag[x]=std::max(tag[x],v);
	}
	void PushDown(int rt)
	{
		if(cov[rt]!=INF) Cov(ls,cov[rt]), Cov(rs,cov[rt]), cov[rt]=INF;
		if(add[rt]) Add(ls,add[rt]), Add(rs,add[rt]), add[rt]=0;
		if(tag[rt]!=-INFl) Max(ls,tag[rt]), Max(rs,tag[rt]), tag[rt]=-INFl;
	}
	void Build(int l,int r,int rt)
	{
		cov[rt]=INF, tag[rt]=-INFl;
		if(l==r)
		{
			cnt[rt]=sz[rt]=1;
			mn[rt]=read(), se[rt]=INFl;
			return;
		}
		int m=l+r>>1;
		Build(lson), Build(rson);
		Update(rt), sz[rt]=sz[ls]+sz[rs];
	}
	void Modify_Cov(int l,int r,int rt,int L,int R,int v)
	{
		if(L<=l && r<=R) {Cov(rt,v); return;}
		PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify_Cov(lson,L,R,v);
		if(m<R) Modify_Cov(rson,L,R,v);
		Update(rt);
	}
	void Modify_Add(int l,int r,int rt,int L,int R,int v)
	{
		if(L<=l && r<=R) {Add(rt,v); return;}
		PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify_Add(lson,L,R,v);
		if(m<R) Modify_Add(rson,L,R,v);
		Update(rt);
	}
	void Modify_Max(int l,int r,int rt,int L,int R,int v)
	{
		if(mn[rt]>=v) return;
		if(L<=l && r<=R && se[rt]>v) {Max(rt,v); return;}
		PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify_Max(lson,L,R,v);
		if(m<R) Modify_Max(rson,L,R,v);
		Update(rt);
	}
	int Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return mn[rt]?0:cnt[rt];
		PushDown(rt);
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return Query(lson,L,R)+Query(rson,L,R);
			else return Query(lson,L,R);
		else return Query(rson,L,R);
	}
}T;

int main()
{
	int n=read(),m=read(); T.Build(1,n,1);
	for(int opt,l,r; m--; )
	{
		opt=read(),l=read(),r=read();
		if(opt==1) T.Modify_Cov(1,n,1,l,r,read());
		else if(opt==2) T.Modify_Add(1,n,1,l,r,read()),T.Modify_Max(1,n,1,l,r,0);
		else printf("%d\n",T.Query(1,n,1,l,r));
	}
	return 0;
}
