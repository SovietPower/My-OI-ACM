//2740kb	132ms
//https://www.cnblogs.com/SovietPower/p/9231606.html
//原数列的值，要在树状数组上减掉啊。
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 400000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5,M=N*3;

int A[N],Ans[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Operation
{
	int l,r,k,id;//id=0:A[l]=r 变化量为k 
}q[M];
struct BIT
{
	int n,t[N];
	#define lb(x) (x&-x)
	inline void Add(int p,int v)
	{
		for(; p<=n; p+=lb(p)) t[p]+=v;
	}
	inline int Query(int p)
	{
		int res=0;
		for(; p; p^=lb(p)) res+=t[p];
		return res;
	}
	inline void Clear(int p)
	{
		for(; p<=n&&t[p]; p+=lb(p)) t[p]=0;
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline char GetOpt()
{
	register char c=gc(); while(c!='Q'&&c!='C') c=gc();
	return c;
}
void Solve(int l,int r,int h,int t)
{
	static Operation q1[M],q2[M];
	if(h>t) return;
	if(l==r)
	{
		for(int i=h; i<=t; ++i) Ans[q[i].id]=l;
		return;
	}
	bool fg=0;
	for(int i=h; i<=t; ++i) if(q[i].id) {fg=1; break;}
	if(!fg) return;
	int m=l+r>>1,t1=0,t2=0;
	for(int i=h; i<=t; ++i)
		if(q[i].id)
		{
			int tmp=T.Query(q[i].r)-T.Query(q[i].l-1);
			if(tmp>=q[i].k) q1[t1++]=q[i];
			else q[i].k-=tmp, q2[t2++]=q[i];
		}
		else if(q[i].r<=m) T.Add(q[i].l,q[i].k), q1[t1++]=q[i];
		else q2[t2++]=q[i];
	for(int i=h; i<=t; ++i) if(!q[i].id&&q[i].r<=m) T.Clear(q[i].l);
	for(int i=h,p=0; p<t1; q[i++]=q1[p++]);
	for(int i=h+t1,p=0; p<t2; q[i++]=q2[p++]);
	Solve(l,m,h,h+t1-1), Solve(m+1,r,h+t1,t);
}

int main()
{
	int n=read(),Q=read(),tot=0,now=n,mn=1e9,mx=0;
	for(int i=1; i<=n; ++i) q[i]=(Operation){i,A[i]=read(),1,0},mx=std::max(mx,A[i]),mn=std::min(mn,A[i]);
	for(int i=1,p; i<=Q; ++i)
		if(GetOpt()=='Q') q[++now]=(Operation){read(),read(),read(),++tot};
		else p=read(),q[++now]=(Operation){p,A[p],-1,0},q[++now]=(Operation){p,A[p]=read(),1,0},mx=std::max(mx,A[p]),mn=std::min(mn,A[p]);//修改原数列！
	T.n=n, Solve(mn,mx,1,now);
	for(int i=1; i<=tot; ++i) printf("%d\n",Ans[i]);

	return 0;
}
