/*
带修改莫队: 普通莫队的扩展，依旧从[l,r,t]怎么转移到[l+1,r,t],[l,r+1,t],[l,r,t+1]去考虑 
对于当前所在的区间维护一个vis[l~r]=1,在修改值时根据是否在当前区间内修改即可。 
块大小取O(n^{2/3})，排序依次按左端点所在块、右端点所在块、修改次数(时间) 
复杂度为O(n^{5/3}) 
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e4+5;

int n,m,size,bel[N],A[N],Now,tm[N*100],las[N],Ans[N];
bool vis[N*100];
struct Ask
{
	int l,r,id,t;
	Ask() {}
	Ask(int l,int r,int id,int t): l(l),r(r),id(id),t(t) {} ;
	bool operator <(const Ask &a)const
	{
		if(bel[l]==bel[a.l]) return bel[r]==bel[a.r]?t<a.t:r<a.r;
		return l<a.l;
	}
}qa[N];
struct Modify
{
	int pos,val,bef;
	Modify() {}
	Modify(int p,int v,int b): pos(p),val(v),bef(b) {} ;
}qm[1005];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Calc(int p)
{
	if(vis[p])
		if(!--tm[A[p]]) --Now;
		else ;
	else if(++tm[A[p]]==1) ++Now;
	vis[p]^=1;
}
void Change(int p,int v)
{
	if(vis[p]) Calc(p), A[p]=v, Calc(p);//(当前位置)在当前访问区间中，先将原先值删掉，再修改、添加 
	else A[p]=v;//不在访问区间中，直接改掉即可 
}

int main()
{
	n=read(),m=read(),size=pow(n,0.667);
	for(int i=1; i<=n; ++i) bel[i]=(i-1)/size+1, las[i]=A[i]=read();
	int na=0,nm=0; char opt[3];
	for(int a,b,i=1; i<=m; ++i)
	{
		scanf("%s",opt),a=read(),b=read();
		if(opt[0]=='Q') qa[++na]=Ask(a,b,na,nm);
 		else qm[++nm]=Modify(a,b,las[a]),las[a]=b;
	}
	std::sort(qa+1,qa+1+na);
	for(int l=1,r=0,t=0,i=1; i<=na; ++i)
	{
		while(t<qa[i].t) ++t,Change(qm[t].pos,qm[t].val);
		while(t>qa[i].t) Change(qm[t].pos,qm[t].bef),--t;
		while(l<qa[i].l) Calc(l++);//不能直接代入A[p] vis[]是某位置的标记 
		while(l>qa[i].l) Calc(--l);
		while(r<qa[i].r) Calc(++r);
		while(r>qa[i].r) Calc(r--);
		Ans[qa[i].id]=Now;
	}
	for(int i=1; i<=na; ++i) printf("%d\n",Ans[i]);

	return 0;
}
