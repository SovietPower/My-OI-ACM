/*
20048kb	11292ms
1316ms	24.8MB
$Description$
有$n$个国家，它们一共有$m$个空间站排列成环。$k$次操作每次对区间$[l_i,r_i]$中的空间站对应的国家数值加$a_i$，求每个国家$i$最少在几次操作后数值$\geq$给定的$need_i$（初始为$0$）。
$n,m,k\leq3\times10^5$。
$Solution$
每个国家的答案可以二分+求前缀和，于是可以想到整体二分。
在每次Solve()中要更新所有国家得到的值，不同位置的空间站对应不同国家比较麻烦。
注意到每次Solve()其国家数是与区间大小相关的，so根据国家处理，区间更新空间站的值，用vector枚举对应空间站得到每个国家的值。(or边表)
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define lb(x) (x&-x)
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=3e5+5,INF=1e9;

int n,m,K,A[N],Ans[N],q[N],q1[N],q2[N];
std::vector<int> v[N];
char IN[MAXIN],*SS=IN,*TT=IN;
inline int read();
struct Operation
{
	int l,r,v;
	inline void Input(){
		l=read(),r=read(),v=read();
	}
}op[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
namespace T//区间修改 单点查询 
{
	int n;
	LL t[N];

	inline void Modify(int p,int v){
		while(p<=n) t[p]+=v, p+=lb(p);
	}
	inline void Modify_Range(int l,int r,int v)
	{
		Modify(l,v), Modify(r+1,-v);
		if(l>r) Modify(1,v);//Modify(n+1,-v)
	}
	inline void Clear(int p)
	{
		for(; p<=n; p+=lb(p))
			if(t[p]) t[p]=0; else break;
	}
	inline void Clear_Range(int l,int r)
	{
		Clear(l), Clear(r+1);//不能少啊 
		if(l>r) Clear(1);
	}
	inline LL Query(int p)
	{
		LL res=0; while(p) res+=t[p], p^=lb(p);
		return res;
	}
}
void Solve(int l,int r,int h,int t)
{
	if(h>t) return;
	if(l==r){
		for(int i=h; i<=t; ++i) Ans[q[i]]=l;
		return;
	}
	int mid=l+r>>1, t1=0, t2=0;
	for(int i=l; i<=mid; ++i) T::Modify_Range(op[i].l,op[i].r,op[i].v);
	for(int i=h,now=q[i]; i<=t; now=q[++i])//now:may be q[n+1]
	{
		LL tmp=0;
		for(int j=0,lim=v[now].size(); j<lim; ++j)
			if((tmp+=T::Query(v[now][j]))>=A[now]) break;//tmp可能爆longlong。。不过也是个剪枝。
		if(tmp>=A[now]) q1[t1++]=now;
		else A[now]-=tmp, q2[t2++]=now;
	}
	for(int i=l; i<=mid; ++i) T::Clear_Range(op[i].l,op[i].r);//T::Modify_Range(op[i].l,op[i].r,-op[i].v);
	//T::Clear(op[i].l), T::Clear(op[i].r);//T::Clear(std::min(op[i].l,op[i].r));//因为有l>r的情况，所以要清空的位置比较麻烦。。这一行的两种都是错的。(而且应是r+1)
	for(int i=0; i<t1; ++i) q[h+i]=q1[i];
	for(int i=0; i<t2; ++i) q[h+t1+i]=q2[i];
	Solve(l,mid,h,h+t1-1), Solve(mid+1,r,h+t1,t);
}

int main()
{
	n=read(),T::n=m=read();
	for(int i=1; i<=m; ++i) v[read()].push_back(i);
	for(int i=1; i<=n; ++i) A[i]=read(), q[i]=i;
	K=read();
	for(int i=1; i<=K; ++i) op[i].Input();
	op[++K]=(Operation){m+1,m+1,0};
	Solve(1,K,1,n);
	for(int i=1; i<=n; ++i) Ans[i]==K?puts("NIE"):printf("%d\n",Ans[i]);

	return 0;
}
