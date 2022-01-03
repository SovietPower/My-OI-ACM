/*
421ms	29184KB(Rank1了233)
$Description$
给定一个长为n的序列，多次询问[l,r]中只出现一次的数，输出任意一个即可(没有输出0)。
$Solution$
记las[i],nxt[i]分别为A[i]上一次、下一次出现的位置，则会对区间[l,r]产生贡献当且仅当las[i]<l && r<nxt[i]。，也就是A[i]会对[las[i]+1,nxt[i]-1]产生贡献。这应该可以用线段树区间修改。
将询问离线，按右端点排序，枚举当前点i作为右端点，用线段树维护[1,i]上las[p]最小的位置p。
那么如果min{las[p]}<l则p为所求解之一；否则无解。
当前A[i]的出现会消除1(las[las[i]])~las[i]上las[i]的贡献，直接将线段树上las[i]的值(las[las[i]])改为INF即可。
不知道直接莫队+set能不能过。不过看过了的莫队(套权值分块/vector)感觉set应该没问题。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=5e5+5,INF=10000000;

int n,Q,A[N],pre[N],las[N],Ans[N];
struct Ques{
	int l,r,id;
	inline bool operator <(const Ques &x)const{
		return r<x.r;
	}
}q[N];
struct Segment_Tree
{
	#define lson rt<<1
	#define rson rt<<1|1
	#define ToL l,m,rt<<1
	#define ToR m+1,r,rt<<1|1
	int n,Min,Val,mn[N<<2],val[N<<2];
	inline void Update(int rt)
	{
		if(mn[lson]<mn[rson]) mn[rt]=mn[lson], val[rt]=val[lson];
		else mn[rt]=mn[rson], val[rt]=val[rson];
	}
	void Build(int l,int r,int rt)
	{
		if(l==r) mn[rt]=las[l], val[rt]=A[l];
		else
		{
			int m=l+r>>1;
			Build(ToL), Build(ToR);
			Update(rt);
		}
	}
	void Modify(int l,int r,int rt,int p)//Modify t[p] to INF
	{
		if(l==r) mn[rt]=INF;
		else
		{
			int m=l+r>>1;
			if(p<=m) Modify(ToL,p);
			else Modify(ToR,p);
			Update(rt);
		}
	}
	void Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R){
			if(mn[rt]<Min) Min=mn[rt], Val=val[rt];
		}
		else
		{
			int m=l+r>>1;
			if(L<=m) Query(ToL,L,R);
			if(m<R) Query(ToR,L,R);
		}
	}
	int Get_Ans(int l,int r)
	{
		Min=INF, Query(1,n,1,l,r);
		return Min<l?Val:0;
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	T.n=n=read();
	for(int i=1; i<=n; ++i) las[i]=pre[A[i]=read()], pre[A[i]]=i;
	T.Build(1,n,1);
	Q=read();
	for(int i=1; i<=Q; ++i) q[i].l=read(), q[i].r=read(), q[i].id=i;
	std::sort(q+1,q+1+Q), q[Q+1].r=n+1;
	for(int i=1,now=1; i<=n&&now<=Q; ++i)
	{
		if(las[i]) T.Modify(1,n,1,las[i]);
		while(/*now<=Q &&*/q[now].r==i) Ans[q[now].id]=T.Get_Ans(q[now].l,i), ++now;
	}
	for(int i=1; i<=Q; ++i) printf("%d\n",Ans[i]);

	return 0;
}
