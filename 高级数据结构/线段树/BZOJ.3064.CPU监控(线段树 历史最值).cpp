/*
$Description$
有一个长为n的序列Ai，要求支持查询[l,r]的最值、历史最值，区间加/重设 
$Solution$
线段树，每个点再维护一个历史(从0到现在)最大值、历史(从上次下传标记到现在)最大的set,add标记 
PushDown时肯定是先下放历史标记，之后再用当前标记更新 
要记得当要PushDown某个点时，last,now的val都是历史的(下传前),所以now.v + last.add就是下传前值+[下传前到现在]一次最大的修改的值 
不能只在Set后清空add。像代码这么做很正确，可以稍微画个图 
每次now的操作不仅要更新now，还要更新last 
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
#define gc() getchar()
#define lson node[node[rt].ls]
#define rson node[node[rt].rs]
const int N=1e5+5,INF=0x3f3f3f3f;

int n,m;
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
#define now node[rt]
struct Seg_Tree
{
	int tot;
	struct Node
	{
		int ls,rs,nv,lv,nadd,ladd,nset,lset;
	}node[N<<1];
	inline void PushUp(int rt)
	{
		now.nv = std::max(lson.nv, rson.nv);
		now.lv = std::max(lson.lv, rson.lv);
	}
	void Build(int l,int r)
	{
		int rt=tot++;
		now.nadd=now.ladd=0, now.nset=now.lset=-INF;
		if(l==r) now.nv=now.lv=read();
		else
		{
			int m=l+r>>1;
			now.ls=tot, Build(l,m);
			now.rs=tot, Build(m+1,r);
			PushUp(rt);
		}
	}
	inline void Update(int &x,int y) {x = std::max(x,y);}
	inline void L_Set(int rt,int v)
	{
		Update(now.lv, v);
		Update(now.lset, v);
	}
	inline void L_Add(int rt,int v)
	{
		Update(now.lv, now.nv+v);
		if(now.nset>-INF) Update(now.lset, now.nset+v);//判断的是nset>-INF(用now更新last关last什么事)//necessary!
		else Update(now.ladd, now.nadd+v);
		//如果之后rt.ladd下传了，那就没了；如果没下传，仍是rt下传前情况(历史)，即可以用now.ladd;或是用上次下传前标记+到现在修改最大值 
	}
	inline void N_Set(int rt,int v)
	{
		Update(now.lv, now.nv=v);
		Update(now.lset, now.nset=v);
		now.nadd = 0;
	}
	inline void N_Add(int rt,int v)
	{
		Update(now.lv, now.nv+=v);
		if(now.nset>-INF) Update(now.lset, now.nset+=v);
		//Update的是lset,not ladd,现在更新的是set不是add//在被set影响后，所有操作都可看做set 
		else Update(now.ladd, now.nadd+=v);
	}
	void PushDown(int rt)
	{
		if(now.ladd)
			L_Add(now.ls,now.ladd),L_Add(now.rs,now.ladd),now.ladd=0;
		if(now.lset>-INF)
			L_Set(now.ls,now.lset),L_Set(now.rs,now.lset),now.lset=-INF;
		if(now.nadd)
			N_Add(now.ls,now.nadd),N_Add(now.rs,now.nadd),now.nadd=0;
		if(now.nset>-INF)
			N_Set(now.ls,now.nset),N_Set(now.rs,now.nset),now.nset=-INF;
	}
	void Modify_Add(int l,int r,int rt,int L,int R,int v)
	{
		if(L<=l && r<=R) {N_Add(rt,v); return;}
		PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify_Add(l,m,now.ls,L,R,v);
		if(m<R) Modify_Add(m+1,r,now.rs,L,R,v);
		PushUp(rt);
	}
	void Modify_Set(int l,int r,int rt,int L,int R,int v)
	{
		if(L<=l && r<=R) {N_Set(rt,v); return;}
		PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify_Set(l,m,now.ls,L,R,v);
		if(m<R) Modify_Set(m+1,r,now.rs,L,R,v);
		PushUp(rt);
	}
	int Query(int l,int r,int rt,int L,int R,bool opt)
	{
		if(L<=l && r<=R) return opt?now.nv:now.lv;
		PushDown(rt);
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return std::max(Query(l,m,now.ls,L,R,opt),Query(m+1,r,now.rs,L,R,opt));
			else return Query(l,m,now.ls,L,R,opt);
		return Query(m+1,r,now.rs,L,R,opt);
	}
}t;
#undef now

int main()
{
	n=read(), t.Build(1,n), m=read();
	char opt[3]; int x,y,z;
	while(m--)
	{
		scanf("%s",opt), x=read(),y=read();
		switch(opt[0])
		{
			case 'Q': printf("%d\n",t.Query(1,n,0,x,y,1)); break;
			case 'A': printf("%d\n",t.Query(1,n,0,x,y,0)); break;
			case 'P': z=read(), t.Modify_Add(1,n,0,x,y,z); break;
			case 'C': z=read(), t.Modify_Set(1,n,0,x,y,z); break;
		}
	}
	return 0;
}
