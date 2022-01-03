/*
无论怎么收割，长得快的草一定是不矮于长得慢的；而询问与下标无关 
所以按生长速度排序，某一时刻的高度一定是递增的，这样就可以二分了 
注意很多longlong 
小于x直接输出0!
Reset在查询里！所以查询中要有PushUp!
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
#define gc() getchar()
#define now node[rt]
#define lson node[node[rt].ls]
#define rson node[node[rt].rs]
typedef long long LL;
const int N=5e5+5;

LL A[N],sum[N];
struct Seg_Tree
{
	int tot;
	struct Node
	{
		LL maxn,sum,tag/*num of days*/,flag/*reset(>=0) or not(-1)*/;
		int l,r,ls,rs;
		Node() {flag=-1;}
	}node[N<<1];
	inline void PushUp(int rt)
	{
		now.sum = lson.sum + rson.sum;
		now.maxn = rson.maxn;
//		now.maxn = std::max(lson.maxn, rson.maxn);
	}
	inline void Reset(int rt,LL f)
	{
		now.sum=1LL*(now.r-now.l+1)*f, now.maxn=f;
		now.tag=0, now.flag=f;
	}
	inline void Update(int rt,LL tg)
	{
		now.tag += tg;
		now.sum += (sum[now.r]-sum[now.l-1])*tg;
		now.maxn += A[now.r]*tg;//最大值肯定是最高的那个 
	}
	void PushDown(int rt)
	{
		if(~now.flag)
		{
			Reset(now.ls,now.flag), Reset(now.rs,now.flag),
			now.flag=-1;
		}
		if(now.tag)//reset后重新赋上的tag 
		{
			Update(now.ls,now.tag), Update(now.rs,now.tag),
			now.tag=0;
		}
	}
	void Build(int l,int r)
	{
		int p=tot++;
		node[p].l=l, node[p].r=r;
//		node[p].tag=0, node[p].flag=-1;
		if(l==r) ;
//			node[p].ls = node[p].rs = -1,
//			node[p].maxn = node[p].sum = A[l];
		else
		{
			int m=l+r>>1;
			node[p].ls=tot, Build(l,m);
			node[p].rs=tot, Build(m+1,r);
//			PushUp(p);
		}
	}
	int Find(int rt,LL x)
	{
		if(now.l==now.r) return now.l;
		PushDown(rt);
		if(lson.maxn>=x) return Find(now.ls,x);
		return Find(now.rs,x);
	}
	LL Query_Sum(int rt,int L,int R,LL x)//Reset N[L~R] to x
	{
		LL res=0;
		if(L<=now.l && now.r<=R) {res=now.sum; Reset(rt,x); return res;}//!
		PushDown(rt);
		int m=now.l+now.r>>1;
		if(L<=m) res=Query_Sum(now.ls,L,R,x);
		if(m<R) res+=Query_Sum(now.rs,L,R,x);
		PushUp(rt);//!
		return res;
	}
//	LL Query_Sum(int rt,int p,LL x)//Reset N[L~R] to x
//	{
//		if(now.r < p) return 0;
//		LL res;
//		if(now.l >= p) {res=now.sum; Reset(rt,x); return res;}//!
//		PushDown(rt);
//		res=Query_Sum(now.ls,p,x)+Query_Sum(now.rs,p,x);
//		PushUp(rt);
//		return res;
//	}
}t;
#undef now
inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("4293.in","r",stdin);
#endif

	LL n=read(),m=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	std::sort(A+1,A+1+n);
	t.Build(1,n);
	for(int i=1; i<=n; ++i) sum[i]=sum[i-1]+A[i];
	for(LL res,day,x,las=0,pos; m; --m,las=day)
	{
		day=read(),x=read();
		t.Update(0, day-las);
		if(t.node[0].maxn < x) {puts("0"); continue;}//很有效 and必须要加！ 
		pos=t.Find(0,x), printf("%lld\n",t.Query_Sum(0,pos,n,x)-(n-pos+1)*x);//longlong 
//		pos=t.Find(0,x), printf("%lld\n",t.Query_Sum(0,pos,x)-(n-pos+1)*x);//longlong 
	}
	return 0;
}
