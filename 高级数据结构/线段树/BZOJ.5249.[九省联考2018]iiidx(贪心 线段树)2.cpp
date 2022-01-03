/*
28656kb	4280ms
从小到大枚举每个位置$x$，我们要填一个尽量大的数$v$，满足大于等于$v$且没有被用过的数至少有$sz[x]$个。
假设对于位置$x$，我们找到了这个$v$，但是大于等于$v$的数可能不只有$sz[x]$个，且我们不知道要选出哪$sz[x]$个。

把所有数从大到小排序，每个位置$i$维护它和它左边还可以选多少数$A_i$（初始$A_i=i$）。
当给位置$x$找到合适的数$v$时，$v$左边的数用哪些不确定，但$v$及$v$右边的数的左边被用到了$sz[x]$个是确定的，所以给$A_v\sim A_{d_n}$都减掉$sz[x]$。
这样对于数$v$，它左边还可以用的数的个数就是$\min\{A_v,A_{v+1},...,A_{d_n}\}$.
这样就可以在线段树上二分找适合$x$的$v$了。具体就是如果右区间的最小值$<sz[x]$，说明右区间不满足，那左区间肯定也不满足，递归到右区间；否则如果$\geq sz[x]$，右区间可行，但还需要递归到左区间看看是否可行，如果不行就直接返回相邻右区间的第一个位置。

枚举到一个点$x$时，如果它有父亲，那要把它父亲$fa[x]$为这些子树预定的值删掉（因为之前就是为了给这些子树留空间啊，枚举到这些子树的时候当然要把之前占的位置空出来了），然后找个合适的位置给$x$子树预定$sz[x]$的大小。（注意每个值别删了多次）
如果有一些相同的数$v$可以选，显然现在把最右边的那个$v$放到当前位置更优。也就是对于相同的数要从右往左依次分。

复杂度$O(n\log n)$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <functional>
#define eps 1e-9
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=5e5+5;

char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	int mn[S],tag[S];
	#undef S
	#define Upd(rt,v) mn[rt]+=v, tag[rt]+=v
	#define Update(rt) mn[rt]=std::min(mn[ls],mn[rs])
	inline void PushDown(int rt)
	{
		Upd(ls,tag[rt]), Upd(rs,tag[rt]), tag[rt]=0;
	}
	void Build(int l,int r,int rt)
	{
		mn[rt]=l;
		if(l!=r)
		{
			int m=l+r>>1;
			Build(lson), Build(rson);
		}
	}
	void Modify(int l,int r,int rt,int p,int v)
	{
		if(p<=l) {Upd(rt,v); return;}
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		Modify(rson,p,v);
		if(p<=m) Modify(lson,p,v);
		Update(rt);
	}
	int Query(int l,int r,int rt,int k)
	{
		while(l!=r)
		{
			if(tag[rt]) PushDown(rt);
			int m=l+r>>1;
			mn[rs]>=k ? (r=m,rt=ls) : (l=m+1,rt=rs);
		}
		return mn[rt]>=k?l:l+1;
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline double readdb()
{
	double x=0,y=0.1;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);x=x*10+c-48,c=gc());
	for(c=='.'&&(c=gc());isdigit(c);x+=y*(c-48),y*=0.1,c=gc());
	return x;
}

int main()
{
	static int A[N],Ans[N],sz[N],fa[N],R[N],cnt[N];
	const int n=read(); const double K=readdb();
	for(int i=1; i<=n; ++i) A[i]=read(), sz[i]=1;
	std::sort(A+1,A+1+n,std::greater<int>());
	T.Build(1,n,1);
	for(int i=n; i; --i) sz[fa[i]=(int)(i/K+eps)]+=sz[i], R[i]=A[i]==A[i+1]?R[i+1]:i;
	for(int i=1; i<=n; ++i)
	{
		if(fa[i] && fa[i]!=fa[i-1]) T.Modify(1,n,1,Ans[fa[i]],sz[fa[i]]-1);
		int p=T.Query(1,n,1,sz[i]);
		p=R[p], ++cnt[p], p-=(cnt[p]-1), Ans[i]=p;
		T.Modify(1,n,1,p,-sz[i]);
	}
	for(int i=1; i<=n; ++i) printf("%d ",A[Ans[i]]);

	return 0;
}
