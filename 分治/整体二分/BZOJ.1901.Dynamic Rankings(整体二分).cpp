/*
2400kb	152ms
40ms	2.52MB
$Description$
给定$n$个数$A_i$，两种操作：
1. 查询$[l,r]$中第$k$大的数。
2. 将$A_x$改为$y$。
$n,m\leq 10^9$。
$Solution$
整体二分。
对于多组的询问、修改，我们可以发现：
假设有对p1,p2,p3...的询问，在这之前有对p0的修改（比如+1），且p0<=p1,p2,p3...，那么我们可以在修改完p0后对p1,p2,p3...这些询问修改（比如需求-1），以后对于p1,p2,p3...都不需要管这个修改了。
这样每次需要操作的序列长度只与当前区间有关。
而这个p0我们通过二分确定。不断根据p0将操作划分为两部分(两个队列)，当二分到底时(l==r)，队列里所有询问的答案就是l了。
复杂度O(nlog^2n)。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 50000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define lb(x) (x&-x)
const int N=10005,M=N*3,INF=1e9;

int n,m,Q,A[N],Ans[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Operation
{
	int K,l,r,pos;//K(opt)!=0:Query [l,r]:K;	K(opt)=0:Modify 即将要改的数是l，贡献值为r，下标为pos 
	Operation() {}
	Operation(int K,int l,int r,int pos):K(K),l(l),r(r),pos(pos) {}
}q[M],q1[M],q2[M];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline bool Is_Query()
{
	register char c=gc();
	while(c!='Q'&&c!='C') c=gc();
	return c=='Q';
}
namespace T
{
	int n,t[N];
	inline void Modify(int p,int v){
		while(p<=n) t[p]+=v, p+=lb(p);
	}
	inline int Query(int p){
		int res=0; while(p) res+=t[p], p-=lb(p);
		return res;
	}
	inline void Clear(int p){
		while(p<=n && t[p]) t[p]=0, p+=lb(p);
	}
}
void Solve(int l,int r,int h,int t)
{
	if(h>t /*|| l>r*/) return;
	if(l==r){
		for(int i=h; i<=t; ++i) if(q[i].K) Ans[q[i].pos]=l;
		return;
	}
	bool goon=0;
	for(int i=h; i<=t; ++i) if(q[i].K) {goon=1; break;}
	if(!goon) return;

	int mid=l+r>>1, t1=0, t2=0;
	for(int i=h; i<=t; ++i)
		if(q[i].K)//Query
		{
			int tmp=T::Query(q[i].r)-T::Query(q[i].l-1);
			if(tmp>=q[i].K) q1[t1++]=q[i];
			else q[i].K-=tmp, q2[t2++]=q[i];
		}
		else
		{
			if(q[i].l<=mid) q1[t1++]=q[i], T::Modify(q[i].pos,q[i].r);
			else q2[t2++]=q[i];
		}
	for(int i=0; i<t1; ++i) if(!q1[i].K) T::Clear(q1[i].pos);
	for(int i=0; i<t1; ++i) q[h+i]=q1[i];
	for(int i=0; i<t2; ++i) q[h+t1+i]=q2[i];
	Solve(l,mid,h,h+t1-1), Solve(mid+1,r,h+t1,t);
}

int main()
{
	n=read(), m=read(), Q=n; int mn=INF, mx=-INF;
	for(int i=1; i<=n; ++i) q[i]=Operation(0,A[i]=read(),1,i), mn=std::min(mn,A[i]), mx=std::max(mx,A[i]);
	int tot=0;
	for(int l,r,p,i=1; i<=m; ++i)
	{
		if(Is_Query()) l=read(), r=read(), q[++Q]=Operation(read(),l,r,++tot);
		else p=read(), q[++Q]=Operation(0,A[p],-1,p), q[++Q]=Operation(0,A[p]=read(),1,p), mn=std::min(mn,A[p]), mx=std::max(mx,A[p]);
	}
	T::n=n, Solve(mn,mx,1,Q);
	for(int i=1; i<=tot; ++i) printf("%d\n",Ans[i]);

	return 0;
}
